# PID Cart

A small inverted-pendulum simulation written in **C** using **raylib**.

The project simulates a cart with a pole attached to it. A PID controller applies a force to the cart in order to keep the pole upright while a second controller moves the cart toward the center of the track.

This project was mainly built as a learning exercise to understand **PID control, physics simulation, numerical integration, and the interaction between a controller and a dynamic system**.

## Features

* Inverted-pendulum physics simulation
* PID controller for pole stabilization
* Position controller for keeping the cart near the center of the track
* Configurable `Kp`, `Ki`, and `Kd` values
* Configurable position-controller gains
* Simulated friction
* Manual cart control using the arrow keys
* Real-time system and PID statistics
* Real-time force, error, acceleration, velocity, and angle display
* Simple raylib visualization

## How it works

The system has two control layers.

### 1. Position controller

The cart has a target position at the center of the track.

The position controller calculates:

```text
position error = target position - cart position
```

and converts this into a desired pole angle:

```text
target angle = Kp_position * position error
             - Kd_position * cart velocity
```

The target angle is limited to prevent the controller from asking the pole to lean too far.

### 2. Pole PID controller

The main PID controller tries to make the actual pole angle follow the target angle.

```text
error = actual angle - target angle

force =
    Kp * error
  + Ki * integral
  + Kd * angular velocity
```

The resulting force is applied to the cart.

The cart and pole are then updated using the simulated dynamics of the inverted pendulum.

## Controls

| Key   | Action                   |
| ----- | ------------------------ |
| `←`   | Apply force to the left  |
| `→`   | Apply force to the right |
| `TAB` | Show/hide statistics     |

## Parameters

The main controller parameters can be changed near the top of `main.c`:

```c
#define KP 35.0f
#define KD 10.0f
#define KI 0.5f

#define KP_POSITION 0.02f
#define KD_POSITION 0.10f

#define MAX_TARGET_ANGLE 0.05f
```

Changing these values changes the behavior of the controller.

For example:

* Increasing `KP` generally makes the controller react more strongly to angular error.
* Increasing `KD` increases the damping response.
* Increasing `KI` causes accumulated error to contribute to the control force.
* The position-controller gains determine how aggressively the cart moves back toward the center.

## Building

### Requirements

* C compiler
* raylib
* math library

On Linux, install raylib using your distribution's package manager or build it from source.

For example, on Arch Linux:

```bash
sudo pacman -S raylib
```

Then compile:

```bash
gcc main.c -o pid-cart -lraylib -lm
```

Run:

```bash
./pid-cart
```

## Project structure

```text
pid-cart/
├── main.c
├── README.md
└── .gitignore
```

## What I learned

This project was built to move beyond simply writing code and understand the relationship between a controller and the physical system it controls.

The main things I worked with were:

* PID control
* Proportional, integral, and derivative terms
* Feedback control
* Angular velocity and acceleration
* Newtonian dynamics
* Numerical integration
* Friction
* Unit conversion between meters and pixels
* Structuring a simulation in C
* Visualizing system state in real time

One of the more difficult parts was not the C syntax itself, but understanding what the equations represented and how changing the controller affected the simulated physical system.

## Limitations

This is a learning simulation rather than a physically accurate inverted-pendulum model.

Some simplifications include:

* Fixed simulation timestep
* Simplified friction model
* Simplified cart/pole dynamics
* No collision or track-boundary response
* No actuator saturation model
* No automatic PID tuning
* Controller parameters are manually selected

The goal of the project was understanding the underlying concepts rather than producing a production-quality physics or control simulation.

## Possible improvements

Some possible future improvements are:

* Add proper track-boundary handling
* Add actuator force limits
* Add configurable simulation timestep
* Add graphs for angle, position, and controller output
* Add PID parameter controls while running
* Add automatic PID tuning
* Separate the physics, controller, and rendering code into modules
* Compare different controller configurations
* Add noise to the sensor measurements
* Add a more realistic motor/actuator model

## Technologies

* **C**
* **raylib**
* **GCC**
* **Git / GitHub**

## Purpose

This repository is part of a collection of small programming and engineering projects built to develop practical experience with C, software development, embedded systems, control systems, and computer engineering.

