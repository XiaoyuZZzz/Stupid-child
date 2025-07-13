/**
 * @file: sc_conf.h
 * @brief: 对外进行宏定义开启关闭
 * @info: v1.0  2025-7-6    @sy
 * @changelog: 1.添加RTT调试部分
 */


 #ifndef SC_CONF_H__
 #define SC_CONF_H__
 
 #include "user_conf.h"

 /******************************LOG*********************************/
 /**
 * 开启调试
 * 支持DEBUG_RTT、DEBUG_UART、DEBUG_FLASH
 * TODO:目前只支持前两个调试方法
 */
#define DEBUG_ENABLE    (1)
/* 
 * |DEBUG_ENABLE
 * |->DEBUG
 * |-->DEBUG_RTT
 * |-->DEBUG_UART
 * |-->DEBUG_FLASH
 * |-->warning message
 */
// TODO:日志部分调试完成之后需要修改成NOT_SUPPORT
#if DEBUG_ENABLE
#define NOT_SUPPORT         (1 << 0)
#define DEBUG_RTT_BIT       (1 << 1)
#define DEBUG_UART_BIT      (1 << 2)
#define DEBUG_FLASH_BIT     (1 << 3)
#define DEBUG_TARGETS       (DEBUG_UART_BIT)

#if (DEBUG_TARGETS & DEBUG_RTT_BIT) 
#define ERR_TERMINAL_ID     (0)      
#define ERR_CHANNEL_INDEX   (0)
#define INFO_TERMINAL_ID    (1)
#define INFO_CHANNEL_INDEX  (0)   
#define RAW_TERMINAL_ID     (2)
#define RAW_CHANNEL_INDEX   (0)
#define WARN_TERMINAL_ID    (3)
#define WARN_CHANNEL_INDEX  (0)

#define RTT_DEBUG_ENABLE
#endif
#if (DEBUG_TARGETS & DEBUG_UART_BIT) 
#define UART_DEBUG_ENABLE

/**用户API接口定义*/
#define SEND_CHAR                   send_char               //注册用户底层的发送字节函数
#define SUPPORT_DEBUG_LEN           (128)                   //默认支持128字节的长度调试

#endif
#if (DEBUG_TARGETS & DEBUG_FLASH_BIT) 
#define FLASH_DEBUG_ENABLE
#endif
#if (DEBUG_TARGETS & NOT_SUPPORT)
#warning "Debug functionality is disabled"
#endif

#endif
/***********************RING_BUFFER******************************/
#define RING_BUFFER_ENABLE     (0)
#if RING_BUFFER_ENABLE

/**设置环形缓冲区的大小*/
#define RING_BUFFER_SIZE        (128)
/**环形缓冲区设置写入方式，默认一字节写入*/
#define PUSH_CHAR               (1)
#define PUSH_STRING             (0)
/**环形缓冲数组 */
#ifdef _WIN32
    #define ALIGN_4 __declspec(align(4))
#else
    #define ALIGN_4 __attribute__((aligned(4))) 
#endif

#define RINGBUFFER_DECLARE(name)\
    struct ALIGN_4 name##_type {   \
        uint8_t                ring_buffer[RING_BUFFER_SIZE];\
		volatile uint16_t      font;\
        volatile uint16_t      tail;\
    } name

enum {
    BUFFER_ERROR,
    BUFFER_SUCCESS
};  

typedef struct {
    void(*init)(void);              /**初始化*/
#if PUSH_CHAR
    uint8_t(*push)(uint8_t data);      /**单字节写入*/
#elif PUSH_STRING
    uint8_t(*push)(uint8_t* data,uint16_t len);    /**多字节写入*/
#endif
}UART_HANDLER;

void buffer_init(UART_HANDLER uart_handler);
#endif
/******************************DRIVER*********************************/

#define AGREEMENT_ENABLE    (1)

#if AGREEMENT_ENABLE
#define NOT_AGREEMENT       (1 << 0)
#define AGREEMENT_SPI       (1 << 1)
#define AGREEMENT_IIC       (1 << 2)
#define AGREEMENT_TARGETS   (NOT_AGREEMENT)

#endif







#endif

