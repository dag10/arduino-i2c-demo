/* I2C Example. */

#include <Wire.h>

// Settings
const int led_pin = 13;
const int master_pin = 7;

// Vars
bool is_master;
byte address = 3;
byte value = 0;

// Prototyptes
void sendToSlave(byte address, int data);
void testSlave(byte address, byte input, byte expected_output);
void runTests(byte address);
void dataHandler(int bytes_read);
void requestHandler();

// Initialization.
void setup() {
  pinMode(master_pin, INPUT);
  is_master = digitalRead(master_pin);

  pinMode(led_pin, OUTPUT);

  if (is_master) {
    Serial.begin(9600);
    Serial.println("Starting.");
    Wire.begin();
    runTests(address);
    Serial.println("Done!");
  } else {
    Wire.begin(address);
    Wire.onReceive(dataHandler);
    Wire.onRequest(requestHandler);
  }
}

// Arduino loop.
void loop() {
  if (is_master) {
    digitalWrite(led_pin, HIGH);
    delay(is_master ? 100 : 300);
    digitalWrite(led_pin, LOW);
    delay(is_master ? 100 : 300);
  }
}

/*
 * Master functions.
 */

// Send a byte to a slave.
void sendToSlave(byte address, byte data) {
  Wire.beginTransmission(address);
  Wire.write(data);
  Wire.endTransmission();
}

// Sends a byte to the given address and tests that the output is correct.
void testSlave(byte address, byte input, byte expected_output) {
  delay(300);

  Serial.print("Sending ");
  Serial.print(input);
  Serial.print(" to slave ");
  Serial.print(address);
  Serial.println(".");
  
  sendToSlave(address, input);
  Wire.requestFrom((int)address, 1, true);

  Serial.println("Waiting for response...");
  while (!Wire.available()) {
    delay(1);
  }

  byte output = Wire.read();
  if (output == expected_output) {
    Serial.print("Output matches expected output (");
    Serial.print(output);
    Serial.println(").");
  } else {
    Serial.print("Output (");
    Serial.print(output);
    Serial.print(") does not match expected output (");
    Serial.print(expected_output);
    Serial.println(").");
  }
}

// Runs tests on a given slave.
void runTests(byte address) {
  testSlave(address, 3, 8);
  testSlave(address, 9, 14);
  testSlave(address, 120, 125);
}

/*
 * Slave functions.
 */

// Called when bytes are received via I2C.
void dataHandler(int bytes_read) {
  // Store the last byte received.
  while (bytes_read-- > 0) {
    value = Wire.read();
  }
}

// Called when bytes are requested via I2C.
void requestHandler() {
  digitalWrite(led_pin, HIGH);
  delay(150);

  // Send the stored value + 5.
  Wire.write(value + 5);

  delay(150);
  digitalWrite(led_pin, LOW);
  delay(100);
}

