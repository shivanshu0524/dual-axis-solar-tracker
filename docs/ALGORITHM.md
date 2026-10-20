# Tracking Algorithm

The dual-axis solar tracker uses four Light Dependent Resistors (LDRs) to sense light coming from different directions. The Arduino Nano reads the sensor values and sends them to the 8051 microcontroller through serial communication.

The four LDRs are arranged in pairs to compare the light intensity on the left, right, top, and bottom sides. The 8051 processes these readings and determines which direction receives more light.

If the left side receives more light than the right, the horizontal servo adjusts the panel's position. Similarly, if the top side receives more light than the bottom, the vertical servo moves to improve alignment. The movement direction depends on the sensor wiring and the mechanical arrangement of the tracker.

A predefined threshold is used to avoid unnecessary servo movements when the difference between sensor readings is small. This helps reduce continuous movement caused by minor changes in light intensity.

The process repeats continuously as the light conditions change, allowing the panel to adjust its horizontal and vertical positions toward the brighter direction.
