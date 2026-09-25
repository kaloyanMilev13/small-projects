# Spinning Cube

A small 3D graphics experiment written in **C** using **raylib**.

The project renders a rotating cube using manually implemented 3D rotation and perspective projection rather than raylib's built-in 3D rendering system.

## What it does

The program:

1. Defines the eight vertices of a cube in 3D space.
2. Rotates each vertex around the Y axis.
3. Moves the cube away from the camera using a Z offset.
4. Projects the 3D coordinates onto a 2D screen.
5. Connects the projected points to draw the cube.
6. Animates the rotation and projection scale over time.

## 3D Rotation

The cube starts with eight points:

```text
(-1, -1,  1)
( 1, -1,  1)
( 1,  1,  1)
(-1,  1,  1)

(-1, -1, -1)
( 1, -1, -1)
( 1,  1, -1)
(-1,  1, -1)
```

The points are rotated around the Y axis using:

```text
x' = x cos(θ) - z sin(θ)

y' = y

z' = x sin(θ) + z cos(θ)
```

The implementation is contained in `rotatePoints()`.

## Perspective Projection

After rotation, the 3D coordinates are converted into screen coordinates.

The basic projection is:

```text
screenX = centerX + x / z × scale

screenY = centerY - y / z × scale
```

Dividing by `z` causes objects further from the camera to appear smaller, producing a basic perspective effect.

The implementation is contained in `convertPoints()`.

## Animation

The cube rotates by changing the angle every frame.

The projection scale also changes over time:

```c
mult = 170 + sinf(timeFrame * 0.05) * 30;
```

This makes the cube appear to move closer to and further away from the viewer.

## Project Structure

```text
spinning-cube/
├── cube.c
└── 3d_cube_calc.ods
```

`cube.c` contains the C implementation.

`3d_cube_calc.ods` contains calculations used while working through the 3D cube mathematics.

## Building

### Requirements

* C compiler
* raylib
* math library

On Linux with GCC:

```bash
gcc cube.c -o cube -lraylib -lm
```

Run it with:

```bash
./cube
```

## What I Learned

This project was mainly an exercise in understanding how a computer can represent and display a 3D object without relying on a 3D rendering API.

The main concepts explored were:

* 3D coordinate systems
* Rotation around an axis
* Trigonometry
* Perspective projection
* Converting 3D coordinates to 2D screen coordinates
* Working with arrays of points in C
* Separating calculations from rendering
* Using raylib for visualization

## Limitations

This is a basic implementation rather than a complete 3D renderer.

It currently:

* Only rotates around one axis
* Has no depth sorting
* Does not perform face rendering
* Does not perform back-face culling
* Uses a fixed cube size
* Uses a manually implemented projection
* Draws only the cube's edges

The purpose of the project was to understand the underlying mathematics rather than build a complete rendering engine.

