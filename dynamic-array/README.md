# Dynamic Array in C

A small dynamic array implementation written in C as a learning project.

The goal was to understand how dynamic memory management works in C and how a simple data structure can be built from scratch using `malloc`, `realloc`, and `free`.

## Features

* Dynamic allocation with `malloc`
* Automatic resizing with `realloc`
* Adding elements
* Getting elements by index
* Removing elements
* Bounds checking
* Memory cleanup
* Separation of interface and implementation using `.h` and `.c` files

## Project Structure

```text
dynamic-array/
├── array.h
├── array.c
├── main.c
└── build/
    └── dynamic_array.exe
```

* `array.h` — Array structure and function declarations
* `array.c` — Dynamic array implementation
* `main.c` — Test program demonstrating the functionality

## Building

Compile with GCC:

```bash
gcc main.c array.c -o build/dynamic_array.exe -Wall -Wextra -Wpedantic
```

Run:

```bash
./build/dynamic_array.exe
```

## What I Learned

This project helped me practice:

* Pointers and pointer arithmetic
* Structures and pointers to structures
* Dynamic memory allocation
* `malloc`, `realloc`, and `free`
* Handling allocation failures
* Array indexing
* Header files and include guards
* Separating an interface from its implementation
* Basic error handling in C
* Compilation and linking of multiple source files

## Notes

The array currently stores `int` values and grows its capacity by 10 elements whenever it becomes full.

This is intentionally a small learning project rather than a complete general-purpose dynamic array library.

