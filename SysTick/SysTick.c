#include "Systick.h"

void SysTick_Delay(uint32_t time) {
    int i = 0;

    // Set the reload value for 1ms delay ( 16 MHz system clock)
    SysTick->LOAD = 16000 - 1;  // 1 ms delay (16000 clock cycles for 16 MHz)
    
    // Clear the current value register
    SysTick->VAL = 0;
    
    // Enable SysTick and Select Internal Clock 
    SysTick->CTRL = (1U << 0) | (1U << 2);  // Enable SysTick and select processor clock

    for (i = 0; i < time; i++) {
        // Wait until the COUNTFLAG is set 
        while ((SysTick->CTRL & (1U << 16)) == 0) {}
    }

    // Clear Systick
    SysTick->CTRL = 0;
}
void Delay_second(uint32_t seconds) {
    SysTick_Delay(seconds * 1000); // G?i hàm Delay_milisecond d? t?o d? tr? b?ng giây
}