#include <stdint.h>
#include <stdio.h>
#define UART_FRAME_BITS 10


typedef struct{
       
	uint8_t bits[UART_FRAME_BITS];

} UARTFrame;

void encode(uint8_t byte, UARTFrame *frame){


	for(int i = 1; i <= 8; i++){

		frame->bits[i] = ((byte & (1 << (i - 1))) >> (i - 1));
		printf("i = %d\n", i);

	}

	frame->bits[0] = 0;
	frame->bits[9] = 1;


}

int main(void){

	printf("\n");


	UARTFrame frame = {0};

	encode(0x55, &frame);


	for(int i = 0; i < UART_FRAME_BITS; i++){

		printf("Element[%d] = %u\n", i, frame.bits[i]);

	}


	return 0;
}
