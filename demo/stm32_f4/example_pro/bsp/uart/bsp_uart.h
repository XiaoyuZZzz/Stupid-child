 #ifndef __BSP_UART_H__
 #define __BSP_UART_H__
 
 #include "stm32f4xx.h"
 
 
 
 //�ⲿ�ɵ��ú���������
void uart1_init(uint32_t __Baud);
void USART1_IRQHandler(void);
 
void send_char(uint8_t data);
 
 
 
 
 
#endif
