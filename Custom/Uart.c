#include "Uart.h"

void Uart1_Init(uint16_t baudrate){
	
	RCC->AHB2ENR|=(1U<<4); // Enable to RCC of Usart1
	
	RCC->AHB1ENR|=(1U<<0); // Enable to RCC of GPIOA
	
	// Configure PA9 (TX) and PA10 (RX) in alternate function mode
	GPIOA->MODER&=~(0xF<<18); // Clear bit 
	GPIOA->MODER|=(0xA<<18); // set PA9,PA10 AF mode
	GPIOA->AFR[1]|=(7U<<4); // AF mapping AF07 of PA9
	GPIOA->AFR[1]|=(7U<<8); // AF mapping AF07 of PA10
	
	// Configure Usart1
	USART1->CR1|=(0x3<<2); // Set RE&TE to enable
	
	// Configure USART2 baud rate based on input parameter for 16Mhz clock
	switch (baudrate){
		case 9600:
			USART1->BRR|=(104<<4)|(3<<0); 
		case 115200:
			USART1->BRR|=(8U<<4)|(0U<<0);
		default:
			break;
	}
USART1->BRR|=(104<<4)|(3<<0); 
	USART1->CR1|=(1U<<13); // EN Usart
}

void Uart1_Transmiter(uint8_t *data, uint16_t size) {
    for (uint16_t i = 0; i < size; i++) {
     
        while (!((USART2->SR >> 7) & 0x1));

        
        USART2->DR = data[i];

        
        while (!((USART2->SR >> 6) & 0x1));
    }
}
uint32_t Uart1_Receiver(){
	// Wait until the data is ready to be received (RXNE bit set)
	while( !((USART1->SR>>5)&0x1));
	
	return USART1->DR;

}
