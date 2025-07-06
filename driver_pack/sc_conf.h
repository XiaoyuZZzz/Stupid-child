/**
 * @file: sc_conf.h
 * @brief: 对外进行宏定义开启关闭
 * @info: v1.0  2025-7-6    @sy
 * @changelog: 1.添加RTT调试部分
 */


 #ifndef SC_CONF_H__
 #define SC_CONF_H__
 
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

#if DEBUG_ENABLE
#define NOT_SUPPORT         (1 << 0)
#define DEBUG_RTT_BIT       (1 << 1)
#define DEBUG_UART_BIT      (1 << 2)
#define DEBUG_FLASH_BIT     (1 << 3)
#define DEBUG_TARGETS       (DEBUG_RTT_BIT)


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
#endif

#if (DEBUG_TARGETS & DEBUG_FLASH_BIT) 
#define FLASH_DEBUG_ENABLE
#endif

#if (DEBUG_TARGETS & NOT_SUPPORT)
#warning "Debug functionality is disabled"
#endif

#endif

#endif

