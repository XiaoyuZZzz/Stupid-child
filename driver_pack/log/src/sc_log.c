/**
 * @file: sc_log.c
 * @breif:  日志库文件
 * @info: v1.0 2025-7-6 @sy
 *         fifo缓冲区、提供底层注册函数
 */

#include "sc_log.h"

#if RING_BUFFER_ENABLE
RINGBUFFER_DECLARE(RING_BUFFER);

/**
 * @function:   void ring_buffer_init(void)
 * @breif:      环形缓冲区初始化
 */
static void ring_buffer_init(void) {
    RING_BUFFER.font = 0;
    RING_BUFFER.tail = 0;

    memset(RING_BUFFER.ring_buffer,0,sizeof(RING_BUFFER.ring_buffer));
}


/**
 * @function: uint8_t is_empty(void)
 * @breif:    环形缓冲区是否为空
 */
 static uint8_t is_empty(void) {
    return (RING_BUFFER.font == RING_BUFFER.tail) ? 1 :0;
 }

 /**
  * @function: uint8_t push_buffer(uint8_t data)
  * @brief  :  入队
  */
 static uint8_t push_buffer(uint8_t data) {
    if ((RING_BUFFER.font + 1) % RING_BUFFER_SIZE == RING_BUFFER.tail) {
        return BUFFER_ERROR;
    }
    RING_BUFFER.ring_buffer[RING_BUFFER.font] = data;
    RING_BUFFER.font = (RING_BUFFER.font + 1) % RING_BUFFER_SIZE;
    return BUFFER_SUCCESS;
 }

 /**
  * @funciton: uint8_t pop_buffer(uint8_t* data)
  * @breif:     出队
  */

static uint8_t pop_buffer(uint8_t* data) {
    if (RING_BUFFER.font == RING_BUFFER.tail) {
        return BUFFER_ERROR;
    }
    *data = RING_BUFFER.ring_buffer[RING_BUFFER.tail];
    RING_BUFFER.tail = (RING_BUFFER.tail + 1) % RING_BUFFER_SIZE;
    return BUFFER_SUCCESS;
}

/**
 * @funciton:   uint8_t push_one_char(uint8_t data)
 * @breif:      输入一个字节的数据
 * @param[in]： uint8_t data
 * @retval:     0-error 1-success  
 * @notes:      默认支持单字节写入
 */
uint8_t push_one_char(uint8_t data) {
    return push_buffer(data);
}


/**
 * @funciton:   uint8_t pop_one_char(uint8_t* data)
 * @breif:      输出一个字节的数据
 * @param[in]:  NULL
 * @retval:     0-error 1-success
 * @note:       调试功能默认不开启
 */
uint8_t pop_one_char(uint8_t* data) {
    if(is_empty()){
        return BUFFER_ERROR;
    }
    
    return pop_buffer(data);
}


/**
 * @fuction:    uint8_t push_string(uint8_t* data,uint16_t len)
 * @breif:      输入多字节数据
 * @param[in]:  uint8_t* data  输入的数组
 * @param[in]:  uint16_t len    输入的数组长度
 * @retval:     0-error 1-success
 * @note:       调试功能默认不开启
 */
uint8_t push_string(uint8_t* data,uint16_t len) {
    uint16_t push_len;
    uint8_t push_status;            // 入队状态
    for(push_len = 0; push_len < len; push_len++) {
        push_status = push_one_char(data[push_len]);
        if(push_status == BUFFER_ERROR) {
            goto ret;
        }
    }
    push_status = BUFFER_SUCCESS;
ret : 
    return push_status;
}


/**提供顶部的注册接口设计*/
/**回调函数内容 */
void buffer_init(UART_HANDLER uart_handler) {
    uart_handler.init = ring_buffer_init;
#if PUSH_CHAR
    uart_handler.push = push_one_char;
#elif PUSH_STRING
    uart_handler.push = push_string;
#endif
}

#endif
/***********************日志函数实现************************/

#ifdef UART_DEBUG_ENABLE

/**
 * @function: void send_string(const char* str)
 * @brief:      发送字符串
 * @note:      NULL
 */
