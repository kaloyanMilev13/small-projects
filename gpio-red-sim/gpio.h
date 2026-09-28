#ifndef GPIO_H
#define GPIO_H

#define MODEr 0b00000000
#define ODRr 0b00000000
#define IDRr 0b00000000


typedef struct{
       
	unsigned char MODER; //mode reg
	unsigned char ODR; //output data reg
	unsigned char IDR; //input data reg

} GPIO; //8 bits


typedef enum {
     
	GPIO_INPUT, //0
	GPIO_OUTPUT // 1     

} GPIO_Mode;

typedef enum {
       
	LOW,
	HIGH

} GPIO_State;


void gpio_init(GPIO *gpio);

unsigned char gpio_checkPin(int pin);

void gpio_MODER_setMode(GPIO *gpio, int pin, GPIO_Mode mode);
unsigned char gpio_MODER_readPin(GPIO *gpio, int pin);

unsigned char gpio_readPin(GPIO *gpio, int pin);
void gpio_writePin(GPIO *gpio, int pin, GPIO_State state);
void gpio_togglePin(GPIO *gpio, int pin);


void gpio_simulateInput(GPIO *gpio, int pin, GPIO_State state);


#endif
