# GPIO Register Simulator

A small GPIO register simulator written in C as a learning project.

The goal of this project was to practice bitwise operations and understand how GPIO-style hardware registers can represent pin configuration, input state, and output state.

## Features

- 8 simulated GPIO pins
- Input/output pin configuration using a mode register
- Output HIGH/LOW control
- Output pin toggling
- Simulated external input signals
- Pin validation
- Direction protection for input/output operations
- Binary register display
- Test program covering the GPIO API

## Registers

The simulator uses three 8-bit registers:

- `MODER` — stores whether each pin is configured as input or output
- `ODR` — stores values driven by output pins
- `IDR` — stores values observed on input pins

## Project Structure

```text
gpio-register-simulator/
├── gpio.h
├── gpio.c
└── main.c
```

## Build

```bash
gcc main.c gpio.c -o gpio_sim -Wall -Wextra
```

Run:

```bash
./gpio_sim
```

## What I Learned

This project helped me practice:

- Bitwise AND, OR, XOR, and NOT
- Bit shifting and bit masks
- Setting, clearing, reading, and toggling individual bits
- Structs and enums
- Register-style programming
- GPIO input/output concepts
- Header and source file separation
- Input validation
- Writing a simple test harness

This is intentionally a small learning project rather than a complete hardware emulator.
