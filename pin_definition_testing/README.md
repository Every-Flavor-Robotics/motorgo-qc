# MotorGo Pin Definition Testing

Testing procedure to confirm that the pin definitions for the MotorGo boards are correct. This should be run every time a new board is added to the arduino-esp32 framework.


## Testing Checklist

- [ ] Install the new board definitions
- [ ] Run the main program in this repository to check I2C, LED, and servo pins
- [ ] Run the example `spin_motors` sketch in the driver code to verify that motors and encoders work as expected
- [ ] Connect the Pihat compatible boards to a Pi and try communicating over SPI with the Pi
- [ ] Confirm the voltage and current limits for the drivers is correct