#include "board.h"
#include "bsp_uart.h"
#include <stdio.h>

#include "user_conf.h"

int main(void)
{
	
	board_init();
	uart1_init(115200U);	
	while(1)
	{
		LOG(ERR,RED,"file_error\r\n");
		delay_1ms(500);
		LOG(INFO,GREEN,"file_info\r\n");
		delay_1ms(500);
	}
	

}
