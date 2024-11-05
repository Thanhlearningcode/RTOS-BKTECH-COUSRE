#include "Encoder.h"

volatile long pos_left = 0;
volatile long pos_right = 0;
// direction of motor
int Direction_left = 1;
int Direction_right = 1;

const int encoder_minimum = -32768;
const int encoder_maximum = 32767;
void Exti_Init(void){
	RCC->APB2ENR|=(1U<<14); // System configuration controller clock enable
	
// Configure GPIOC Input
GPIOC->MODER &= ~(3U << 18); // Clear MODER bits for PC9 (input mode)
GPIOC->MODER &= ~(3U << 14); // Clear MODER bits for PC7 (input mode)

// Configure Pull-up resistors for GPIOC
GPIOC->PUPDR |= (1U << 14); // Enable PULL-UP for PC7
GPIOC->PUPDR |= (1U << 18); // Enable PULL-UP for PC9

// Syscfg EXTI Configuration
SYSCFG->EXTICR[1] |= (2U << 12); // Connect PC7 to EXTI7
SYSCFG->EXTICR[2] |= (2U << 4);  // Connect PC9 to EXTI9

// Configure Falling edge trigger for EXTI7 and EXTI9
EXTI->FTSR |= (1U << 7); // Enable falling edge trigger for EXTI7
EXTI->FTSR |= (1U << 9); // Enable falling edge trigger for EXTI9


// Enable interrupt for EXTI7 and EXTI9
EXTI->IMR |= (1U << 7); // Unmask EXTI line 7
EXTI->IMR |= (1U << 9); // Unmask EXTI line 9

EXTI->PR|=(1U<<7);
EXTI->PR|=(1U<<9);
// Enable EXTI interrupt in NVIC
NVIC_EnableIRQ(EXTI9_5_IRQn); // Enable IRQ handler for EXTI lines [9:5]

}	

 void EXTI9_5_IRQHandler(){
 int b1 = readEncoder1 ;
//    	int increment1 = 0;

    	if(b1 == 0){
    		Direction_left = 1;
    	}
    	else if (b1 > 0){
    		Direction_left = 0;
    	}

    	if(Direction_left == 1){
    		if (pos_left == encoder_maximum){
    			pos_left = encoder_minimum;
    		}
    		else{
    			pos_left++;
    		}
    	}
    	else {
    	    if (pos_left == encoder_minimum) {
    	    	pos_left = encoder_maximum;
    	    }
    	    else {
    	    	pos_left--;
    	    }
    	}
 }
void EXTI15_10_IRQHandler(void){
 	int b2 =	readEncoder2;

    	if(b2 == 0){
    		Direction_right = 0;
    	}
    	else if (b2 > 0){
    		Direction_right = 1;
    	}

    	if(Direction_right == 1){
    		if (pos_right == encoder_maximum){
    			pos_right = encoder_minimum;
    		}
    		else{
    			pos_right++;
    		}
    	}
    	else {
    	    if (pos_right == encoder_minimum) {
    	    	pos_right = encoder_maximum;
    	    }
    	    else {
    	    	pos_right--;
    	    }
    	}

    }



