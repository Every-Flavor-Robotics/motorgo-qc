

#include <Arduino.h>
#include <Wire.h>

// Define alternate TwoWire instances for different buses (e.g., QWIIC, HIDDEN)
TwoWire QwiicWire(0);   // Instance for QWIIC bus
TwoWire HiddenWire(1);  // Instance for HIDDEN bus

void scan_i2c_devices(TwoWire &i2c, uint8_t sda, uint8_t scl);

void setup()
{
  Serial.begin(9600);

  // Wait for serial port to connect
  while (!Serial);

  Serial.println("\n\n===== I2C testing =====\n");
  Serial.println("-------------------------");

  //   Confirm that the QWIIC_SDA/QWIIC_SCL == SDA/SCL
  if (QWIIC_SDA != SDA || QWIIC_SCL != SCL)
  {
    Serial.println("Error: QWIIC_SDA/QWIIC_SCL != SDA/SCL");
    Serial.println("Please check the wiring and try again.");
    while (true);
  }
  else
  {
    Serial.println("QWIIC_SDA/QWIIC_SCL == SDA/SCL, test passed!");
  }
  Serial.println("-------------------------\n");
  Serial.println("-------------------------");

  Serial.println(
      "Testing the QWIIC I2C bus (SDA/SCL). You should see the addresses of "
      "any devices connected to the QWIIC bus.");
  Serial.println("Pins: SDA: " + String(SDA) + " SCL: " + String(SCL));
  scan_i2c_devices(Wire, SDA, SCL);
  Serial.println("-------------------------\n");

  Serial.println("-------------------------");
  Serial.println(
      "\nTesting the internal I2C bus (HIDDEN_SDA/HIDDEN_SCL). You should see "
      "the addresses of any devices on the hidden bus.");
  Serial.println("Pins: HIDDEN_SDA: " + String(HIDDEN_SDA) +
                 " HIDDEN_SCL: " + String(HIDDEN_SCL));
  scan_i2c_devices(HiddenWire, HIDDEN_SDA, HIDDEN_SCL);
  Serial.println("-------------------------\n");

  Serial.println("===== I2C testing complete =====");

  Serial.println("\n\n===== LED testing =====\n");

  Serial.println("-------------------------");
  //   Confirm LED_BUILTIN, BUILTIN_LED, and LED_STATUS, STATUS_LED are defined
  if (LED_BUILTIN != BUILTIN_LED || LED_STATUS != STATUS_LED)
  {
    Serial.println(
        "Error: LED_BUILTIN, BUILTIN_LED, LED_STATUS, STATUS_LED "
        "not defined");
    while (true);
  }
  else
  {
    Serial.println(
        "LED_BUILTIN, BUILTIN_LED, LED_STATUS, STATUS_LED defined, "
        "test passed!");
  }
  Serial.println("-------------------------\n");

  Serial.println("-------------------------");
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.println("Blinking the built-in LED");
  for (int i = 0; i < 5; i++)
  {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
  }

  Serial.println("-------------------------\n");

  Serial.println("-------------------------");
  //   Repeat for status LED
  pinMode(LED_STATUS, OUTPUT);
  Serial.println("Blinking the status LED");
  for (int i = 0; i < 5; i++)
  {
    digitalWrite(LED_STATUS, HIGH);
    delay(500);
    digitalWrite(LED_STATUS, LOW);
    delay(500);
  }

  Serial.println("-------------------------\n");

  Serial.println("===== LED testing complete =====");

  delay(3000);

  //   Servo testing
  Serial.println("\n\n===== Servo testing =====\n");
  // for SERVO_1_PWM, SERVO_2_PWM, SERVO_3_PWM, SERVO_4_PWM, run the servo sweep
  // test
  Serial.println("-------------------------");
  Serial.println("Testing Servo 1");
//   Servo 1
#if defined(SERVO_1_PWM)
  Servo servo1;
  servo1.attach(SERVO_1_PWM);
  for (int i = 0; i < 180; i++)
  {
    servo1.write(i);
    delay(15);
  }
  for (int i = 180; i > 0; i--)
  {
    servo1.write(i);
    delay(15);
  }
  servo1.detach();
  Serial.println("Servo 1 test complete");
#else
  Serial.println("Servo 1 not defined");
#endif
  Serial.println("-------------------------\n");

  Serial.println("-------------------------");
  Serial.println("Testing Servo 2");
//   Servo 2
#if defined(SERVO_2_PWM)
  Servo servo2;
  servo2.attach(SERVO_2_PWM);
  for (int i = 0; i < 180; i++)
  {
    servo2.write(i);
    delay(15);
  }
  for (int i = 180; i > 0; i--)
  {
    servo2.write(i);
    delay(15);
  }
  servo2.detach();
  Serial.println("Servo 2 test complete");

#else
  Serial.println("Servo 2 not defined");
#endif
  Serial.println("-------------------------\n");

  Serial.println("-------------------------");
  Serial.println("Testing Servo 3");
//   Servo 3
#if defined(SERVO_3_PWM)
  Servo servo3;
  servo3.attach(SERVO_3_PWM);
  for (int i = 0; i < 180; i++)
  {
    servo3.write(i);
    delay(15);
  }
  for (int i = 180; i > 0; i--)
  {
    servo3.write(i);
    delay(15);
  }
  servo3.detach();
  Serial.println("Servo 3 test complete");

#else
  Serial.println("Servo 3 not defined");
#endif
  Serial.println("-------------------------\n");

  Serial.println("-------------------------");
  Serial.println("Testing Servo 4");
//   Servo 4
#if defined(SERVO_4_PWM)
  Servo servo4;
  servo4.attach(SERVO_4_PWM);
  for (int i = 0; i < 180; i++)
  {
    servo4.write(i);
    delay(15);
  }
  for (int i = 180; i > 0; i--)
  {
    servo4.write(i);
    delay(15);
  }
  servo4.detach();
  Serial.println("Servo 4 test complete");

#else
  Serial.println("Servo 4 not defined");
#endif
  Serial.println("-------------------------\n");

  Serial.println("===== Servo testing complete =====");

  delay(3000);
}

void loop()
{
  Serial.println("Testing Complete, reset the board to run again.");
  delay(3000);
}

void scan_i2c_devices(TwoWire &i2c, uint8_t sda, uint8_t scl)
{
  byte error, address;
  int devicesFound = 0;

  Serial.println("Scanning for I2C devices...");

  // Initialize the I2C bus with the specified SDA and SCL pins
  i2c.begin(sda, scl);

  for (address = 1; address < 127; address++)
  {
    i2c.beginTransmission(address);
    error = i2c.endTransmission();

    if (error == 0)
    {
      Serial.print("\t0x");
      if (address < 16) Serial.print("0");
      Serial.println(address, HEX);

      devicesFound++;
    }
    else if (error == 4)
    {
      Serial.print("Unknown error at address 0x");
      if (address < 16) Serial.print("0");
      Serial.println(address, HEX);
    }
  }

  if (devicesFound == 0)
  {
    Serial.println("No I2C devices found.");
  }
  else
  {
    Serial.print(devicesFound);
    Serial.println(" devices found.");
  }

  // End the I2C bus to release resources
  i2c.end();
}
