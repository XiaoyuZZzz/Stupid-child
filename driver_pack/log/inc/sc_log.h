/**
 * @file: sc_log.h
 */

 #ifndef SC_LOG_H__
 #define SC_LOG_H__


#include "sc_conf.h"

#include <string.h>

/**日志*/
#if DEBUG_ENABLE

#ifdef RTT_DEBUG_ENABLE
#include "SEGGER_RTT.h"

#define LOG_I(ID,Index,sFormat,...) do{\
    SEGGER_RTT_SetTerminal(ID);\
    SEGGER_RTT_printf(Index,sFormat);\
    SEGGER_RTT_printf(Index,"[:%s->%s],%s ",__FILE__,__func__, ##__VA_ARGS__);\
}while(0);

#else 
#define LOG_I(ID,Index,sFormat,...)  ((void)0)
#endif

#ifdef UART_DEBUG_ENABLE
#include <stdarg.h>
typedef enum {
    ERR,
    INFO,
    WARN
}LogLevel;

/**需要终端支持ANSI颜色 */
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

void log_printf(LogLevel level, const char* format, ...);
#else 
#define log_printf			((void)0)
#endif
#ifdef FLASH_DEBUG_ENABLE

#endif
#else
#define LOG(name,colro,format, ...)     ((void)0)
#endif






#define LOG(name,color,format, ...)  do{\
    if(DEBUG_TARGETS & DEBUG_RTT_BIT) { \
        LOG_I(\
            name##_TERMINAL_ID, \
            name##_CHANNEL_INDEX, \
            RTT_CTRL_TEXT_BRIGHT_##color format, \
            ##__VA_ARGS__); \
    } \
    if(DEBUG_TARGETS & DEBUG_UART_BIT) { \
        log_printf(\
            name,\
            ANSI_COLOR_##color "[" #name":%s->%s]:%s",__FILE__,__func__, format, \
            ##__VA_ARGS__);\
    } \
    if(DEBUG_TARGETS & DEBUG_FLASH_BIT) { \
    } \
}while(0);



#endif
