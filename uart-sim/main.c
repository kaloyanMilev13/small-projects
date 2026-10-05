#include <complex.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>
#define UART_FRAME_BITS 10


typedef enum{
       
	UART_TX_IDLE,
	UART_TX_START,
	UART_TX_DATA,
	UART_TX_STOP

} UARTTxState;

typedef enum{

	UART_RX_IDLE,
	UART_RX_DATA,
	UART_RX_STOP

} UARTRxState;

typedef struct{

	uint32_t baud_rate;

	//TX
	UARTTxState tx_state;
	uint8_t tx_byte;
	uint8_t tx_bit_index;


	//RX
	UARTRxState rx_state;
	uint8_t rx_byte;
	uint8_t rx_bit_index;

	uint8_t rx_ready;
	uint8_t rx_framing_error;

} UART;

typedef struct{
       
	uint8_t bits[UART_FRAME_BITS];

} UARTFrame;

typedef enum{

	UART_OK,
	UART_ERROR_START_BIT,
	UART_ERROR_STOP_BIT

} UARTStatus;


void uart_init(UART *uart, uint32_t baud){

	uart->baud_rate = baud;

	uart->tx_state = UART_TX_IDLE;
	uart->tx_bit_index = 0;
	uart->tx_byte = 0x00;

}

double uart_bit_period_us(uint32_t baud_rate){

	return (double)(1 / (double)(baud_rate)) * pow(10, 6);

}


void encode(uint8_t byte, UARTFrame *frame){


	for(int i = 1; i <= 8; i++){

		frame->bits[i] = ((byte & (1 << (i - 1))) >> (i - 1));

	}

	frame->bits[0] = 0;
	frame->bits[9] = 1;


}


UARTStatus decode(UARTFrame *frame, uint8_t *byte){

	if(frame->bits[0] != 0)
		return UART_ERROR_START_BIT;

	if(frame->bits[9] != 1)
		return UART_ERROR_STOP_BIT;


	*byte = 0;

	for(int i = 1; i <= 8; i++){

		*byte |= frame->bits[i] << (i-1);
		
	}

	return UART_OK;

}


int uart_tx_busy(UART *uart){


	if(uart->tx_state == UART_TX_IDLE)
		return 0;

	return 1;

}


int uart_tx_start(UART *uart, uint8_t byte){

	if(uart_tx_busy(uart) == 0){

		uart->tx_byte = byte;

		uart->tx_bit_index = 0;

		uart->tx_state = UART_TX_START;

		return 1;

	}


	return 0;


}


uint8_t uart_tx_tick(UART *uart){
	
	uint8_t output = 1;

	if(uart->tx_state == UART_TX_IDLE)
		return 1;

	
	if(uart->tx_state == UART_TX_START){

		uart->tx_state = UART_TX_DATA;
		return 0;

	}

	if(uart->tx_state == UART_TX_DATA){

		if(uart->tx_bit_index < 7){

			output = ((uart->tx_byte & (1 << uart->tx_bit_index)) >> uart->tx_bit_index);
			uart->tx_bit_index++;
			return output;	

		}else if (uart->tx_bit_index == 7) {

			output = ((uart->tx_byte & (1 << uart->tx_bit_index)) >> uart->tx_bit_index);
			uart->tx_bit_index++;
			uart->tx_state = UART_TX_STOP;
			return output;

		}

			

	}

	if(uart->tx_state == UART_TX_STOP){

		uart->tx_state = UART_TX_IDLE;
		return 1;

	}

	return output;
}

int main(void){
	UART uart;

	uart_init(&uart, 9600);

	uart_tx_start(&uart, 0x55);

	while (uart_tx_busy(&uart) != 0) {

		uint8_t wire = uart_tx_tick(&uart);

		printf("%u ", wire);
	}

	printf("\n");

	return 0;
}