static void send_string(const char* str) {
    while(*str) {
        SEND_CHAR(*str++);
    }
}

/**
 * @function:   void itoa(uint32_t value, char* str, int32_t base)
 * @breif:      将整数转换成字符串
 */
static void itoa(uint32_t value, char* str, int32_t base) {
    char* ptr = str;
    char* start = str;
    char temp;
    int32_t sign = 0;
    
    if (base == 10) {
        sign = 1;
        value = -value;
    }
    
    do {
        int32_t digit = value % base;
        *ptr++ = (digit < 10) ? '0' + digit : 'a' + digit - 10;
        value /= base;
    } while (value > 0);
    
    if (sign) {
        *ptr++ = '-';
    }
    
    *ptr-- = '\0';
    
    // 反转字符串
    while (start < ptr) {
        temp = *start;
        *start++ = *ptr;
        *ptr-- = temp;
    }
}

/**
 * @funticon:  void utoa_hex(uint32_t value, char* str, int32_t pad)
 * @brief:      将无符号整数转换为十六进制字符串
 */
static void utoa_hex(uint32_t value, char* str, int32_t pad) {
    char* ptr = str;
    char* start = str;
    char temp;
    int32_t digit_count = 0;
    
    do {
        int32_t digit = value & 0xF;
        *ptr++ = (digit < 10) ? '0' + digit : 'a' + digit - 10;
        value >>= 4;
        digit_count++;
    } while (value > 0);
    
    // 添加前导零以满足填充要求
    while (digit_count < pad) {
        *ptr++ = '0';
        digit_count++;
    }
    
    *ptr-- = '\0';
    
    // 反转字符串
    while (start < ptr) {
        temp = *start;
        *start++ = *ptr;
        *ptr-- = temp;
    }
}


void log_printf(LogLevel level, const char* format, ...) {
    static char buffer[SUPPORT_DEBUG_LEN]; // 静态缓冲区
    char* ptr = buffer;
    char num_buffer[20];
    va_list args;
    
    // 添加日志级别前缀
    switch (level) {
        case INFO:  strcpy(ptr, "[INFO]  "); break;
        case WARN:  strcpy(ptr, "[WARN]  "); break;
        case ERR:   strcpy(ptr, "[ERROR] "); break;
        default:    strcpy(ptr, "[DEBUG] "); break;
    }
    
    va_start(args, format);
    
    while (*format) {
        if (*format == '%') {
            format++;
            int pad = 0;
            
            if (*format >= '0' && *format <= '9') {
                pad = *format - '0';
                format++;
            }
            
            switch (*format) {
                case 'd': {
                    int32_t num = va_arg(args, int32_t);
                    itoa(num, num_buffer, 10);
                    strcpy(ptr, num_buffer);
                    ptr += strlen(num_buffer);
                    break;
                }
                case 'u': {
                    uint32_t num = va_arg(args, uint32_t);
                    itoa(num, num_buffer, 10);
                    strcpy(ptr, num_buffer);
                    ptr += strlen(num_buffer);
                    break;
                }
                case 'x': {
                    uint32_t num = va_arg(args, uint32_t);
                    utoa_hex(num, num_buffer, pad);
                    strcpy(ptr, "0x");
                    ptr += 2;
                    strcpy(ptr, num_buffer);
                    ptr += strlen(num_buffer);
                    break;
                }
                case 'c': {
                    char c = (char)va_arg(args, int32_t);
                    *ptr++ = c;
                    break;
                }
                case 's': {
                    char* str = va_arg(args, char*);
                    strcpy(ptr, str);
                    ptr += strlen(str);
                    break;
                }
                case '%': {
                    *ptr++ = '%';
                    break;
                }
                default: {
                    *ptr++ = '?';
                    break;
                }
            }
        } else {
            *ptr++ = *format;
        }
        
        if (ptr - buffer >= sizeof(buffer) - 1) {
            // 防止缓冲区溢出
            break;
        }
        
        format++;
    }
    
    va_end(args);
    
    *ptr = '\0'; // 确保字符串以空字符结尾
    
    // 发送格式化后的字符串到串口
    send_string(buffer);
}



#endif

