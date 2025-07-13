
 
#include "bsp_uart.h" 
#include "stdio.h"

void uart1_init(uint32_t __Baud)
{
	GPIO_InitTypeDef GPIO_InitStructure;	

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);	

	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1);

	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin           = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode          = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed         = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType         = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd          = GPIO_PuPd_UP;
	GPIO_Init(GPIOA,&GPIO_InitStructure);

	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin           = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode          = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed         = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType         = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd          = GPIO_PuPd_UP;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
  
	USART_InitTypeDef USART_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

	USART_DeInit(USART1);
	USART_StructInit(&USART_InitStructure);
	USART_InitStructure.USART_BaudRate              = __Baud;
	USART_InitStructure.USART_WordLength            = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits              = USART_StopBits_1;
	USART_InitStructure.USART_Parity                = USART_Parity_No ;
	USART_InitStructure.USART_Mode                  = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStructure.USART_HardwareFlowControl   = USART_HardwareFlowControl_None; 
	USART_Init(USART1,&USART_InitStructure);
	
	USART_ClearFlag(USART1,USART_FLAG_RXNE);

	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

	USART_Cmd(USART1,ENABLE);
	
	NVIC_InitTypeDef NVIC_InitStructure;

	NVIC_InitStructure.NVIC_IRQChannel                    = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority  = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority         = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd                 = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
		
}

#if !defined(__MICROLIB)
#if (__ARMCLIB_VERSION <= 6000000)

struct __FILE
{
	int handle;
};
#endif

FILE __stdout;

void _sys_exit(int x)
{
	x = x;
}
#endif

int fputc(int ch, FILE *f)
{
    USART_SendData(USART1, (uint8_t)ch);
	
	while( RESET == USART_GetFlagStatus(USART1, USART_FLAG_TXE) ){}
	
    return ch;
}

void USART1_IRQHandler(void)
{
	if(USART_GetITStatus(USART1, USART_IT_RXNE) == SET)//�ж��ǲ���������жϷ���
	{
		//USART_SendData(USART1,USART_ReceiveData(USART1));//�ֽ����ݷ���ȥ(������֤)
		
		
		USART_ClearITPendingBit(USART1, USART_IT_RXNE); //�Ѿ������������־λ 
	}  
}

/**
 * @function:   void send_char(uint8_t data);
 * @brief:		发送一个字节的函数
 */
void send_char(uint8_t data) {
	while (!(USART1->SR & USART_SR_TXE));
    USART1->DR = data;
}




