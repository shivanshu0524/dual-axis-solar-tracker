# Dual-Axis Solar Tracker (8051 + Arduino Nano)

> **Project status:** Reconstructed implementation / proposed baseline. This repository was prepared after the original source files were unavailable. It is not a recovered copy of the original firmware. Verify the wiring and test the hardware before describing it as a completed build.

## Overview

This project is designed to orient a small solar panel toward the brighter part of the sky using four LDR sensors and two hobby servo motors.

- **Main controller:** Nuvoton W78E052DDG (8051-compatible MCU development kit)
- **Sensor/ADC helper:** Arduino Nano
- **Sensors:** 4 LDRs in a quadrant arrangement
- **Actuators:** 2 SG90 servos
- **Communication:** 9600-baud UART, Nano TX -> 8051 RX
- **Tracking method:** Compare summed left/right and top/bottom LDR readings, then move the corresponding servo within configured angle limits.

## Repository contents

- `Arduino_Code/ldr_sensor_reading.ino` — reads A0-A3 and sends one CSV line over UART.
- `8051_Code/solar_tracker_8051.c` — Keil C51-style firmware for UART parsing, tracking decisions, and software servo pulses.
- `docs/WIRING.md` — proposed wiring and electrical notes.
- `docs/ALGORITHM.md` — control logic and assumptions.
- `docs/TEST_PLAN.md` — commissioning and validation checklist.
- `docs/BILL_OF_MATERIALS.md` — parts list.
- `LICENSE` — MIT license template; confirm you have the right to license all included work before publishing.

## Important implementation assumptions

1. The Arduino Nano and 8051 board operate at compatible 5 V logic levels.
2. Both boards share a common ground.
3. The Nano transmits sensor values as `A0,A1,A2,A3\\n` at 9600 baud.
4. The 8051 board's UART RX pin is available at P3.0/RXD.
5. P2.0 and P2.1 are available for servo control.
6. Servo power is supplied from a suitable regulated 5 V source, not directly from a weak MCU board regulator.
7. The reconstructed firmware's timer settings assume a classic 8051 machine-cycle timing model with an approximately 11.0592 MHz crystal. Check the actual board clock and timer configuration before use.

If any assumption is false for your hardware, change the wiring/code before powering the circuit.

## Build and test

### Arduino Nano
1. Open `Arduino_Code/ldr_sensor_reading.ino` in Arduino IDE.
2. Select the correct Nano board and port.
3. Upload the sketch.
4. Open Serial Monitor at 9600 baud. You should see four comma-separated values once every 100 ms.

### 8051
1. Open `8051_Code/solar_tracker_8051.c` in Keil µVision with the correct 8051 device selected.
2. Confirm the crystal frequency and timer behaviour for your exact board.
3. Build the project and program the MCU using your available programming setup.
4. Connect Nano TX to 8051 P3.0/RXD, and connect grounds together.
5. Connect the servo signal wires to P2.0 and P2.1. Power the servos from an adequate external 5 V supply with a shared ground.
6. Test with the servos mechanically disconnected from the panel first.

## Calibration

- Cover one LDR at a time and confirm the expected direction of movement.
- Adjust `DEADBAND` in the 8051 source if the servos jitter or respond too slowly.
- Adjust `SERVO_MIN_TICKS`, `SERVO_MAX_TICKS`, and the initial pulse values after verifying the servo's safe travel range.
- The default software limits are intended to be conservative, but servo mechanics vary.

## Results

Do not add performance claims, energy-yield improvements, or test measurements until you have measured and recorded them on the actual prototype. Add your own photos, serial logs, test table, and measured results here after validation.

## Attribution and publication

Describe this as a reconstructed implementation if you use this baseline. Credit collaborators and third-party libraries as appropriate. Do not publish private credentials, personal data, or research-paper material that you do not have permission to release.
