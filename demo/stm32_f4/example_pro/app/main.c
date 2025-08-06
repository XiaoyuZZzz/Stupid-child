/*
 * @Author       : SuperYu 824229900@qq.com
 * @Date         : 2025-07-06 15:51
 * @LastEditors  : Please set LastEditors
 * @LastEditTime : 2025-08-07 00:19
 * @Description  : 
 */
#include "board.h"
#include <stdio.h>

#include "user_conf.h"


UART_HANDLER usart_handler;

int main(void)
{

	board_init();
	uart1_init(115200U);	
	tick_timer_init();
	buffer_init(&usart_handler);
	uint8_t temp_buf[RING_BUFFER_SIZE];
	while(1)
	{
		uint16_t num = usart_handler.get_data(temp_buf, sizeof(temp_buf));
		if (num > 0) {
			for (uint16_t i = 0; i < num; i++) {
				send_char(temp_buf[i]);
			}
		}
		// 添加短暂延时防止CPU满载
		delay_ms(1);
	}
}
