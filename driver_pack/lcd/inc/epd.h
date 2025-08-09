/*
 * @file         : epd.h
 * @Author       : shuyu
 * @LastEditTime : 2025-08-09 20:58
 * @Description  : 
 */

#include "lcd_driver.h"

/*!> 局部刷新需要在局部刷新模式下使用*/

/*******************
Rotate:0-0度方向
Rotate:90-90度方向
Rotate:180-180度方向
Rotate:270-270度方向
*******************/

// 是否支持局部
#define PART_ENABLE         (1)
// 是否支持快速
#define FAST_ENABLE         (1)

/**如果开启了快刷需要选择一个模式,默认如果开启快刷是开启快刷模式1.如果需要修改成快刷模式2，则需要将其置位 */
#if FAST_ENABLE
#define MODE                (0)
#if MODE
#define MODE1 
#else
#define MODE2        
#endif
#endif



#define SLEEP_CMD               (0x10)
#define RESET_CMD               (0x12)
#define MASTER_Activation       (0x20)
#define UP_MODE_2               (0x22)
#define WRITE_RAM               (0x24)

void ssd1680_driver_init_callback(LCD_DRIVER* lcd_driver);

