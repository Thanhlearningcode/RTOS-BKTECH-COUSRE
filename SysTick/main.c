#include "stm32f411xe.h"
#include "SysTick.h"
/*******************************DATA***********************************************/

 uint16_t vin, temp;
 /*******************************Functions***********************************************/
void ADC_init();
uint16_t Read_ADC();




int main(void){
				ADC_init();
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
	while(1){
				uint16_t cnt = Read_ADC(); // Read the ADC value
        vin = (cnt * 3.3) / 4095; // Convert ADC value to voltage
        temp = (vin - 0.76) / 0.025; // Convert voltage to temperature
		
				SysTick_Delay(1000); // TIME SAMPLING 1s
		
	if(temp>0) {GPIOD->ODR |= ( 1U<<12);  GPIOD->ODR &= ~(1U << 13);  GPIOD->ODR &= ~(1U << 14); }  // LED 12 ON
	
	else if( temp>20) {GPIOD->ODR |= ( 1U <<13) ; GPIOD->ODR &= ~(1U << 12);  GPIOD->ODR &= ~(1U << 14);}  // LED 13 ON

	else if( temp >40) {GPIOD->ODR |= ( 1U <<14) ; GPIOD->ODR &= ~(1U << 13);  GPIOD->ODR &= ~(1U << 12);} // LED 14 ON
	
	
		}

}

// Author: Nguyen Van Thanh
void ADC_init() {
    // Enable the clock for ADC1
    RCC->AHB2ENR |= (1<<8);
    
    // Configure the injected sequence register for channel 16 (temperature sensor)
    uint32_t* JSQR = (uint32_t*)0x40012338; // Injected Sequence Register
    *JSQR |= (1 << 15); // Set channel 16 for JSQ4

    // Setup Control Registers
    uint32_t* CR1 = (uint32_t*)0x40012404; // Control Register 1
    uint32_t* CR2 = (uint32_t*)0x40012408; // Control Register 2
    *CR2 |= (1 << 20); // Enable continuous conversion

    // Setup the Common Control Register
    uint32_t* CCR = (uint32_t*)0x40012304; // Common Control Register
    *CCR |= (1 << 23); // Configure common functionalities
}

// Function to read the ADC value
uint16_t Read_ADC() {
    // Start the ADC conversion
    uint32_t* CR2 = (uint32_t*)0x40012408; // Control Register 2
    *CR2 |= (1 << 22); // Start conversion

    // Wait for conversion to complete
    uint32_t* SR = (uint32_t*)0x40012400; // Status Register
    while (!(*SR & (1 << 1))); // Wait until the conversion is complete

    // Read the ADC value from the injected data register
    uint32_t* JDR4 = (uint32_t*)0x40012020; // Injected Data Register 4
    return *JDR4; // Return the ADC value
}
