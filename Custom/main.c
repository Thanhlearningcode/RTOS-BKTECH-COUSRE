#include "Encoder.h"
#include "Uart.h"
#include <stdint.h>
extern volatile long pos_left ;
extern volatile long pos_right ;
// direction of motor
extern int Direction_left ;
extern int Direction_right ;

extern const int encoder_minimum ;
extern const int encoder_maximum ;
uint8_t txData[50];
 void readEncoder(void) {
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
int main(){
Exti_Init();
Uart1_Init(115200);
		uint32_t* VTOR = (uint32_t*)0xE000ED08;
    *VTOR = 0x20000000;  
    uint32_t* temp = (uint32_t*)(0x20000000 + 0x58); // Base Vector + offset ngat 9
    *temp = (uint32_t)readEncoder; // Rename Ngat Exti 9
while(1){
	sprintf((char *)txData, "%ld, %ld\n", pos_left, pos_right);
 Uart1_Transmiter(txData, strlen((char *)txData));
}
}
