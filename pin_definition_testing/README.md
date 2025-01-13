# MotorGo Pin Definition Testing

Testing procedure to confirm that the pin definitions for the MotorGo boards are correct. This should be run every time a new board is added to the arduino-esp32 framework.


## Testing Checklist

Copy this checklist into the PR description for adding new board, do not merge until all items are checked off.

- [ ] Install the new board definitions
- [ ] Run the main program in this repository to check I2C, LED, and servo pins
- [ ] Run the example `spin_motors` example from the driver to verify that motors and encoders work as expected
- [ ] Connect the Pihat compatible boards to a Pi and try communicating over SPI with the Pi
- [ ] Confirm the voltage and current limits for the drivers is correct
- [ ] Confirm that all motor driver pins are set low on boot

## Testing
This codebase is written to work for all MotorGo boards, you simply have to change the board that it is compiled for. It will test:
* I2C communication, on the hidden and exposed I2C pins
* QWIIC_SDA and QWIIC_SCL are mapped to the same pins as SDAs and SCL
* Builtin LED and Status LED pins are correct
* BUILTIN_LED == LED_BUILTIN and LED_STATUS == STATUS_LED

Any new tests, that work across all of the boards and do not require additional hardware/software, should be added to this repository.