#ifndef _Encoder_H_
#define _Encoder_H_

#include "stm32f411xe.h"

 
#define readEncoder1 (( GPIOC->IDR>>8)&0x1)
#define readEncoder2 (( GPIOC->IDR>>6)&0x1)
void EXTI9_5_IRQHandler(void); 
void Exti_Init(void);



#endif // _Encoder_H_