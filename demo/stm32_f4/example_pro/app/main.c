/*
 * @Author       : SuperYu 824229900@qq.com
 * @Date         : 2025-07-06 15:51
 * @LastEditors  : SuperYu 824229900@qq.com
 * @LastEditTime : 2025-08-03 16:34
 * @Description  : 
 */
#include "board.h"
#include <stdio.h>

#include "user_conf.h"


struct cbtimer cb1_timer;
struct cbtimer cb2_timer;

//void cbtimer1_callback(void* param) {
//	static uint8_t i  = 0;
//	LOG(INFO,RED,"log_write\r\n");
//	f_log_write(INFO,"test:%d",i);
//	i++;
//	cbtimer_restart(&cb1_timer);
//}

//void cbtimer2_callback(void* param) {
//	static uint8_t i = 0;
//	LOG_PACK rec_pack;
//	char mem_buffer[SUPPORT_MAX_WRITE_SIZE];
//	LOG(INFO,RED,"log_read\r\n");
//	
//	f_log_read(INFO,i,&rec_pack);
//	i++;

//	c_memcpy(mem_buffer,rec_pack.data,rec_pack.data_len);
//	mem_buffer[rec_pack.data_len] = '\0';
//	LOG(INFO,RED,"tick_time:%d\r\n",rec_pack.timestamp);
//	LOG(INFO,RED,"event_id:%d\r\n",rec_pack.event_id);

//	LOG(INFO,RED,"%x,%x,%x,%x\r\n",mem_buffer[0],mem_buffer[1],mem_buffer[2],mem_buffer[3]);

//	cbtimer_restart(&cb2_timer);
//}



int main(void)
{

	board_init();
	uart1_init(115200U);	
	tick_timer_init();
	//flash_log_init();
	uint32_t i = 2;
	uint8_t z = 10;
	
	//cbtimer_start(&cb1_timer,5000,NULL,cbtimer1_callback);
	//cbtimer_start(&cb2_timer,3000,NULL,cbtimer2_callback);
	while(1)
	{
		//cbtimer_poll();
		LOG(INFO,YELLOW,"log_read:%d\r\n",i);
		delay_ms(1000);
		LOG(INFO,RED,"log_read:%x\r\n",z);
		delay_ms(1000);
		LOG(INFO,GREEN,"log_read\r\n");
		delay_ms(1000);
		LOG(INFO,BLUE,"log_read\r\n");
		delay_ms(1000);
		LOG(INFO,MAGENTA,"log_read\r\n");
		delay_ms(1000);
		LOG(INFO,CYAN,"log_read\r\n");
		delay_ms(1000);
	}
}
