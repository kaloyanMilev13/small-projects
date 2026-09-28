#include <stdio.h>
#include "gpio.h"


static int tests_run = 0;
static int tests_failed = 0;

void print_register(const char *name, unsigned char reg)
{
    printf("%-6s: ", name);

    for (int i = 7; i >= 0; i--) {
        printf("%d", (reg >> i) & 1);
    }

    printf("\n");
}


void check(const char *name, int condition)
{
    tests_run++;

    if (condition) {
        printf("[PASS] %s\n", name);
    } else {
        printf("[FAIL] %s\n", name);
        tests_failed++;
    }
}





int main(void)
{
    GPIO gpio;

    printf("=================================\n");
    printf("       GPIO Simulator Tests\n");
    printf("=================================\n\n");

    /*
     * 1. Initialization
     */
    printf("--- Initialization ---\n");

    gpio_init(&gpio);

    print_register("MODER", gpio.MODER);
    print_register("ODR", gpio.ODR);
    print_register("IDR", gpio.IDR);

    check("MODER starts at 00000000",
          gpio.MODER == 0b00000000);

    check("ODR starts at 00000000",
          gpio.ODR == 0b00000000);

    check("IDR starts at 00000000",
          gpio.IDR == 0b00000000);

    printf("\n");


    /*
     * 2. Pin validation
     */
    printf("--- Pin Validation ---\n");

    check("Pin 0 accepted",
          gpio_checkPin(0) == 1);

    check("Pin 7 accepted",
          gpio_checkPin(7) == 1);

    check("Pin -1 rejected",
          gpio_checkPin(-1) == 0);

    check("Pin 8 rejected",
          gpio_checkPin(8) == 0);

    printf("\n");


    /*
     * 3. Configure modes
     *
     * pin 0 -> OUTPUT
     * pin 1 -> INPUT
     * pin 2 -> OUTPUT
     * pin 3 -> INPUT
     */
    printf("--- Pin Modes ---\n");

    gpio_MODER_setMode(&gpio, 0, GPIO_OUTPUT);
    gpio_MODER_setMode(&gpio, 1, GPIO_INPUT);
    gpio_MODER_setMode(&gpio, 2, GPIO_OUTPUT);
    gpio_MODER_setMode(&gpio, 3, GPIO_INPUT);

    print_register("MODER", gpio.MODER);

    check("Pin 0 configured OUTPUT",
          gpio_MODER_readPin(&gpio, 0) == GPIO_OUTPUT);

    check("Pin 1 configured INPUT",
          gpio_MODER_readPin(&gpio, 1) == GPIO_INPUT);

    check("Pin 2 configured OUTPUT",
          gpio_MODER_readPin(&gpio, 2) == GPIO_OUTPUT);

    check("Pin 3 configured INPUT",
          gpio_MODER_readPin(&gpio, 3) == GPIO_INPUT);

    check("MODER equals 00000101",
          gpio.MODER == 0b00000101);

    printf("\n");


    /*
     * 4. Simulated input
     */
    printf("--- Input Simulation ---\n");

    gpio_simulateInput(&gpio, 1, HIGH);

    check("Input pin 1 receives HIGH",
          gpio_readPin(&gpio, 1) == HIGH);

    gpio_simulateInput(&gpio, 3, HIGH);

    check("Input pin 3 receives HIGH",
          gpio_readPin(&gpio, 3) == HIGH);

    check("IDR equals 00001010",
          gpio.IDR == 0b00001010);

    print_register("IDR", gpio.IDR);


    gpio_simulateInput(&gpio, 1, LOW);

    check("Input pin 1 changes to LOW",
          gpio_readPin(&gpio, 1) == LOW);

    check("IDR equals 00001000",
          gpio.IDR == 0b00001000);

    printf("\n");


    /*
     * 5. Input simulation must not modify output pins
     */
    printf("--- Input Direction Protection ---\n");

    unsigned char old_idr = gpio.IDR;

    gpio_simulateInput(&gpio, 0, HIGH);

    check("Cannot simulate input on OUTPUT pin 0",
          gpio.IDR == old_idr);

    printf("\n");


    /*
     * 6. Output writing
     */
    printf("--- Output Writing ---\n");

    gpio_writePin(&gpio, 0, HIGH);

    check("Output pin 0 written HIGH",
          ((gpio.ODR >> 0) & 1) == HIGH);

    gpio_writePin(&gpio, 2, HIGH);

    check("Output pin 2 written HIGH",
          ((gpio.ODR >> 2) & 1) == HIGH);

    check("ODR equals 00000101",
          gpio.ODR == 0b00000101);

    print_register("ODR", gpio.ODR);


    gpio_writePin(&gpio, 0, LOW);

    check("Output pin 0 written LOW",
          ((gpio.ODR >> 0) & 1) == LOW);

    check("ODR equals 00000100",
          gpio.ODR == 0b00000100);

    printf("\n");


    /*
     * 7. Output write must not modify input pins
     */
    printf("--- Output Direction Protection ---\n");

    unsigned char old_odr = gpio.ODR;

    gpio_writePin(&gpio, 1, HIGH);

    check("Cannot write to INPUT pin 1",
          gpio.ODR == old_odr);

    printf("\n");


    /*
     * 8. Toggle output
     */
    printf("--- Toggle ---\n");

    gpio_togglePin(&gpio, 2);

    check("Pin 2 toggles HIGH -> LOW",
          ((gpio.ODR >> 2) & 1) == LOW);

    gpio_togglePin(&gpio, 2);

    check("Pin 2 toggles LOW -> HIGH",
          ((gpio.ODR >> 2) & 1) == HIGH);

    print_register("ODR", gpio.ODR);

    printf("\n");


    /*
     * 9. Toggle must not modify input pins
     */
    printf("--- Toggle Direction Protection ---\n");

    old_odr = gpio.ODR;

    gpio_togglePin(&gpio, 1);

    check("Cannot toggle INPUT pin 1",
          gpio.ODR == old_odr);

    printf("\n");


    /*
     * 10. Invalid operations
     */
    printf("--- Invalid Pin Operations ---\n");

    unsigned char old_moder = gpio.MODER;
    old_odr = gpio.ODR;
    old_idr = gpio.IDR;

    gpio_MODER_setMode(&gpio, -1, GPIO_OUTPUT);
    gpio_MODER_setMode(&gpio, 8, GPIO_OUTPUT);

    gpio_writePin(&gpio, -1, HIGH);
    gpio_writePin(&gpio, 8, HIGH);

    gpio_togglePin(&gpio, -1);
    gpio_togglePin(&gpio, 8);

    gpio_simulateInput(&gpio, -1, HIGH);
    gpio_simulateInput(&gpio, 8, HIGH);

    check("Invalid pins do not change MODER",
          gpio.MODER == old_moder);

    check("Invalid pins do not change ODR",
          gpio.ODR == old_odr);

    check("Invalid pins do not change IDR",
          gpio.IDR == old_idr);

    printf("\n");


    /*
     * Final state
     */
    printf("--- Final Registers ---\n");

    print_register("MODER", gpio.MODER);
    print_register("ODR", gpio.ODR);
    print_register("IDR", gpio.IDR);

    printf("\n=================================\n");
    printf("Tests run:    %d\n", tests_run);
    printf("Tests passed: %d\n", tests_run - tests_failed);
    printf("Tests failed: %d\n", tests_failed);
    printf("=================================\n");

    return tests_failed == 0 ? 0 : 1;
}

