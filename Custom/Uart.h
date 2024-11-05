#ifndef _Uart1_H_
#define _Uart1_H_

#include "stm32f411xe.h"

void Uart1_Init(uint16_t baudrate);
void Uart1_Transmiter(uint32_t data);
uint32_t Uart1_receiver();

#endif // _Uart1_H_