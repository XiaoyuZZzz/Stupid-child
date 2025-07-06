
 
#include "bsp_uart.h" 
#include "stdio.h"

void uart1_init(uint32_t __Baud)
{
	GPIO_InitTypeDef GPIO_InitStructure;	

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);	

	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1);//IO��������������Ҫ���ø���ģʽ
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1);

	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin           = GPIO_Pin_9;//TX����
	GPIO_InitStructure.GPIO_Mode          = GPIO_Mode_AF;//IO��������������Ҫ���ø���ģʽ
	GPIO_InitStructure.GPIO_Speed         = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType         = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd          = GPIO_PuPd_UP;
	GPIO_Init(GPIOA,&GPIO_InitStructure);

	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin           = GPIO_Pin_10;//RX����
	GPIO_InitStructure.GPIO_Mode          = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed         = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType         = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd          = GPIO_PuPd_UP;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
  
	USART_InitTypeDef USART_InitStructure;//�������ô��ڵĽṹ�����

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);//��������1��ʱ��

	USART_DeInit(USART1);//�����˼�ǽ���˴��ڵ���������

	USART_StructInit(&USART_InitStructure);
	USART_InitStructure.USART_BaudRate              = __Baud;//���ò�����
	USART_InitStructure.USART_WordLength            = USART_WordLength_8b;//�ֽڳ���Ϊ8bit
	USART_InitStructure.USART_StopBits              = USART_StopBits_1;//1��ֹͣλ
	USART_InitStructure.USART_Parity                = USART_Parity_No ;//û��У��λ
	USART_InitStructure.USART_Mode                  = USART_Mode_Rx | USART_Mode_Tx;//����������Ϊ�շ�ģʽ
	USART_InitStructure.USART_HardwareFlowControl   = USART_HardwareFlowControl_None; //���ṩ���� 
	USART_Init(USART1,&USART_InitStructure);//����ز�����ʼ��������1
	
	USART_ClearFlag(USART1,USART_FLAG_RXNE);//��ʼ����ʱ���������λ

	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//��ʼ���ý����ж�

	USART_Cmd(USART1,ENABLE);//��������1
	
	NVIC_InitTypeDef NVIC_InitStructure;//�жϿ��ƽṹ���������

	NVIC_InitStructure.NVIC_IRQChannel                    = USART1_IRQn;//�ж�ͨ��ָ��ΪUSART1
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority  = 0;//�����ȼ�Ϊ0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority         = 1;//�����ȼ�Ϊ1
	NVIC_InitStructure.NVIC_IRQChannelCmd                 = ENABLE;//ȷ��ʹ��
	NVIC_Init(&NVIC_InitStructure);//��ʼ�����ô��ж�ͨ��
		
}

#if !defined(__MICROLIB)
//��ʹ��΢��Ļ�����Ҫ��������ĺ���
#if (__ARMCLIB_VERSION <= 6000000)
//�����������AC5  �Ͷ�����������ṹ��
struct __FILE
{
	int handle;
};
#endif

FILE __stdout;

//����_sys_exit()�Ա���ʹ�ð�����ģʽ
void _sys_exit(int x)
{
	x = x;
}
#endif

/* retarget the C library printf function to the USART */
int fputc(int ch, FILE *f)
{
    USART_SendData(USART1, (uint8_t)ch);
	
	while( RESET == USART_GetFlagStatus(USART1, USART_FLAG_TXE) ){}
	
    return ch;
}



/******** ����1 �жϷ����� ***********/
void USART1_IRQHandler(void)
{
	if(USART_GetITStatus(USART1, USART_IT_RXNE) == SET)//�ж��ǲ���������жϷ���
	{
		//USART_SendData(USART1,USART_ReceiveData(USART1));//�ֽ����ݷ���ȥ(������֤)
		
		
		USART_ClearITPendingBit(USART1, USART_IT_RXNE); //�Ѿ������������־λ 
	}  
}


