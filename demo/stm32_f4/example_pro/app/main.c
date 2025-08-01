/*
 * @Author       : SuperYu 824229900@qq.com
 * @Date         : 2025-07-06 15:51
 * @LastEditors  : SuperYu 824229900@qq.com
 * @LastEditTime : 2025-08-01 21:15
 * @Description  : 
 */
#include "board.h"
#include <stdio.h>

#include "user_conf.h"




int main(void)
{

	board_init();
	uart1_init(115200U);	
	tick_timer_init();
	flash_log_init();
	
	while(1)
	{

	}
}
