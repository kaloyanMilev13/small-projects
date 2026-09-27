typedef struct{
       
	unsigned char MODER; //mode reg
	unsigned char ODR; //output data reg
	unsigned char IDR; //input data reg

} GPIO; //8 bits


typedef enum {
     
	GPIO_INPUT,
	GPIO_OUTPUT      

} GPIO_Mode;

typedef enum {
       
	LOW,
	HIGH

} GPIO_State;


void gpio_init(GPIO *gpio);
void gpio_setMode(GPIO *gpio, int pin, GPIO_Mode mode);
void gpio_write(GPIO *gpio, int pin, GPIO_State state);


int main(void){

	GPIO gpio;

	gpio_init(&gpio);

	gpio_setMode(&gpio, 3, GPIO_INPUT);
	gpio_setMode(&gpio, 4, GPIO_OUTPUT);

	return 0;
}





void gpio_init(GPIO *gpio){


	gpio->MODER = 0b00000000;
	gpio->IDR = 0b00000000;
	gpio->ODR = 0b00000000;

}


void gpio_setMode(GPIO *gpio, int pin, GPIO_Mode mode){

	if(mode == GPIO_INPUT)
		gpio->MODER |= (1 << pin);

	else if(mode == GPIO_OUTPUT)
		gpio->MODER &= ~(1 << pin);



}

void gpio_write(GPIO *gpio, int pin, GPIO_State state){




}


