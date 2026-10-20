# Wiring and Connections

The dual-axis solar tracker consists of four LDR sensors, an Arduino Nano, an 8051 microcontroller, and two servo motors. Each component has a specific role in sensing light and adjusting the panel's position.

## LDR Sensor Connections

The four LDR sensors are connected to the Arduino Nano's analog input pins through voltage-divider circuits.

- Top-left LDR: A0
- Top-right LDR: A1
- Bottom-left LDR: A2
- Bottom-right LDR: A3

## Arduino Nano to 8051

The Arduino Nano reads the LDR values and sends them to the 8051 through serial communication.

- Arduino Nano TX (D1) connects to 8051 P3.0/RXD.
- Arduino Nano GND connects to 8051 GND.

Both boards must share a common ground for reliable communication.

## Servo Motor Connections

The two servo motors are controlled by the 8051.

- Vertical servo signal: P2.0
- Horizontal servo signal: P2.1

The servos should use a suitable regulated power supply capable of handling their current requirements. Connect the servo supply ground to the controller ground.

## Important Notes

Check the pin labels on the actual development boards before making connections. Confirm the power requirements and signal connections before switching on the circuit.
