// Write a script that will write an ID to the ESP32 persistent memory, using Preferences.h
// 16-bit unsigned integer, 0-65535

#include <Arduino.h>
#include <Preferences.h>

Preferences preferences;

// namespace
const char* ns = "__mg";
// Key
const char* key = "__mg_id";

// ID to write
uint16_t id = 0x03;

// ID read back from memory
uint16_t id_confirm;

uint16_t readID() {
  // Open preferences
  preferences.begin(ns, true);

  // Read the ID
  uint16_t id = preferences.getUShort(key, 0);

  // Close the preferences
  preferences.end();

  return id;
}

void setup() {
  Serial.begin(115200);

    // Open preferences
    preferences.begin(ns, false);

    // Write the ID
    preferences.putUShort(key, id);

    // Close the preferences
    preferences.end();

    delay(1000);

    id_confirm = readID();

    Serial.begin(115200);
}

void loop()
{
    Serial.printf("ID from memory: %d\n", id_confirm);
    delay(1000);
}
