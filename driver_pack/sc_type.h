/**
 * @file: sc_type.h
 * @brief: 类型定义，中间件采用自定义类型，避免不同项目使用的类型不一致
 * @info: v1.0  2025-7-6    @sy
 *        文件的自定义类型
 */

 #ifndef SC_TYPE_H__
 #define SC_TYPE_H__

#ifdef __cplusplus
extern "C"{
#endif

#include "core_cm4.h"             /* Cortex-M4 processor and core peripherals */
#include "system_stm32f4xx.h"
#include <stdint.h>

/*log_type*/
typedef unsigned char  ulog8_t;
typedef char log8_t;
typedef unsigned short ulog16_t;
typedef short   log16_t;
typedef unsigned int    ulog32_t;
typedef int log32_t;
 










#ifdef __cplusplus
}
#endif
#endif
