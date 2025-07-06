#ifndef __BOARD_H__
#define __BOARD_H__

#include "stm32f4xx.h"

void board_init(void);
void delay_us(uint32_t _us);
void delay_ms(uint32_t _ms);
void delay_1ms(uint32_t ms);
void delay_1us(uint32_t us);

#endif
