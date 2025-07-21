# Dual DC Motor Control on ESP32 using Zephyr RTOS

This project demonstrates how to control two DC motors using an ESP32 board running Zephyr RTOS. The motors are controlled via GPIO-based direction logic (no PWM in this version), suitable for use with H-bridge motor drivers like L298N or similar.

##  Features
- Forward, backward, and stop functionality for two motors
- Abstracted functions for cleaner motor control
- DeviceTree-based GPIO pin mapping
- Runs on Zephyr RTOS (tested on ESP32)

##  What It Shows
- GPIO control using Zephyr's `gpio_dt_spec` abstraction
- Safe device initialization with `device_is_ready()` and `gpio_pin_configure_dt()`
- Structured motor control code suitable for modular extension (e.g., PWM, PID later)

##  Hardware Requirements
- ESP32 board 
- L298N Motor Driver (or any compatible H-bridge)
- 2x DC Motors
- External power supply (for motors)
- Wiring:
  - IN1 → D2
  - IN2 → D4
  - IN3 → D18
  - IN4 → D19
