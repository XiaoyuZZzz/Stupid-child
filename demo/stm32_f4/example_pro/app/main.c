/*
 * @Author       : SuperYu 824229900@qq.com
 * @Date         : 2025-07-06 15:51
 * @LastEditors  : Please set LastEditors
 * @LastEditTime : 2025-08-07 22:50
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
	uint8_t cmp_buf[RING_BUFFER_SIZE];
	while(1)
	{

		uint16_t num = usart_handler.get_data(temp_buf, sizeof(temp_buf));
		memset(cmp_buf,0,RING_BUFFER_SIZE);
		c_memcpy(cmp_buf,temp_buf,num);
		if(num > 0 ) {
			process_command(cmp_buf);
		}
		
		// 添加短暂延时防止CPU满载
		delay_ms(1);
		
	}
}
