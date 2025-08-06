 #ifndef __BSP_UART_H__
 #define __BSP_UART_H__
 
 #include "stm32f4xx.h"
 #include "user_conf.h"
 
 
#define USART_RX_DMA_STREAM DMA2_Stream5
#define USART_RX_DMA_CHANNEL DMA_Channel_4
 
void uart1_init(uint32_t __Baud);
void USART1_IRQHandler(void);
 
void send_char(uint8_t data);
void uart1DmaClear(void);
 
 
 
 
 
#endif
