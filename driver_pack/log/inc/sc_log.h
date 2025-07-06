/**
 * @file: sc_log.h
 */

 #ifndef SC_LOG_H__
 #define SC_LOG_H__


#include "sc_type.h"
#include "sc_conf.h"

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
#endif
#ifdef FLASH_DEBUG_ENABLE
#endif


#define LOG(name,colro,format, ...)  do{\
    if(DEBUG_TARGETS & DEBUG_RTT_BIT) { \
        LOG_I(\
            name##_TERMINAL_ID, \
            name##_CHANNEL_INDEX, \
            RTT_CTRL_TEXT_BRIGHT_##colro format,\
            ##__VA_ARGS__); \
    } \
    if(DEBUG_TARGETS & DEBUG_UART_BIT) { \
    } \
    if(DEBUG_TARGETS & DEBUG_FLASH_BIT) { \
    } \
}while(0);

#else
#define LOG(name,colro,format, ...)     ((void)0)

#endif

#endif
