# Dual-Axis Solar Tracker Using 8051 and Arduino Nano

A dual-axis solar tracking prototype designed to adjust a small solar panel's orientation according to the direction of maximum light intensity.

## Overview

The system uses four Light Dependent Resistors (LDRs) arranged in a quadrant pattern to compare light intensity from different directions. An Arduino Nano reads the analog LDR signals, and an 8051 microcontroller uses the readings to control two servo motors for horizontal and vertical movement.

## System Architecture

**LDR sensor array → Arduino Nano (analog readings) → UART serial link → 8051 controller → Two servo motors**

## Key Hardware

- Nuvoton W78E052DDG 8051 development board
- Arduino Nano for analog sensor acquisition
- Four LDR sensors
- Two SG90 servo motors
- LDR voltage-divider resistors
- Breadboard, jumper wires, and a suitable regulated servo supply

## How It Works

1. Four LDRs measure light intensity from different directions.
2. The Arduino Nano reads the four analog sensor values.
3. The readings are sent to the 8051 controller over UART.
4. The 8051 compares the left/right and top/bottom sensor groups.
5. The controller adjusts the appropriate servo when the difference exceeds a threshold.
6. The process repeats to track the brighter direction.

## Repository Structure

- `Arduino_Code/` — LDR acquisition sketch
- `8051_Code/` — 8051 tracking firmware
- `docs/` — Wiring diagrams, system architecture, and tracking algorithm documentation

## Getting Started

Review the wiring notes, upload the Arduino sketch, build the 8051 firmware with a compatible toolchain, and verify sensor readings and servo movement before connecting the panel mechanism. Confirm board pinouts, clock settings, UART configuration, and servo power requirements first.

## Testing and Future Work

Record actual sensor readings, servo response, calibration settings, and prototype photos. Future improvements include sensor filtering, live monitoring, and comparison against a fixed panel using measured output data.

## Credits

Add project team members, individual contributions, and third-party references before publication.
