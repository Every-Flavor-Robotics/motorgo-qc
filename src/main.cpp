// This is a QC testing script to confirm that the I/O is working as expected
// It will do the following:
// 1. Set up the motor driver for both channels
// 2. Run the motors in both directions in open loop mode while printing the
// current velocities
// 3. Blink the onboard LED
// 4. Test all GPIO by toggling them on and off
// This QC test skips over calibration

#include <Arduino.h>

#include "motorgo_mini.h"

// MotorGo setup
MotorGo::MotorGoMini motorgo;
MotorGo::MotorChannel& motor1 = motorgo.ch0;
MotorGo::MotorChannel& motor2 = motorgo.ch1;

MotorGo::MotorParameters ptz_params;

// Create an array of pins to test
const int num_pins = 9;
int test_pins[] = {LED_BUILTIN, 47, 38, 39, 40, 41, 42, 43, 44};

// Helper function to print at a maximum frequency
void freq_println(String str, int freq)
{
  static unsigned long last_print_time = 0;
  unsigned long now = millis();

  if (now - last_print_time > 1000 / freq)
  {
    Serial.println(str);
    last_print_time = now;
  }
}

void setup()
{
  Serial.begin(115200);

  delay(3000);
  Serial.println("Starting MotorGo Mini QC Test");

  //   Setup pins to test
  for (int i = 0; i < num_pins; i++)
  {
    pinMode(test_pins[i], OUTPUT);
  }

  // Configure motor parameters
  ptz_params.power_supply_voltage = 5;
  ptz_params.calibration_voltage = 1.0;
  ptz_params.pole_pairs = 7;
  ptz_params.current_limit = 1000;
  ptz_params.velocity_limit = 1000;

  // MotorGo setup
  motor1.init(ptz_params, false);
  motor2.init(ptz_params, false);

  motor1.set_control_mode(MotorGo::ControlMode::VelocityOpenLoop);
  motor2.set_control_mode(MotorGo::ControlMode::VelocityOpenLoop);

  motor1.enable();
  motor2.enable();
}

long last_time_pin_change = 0;
long last_motor_direction_change = 0;
int motor_direction = 1;
int cur_pin = 0;
void loop()
{
  // Update controls
  motor1.loop();
  motor2.loop();

  // Every 100 ms, change the pins to test
  if (millis() - last_time_pin_change > 100)
  {
    // Set the current pin to low
    digitalWrite(test_pins[cur_pin], LOW);

    // Update the current pin
    cur_pin = (cur_pin + 1) % num_pins;
    digitalWrite(test_pins[cur_pin], HIGH);

    last_time_pin_change = millis();
  }

  // Change motor_direction every second
  if (millis() - last_motor_direction_change > 1000)
  {
    motor_direction *= -1;
    motor1.set_target_velocity(5 * motor_direction);
    motor2.set_target_velocity(5 * motor_direction);
    last_motor_direction_change = millis();
  }

  //   Print measured velocities
  freq_println("Motor 1: " + String(motor1.get_velocity()) +
                   "Motor 2: " + String(motor2.get_velocity()),
               10);
}
