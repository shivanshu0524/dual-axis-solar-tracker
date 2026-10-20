# Testing and Validation

The dual-axis solar tracker should be checked to ensure that the LDR sensors, controller, serial communication, and servo motors work together correctly.

## Testing Procedure

1. **LDR Sensors:** Check whether all four sensors respond to changes in light intensity.
2. **Arduino Nano:** Verify that the sensor readings are collected correctly.
3. **Serial Communication:** Check whether the sensor data reaches the 8051 microcontroller.
4. **Servo Motors:** Verify that both servos move in the intended directions.
5. **Horizontal Tracking:** Change the light intensity on the left and right sides and observe the panel's response.
6. **Vertical Tracking:** Change the light intensity on the top and bottom sides and observe the panel's response.
7. **Overall Operation:** Observe whether the tracker adjusts its position as the direction of light changes.

## Observations

Record the actual observations from your prototype, including any sensor calibration, servo direction adjustments, or issues encountered during testing.

## Conclusion

These checks help verify that the sensor readings, controller logic, and servo movements work together as intended. The final assessment should be based on the behaviour observed during actual hardware testing.
