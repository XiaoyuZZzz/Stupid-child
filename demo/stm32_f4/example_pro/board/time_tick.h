#ifndef TIME_TICK_H__
#define TIME_TICK_H__

#include "stm32f4xx.h" 
#include "stm32f4xx_tim.h"


void tick_timer_init(void);
uint32_t get_heart_tick_time(void);

#endif

