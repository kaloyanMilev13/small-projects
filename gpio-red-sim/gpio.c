#include "gpio.h"

void gpio_simulateInput(GPIO *gpio, int pin, GPIO_State state){


	if(gpio_checkPin(pin)){

		if(gpio_MODER_readPin(gpio, pin) == 0){//input mode


			if(state == LOW){

				gpio->IDR &= ~(1 << pin);

			}else if (state == HIGH) {

				gpio->IDR |= (1 << pin);

			}	

		}		


	}


}


void gpio_init(GPIO *gpio){

	//set everything to 0
	gpio->MODER = MODEr;
	gpio->IDR = IDRr; 
	gpio->ODR = ODRr;

}

unsigned char gpio_checkPin(int pin){


	if(pin >= 0 && pin < 8)
		return 1;
	else
		return 0;


}


void gpio_MODER_setMode(GPIO *gpio, int pin, GPIO_Mode mode){

	if(gpio_checkPin(pin)){


		if(mode == GPIO_INPUT)
			gpio->MODER &= ~(1 << pin); // 0

		else if(mode == GPIO_OUTPUT)
			gpio->MODER |= (1 << pin); // 1



	}


}

unsigned char gpio_MODER_readPin(GPIO *gpio, int pin){

	if(gpio_checkPin(pin)){

		return ((gpio->MODER & (1 << pin)) >> pin);



	}


	return -1;

}



unsigned char gpio_readPin(GPIO *gpio, int pin){

	if(gpio_checkPin(pin)){

		return ((gpio->IDR & (1 << pin)) >> pin);


	}


	return -1;


}


void gpio_writePin(GPIO *gpio, int pin, GPIO_State state){

	if(gpio_checkPin(pin)){

		if(gpio_MODER_readPin(gpio, pin) == 1){ //then MODER reg for this pin is set as OUTPUT

			if(state == LOW){

				gpio->ODR &= ~(1 << pin);

			}else if (state == HIGH) {

				gpio->ODR |= (1 << pin);

			}	


		}



	}



}




void gpio_togglePin(GPIO *gpio, int pin){

	if(gpio_checkPin(pin)){


		if(gpio_MODER_readPin(gpio, pin)){

			gpio->ODR ^= (1 << pin);

		}
	}


}
