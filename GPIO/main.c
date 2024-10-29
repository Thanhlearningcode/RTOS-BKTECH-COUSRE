#include "stm32f411xe.h"
int a=0;
void TIM1_Init(void){
RCC->APB2ENR|=(1U<<0);
	TIM1->CNT=0;
    TIM1->PSC = 15;          
    TIM1->ARR = 999;
	TIM1->CR1|=(1U<<7);
	TIM1->CR1&=~(1U<<4);
	TIM1->CR1&=~(1U<<2);
		TIM1->CR1&=~(1U<<1);
	TIM1->EGR|=(1U<<0);
	TIM1->CR1|=(1U<<0);
}
void Delay_VanThanh(uint16_t time){
	TIM1->EGR=0;
while(time>0){
while( (TIM1->SR&0x1)==1){
time--;
	TIM1->SR&=~0x1;
}}}
void EXTI0_Init(void)
{
    /* Enable clock for SYSCFG and GPIOA */
    RCC->APB2ENR |= (1U << 14);
    RCC->AHB1ENR |= (1U << 0);
    /* Configure GPIOA Pin 0 as input */
    GPIOA->MODER &= ~(3U << 0);
    SYSCFG->EXTICR[0] &= ~(0xFU << 0);
    EXTI->FTSR |= (1U << 0);  // Falling edge
    EXTI->RTSR &= ~(1U << 0); // Disable rising edge
    EXTI->IMR |= (1U << 0);  // Unmask EXTI0 interrupt
    EXTI->PR |= (1U << 0);   // Clear pending flag
    NVIC_EnableIRQ(EXTI0_IRQn);
}

void LED_MODE(int Pin,int TimeDelay){
	TIM1->CNT=0;
  GPIOD->ODR ^= (1 << Pin);
  Delay_VanThanh(TimeDelay);
}
void Mode(void(*ptr)(int,int),int Pin,int TimeDelay){
ptr(Pin,TimeDelay);
}
void EXTI0_IRQHandler(void){
	a++;
	if( a%2==1){
Mode(LED_MODE,12,1000);
	}
else{
Mode(LED_MODE,12,3000);
}
EXTI->PR;
}   
int main(){	
	  EXTI0_Init();
	  TIM1_Init();
    RCC->AHB1ENR |= (1U << 3);  // Enable clock for GPIOD
    GPIOD->MODER &= ~(0x3 << 24); 
    GPIOD->MODER |= (0x1 << 24); 
		GPIOD->MODER &= ~(0x3 << 26); 
    GPIOD->MODER |= (0x1 << 26);  
	  GPIOD->MODER &= ~(0x3 << 28); 
    GPIOD->MODER |= (0x1 << 28); 
	  GPIOD->MODER &= ~(0x3 << 30); 
    GPIOD->MODER |= (0x1 << 30);  
    GPIOD->OTYPER &= ~(1U <<12); 
    GPIOD->OTYPER &= ~(1U << 13); 
    GPIOD->OTYPER &= ~(1U << 14); 
	  GPIOD->OTYPER &= ~(1U << 15); 
    GPIOD->ODR &= ~(1U << 12); 
	  GPIOD->ODR &= ~(1U << 13); 
	  GPIOD->ODR &= ~(1U << 14); 
    while(1) {
		}
		}

