/*
 * @Author       : SuperYu 824229900@qq.com
 * @Date         : 2025-07-06 15:51
 * @LastEditors  : Please set LastEditors
 * @LastEditTime : 2025-08-09 19:56
 * @Description  : 
 */
#include "board.h"
#include <stdio.h>

#include "user_conf.h"

#include "lcd_ui.h"
#include "pic.h"


UART_HANDLER usart_handler;

int main(void)
{

	board_init();
	uart1_init(115200U);	
	tick_timer_init();
	buffer_init(&usart_handler);
	ui_init();
	ui_show_picture(0,0,152,152,gImage_2,BLACK);
	//ui_show_string(0,0,"hello world",16,BLACK);
#if 1
	uint8_t temp_buf[RING_BUFFER_SIZE];
	uint8_t cmp_buf[RING_BUFFER_SIZE];
#endif
	

	while(1)
	{
		ui_sleep();
/*用于测试自定义段数据是否能够正常处理*/		
#if 1
		uint16_t num = usart_handler.get_data(temp_buf, sizeof(temp_buf));
		memset(cmp_buf,0,RING_BUFFER_SIZE);
		c_memcpy(cmp_buf,temp_buf,num);
		if(num > 0 ) {
			process_command(cmp_buf);
		}
		
		// 添加短暂延时防止CPU满载
		delay_ms(1);
#endif
#if 0
		
		LOG(INFO,RED,"info1\r\n");
		delay_ms(1000);
		LOG(ERR,RED,"err1\r\n");
		delay_ms(1000);
		LOG(WARN,RED,"warn1\r\n");
		delay_ms(1000);
		
		LOG(INFO,GREEN,"info2\r\n");
		delay_ms(1000);
		LOG(ERR,GREEN,"err2\r\n");
		delay_ms(1000);
		LOG(WARN,GREEN,"warn2\r\n");
		delay_ms(1000);
		
		LOG(INFO,BLUE,"info2\r\n");
		delay_ms(1000);
		LOG(ERR,BLUE,"err2\r\n");
		delay_ms(1000);
		LOG(WARN,BLUE,"warn2\r\n");
		delay_ms(1000);
#endif		
	}
}
