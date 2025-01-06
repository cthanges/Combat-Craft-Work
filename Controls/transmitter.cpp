#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// Define CE and CSN pins
#define CE_PIN 25
#define CSN_PIN 26

RF24 radio(CE_PIN, CSN_PIN); // Create RF24 object

// Address for communication
const byte address[6] = "00001";

enum Commands { STOP = 0, FORWARD, BACKWARD, LEFT, RIGHT };
Commands command;

// Joystick/button pins
#define UP_BUTTON 33
#define DOWN_BUTTON 32
#define LEFT_BUTTON 35
#define RIGHT_BUTTON 34

void setup() {
  Serial.begin(115200);

  // Initialize buttons
  pinMode(UP_BUTTON, INPUT_PULLUP);
  pinMode(DOWN_BUTTON, INPUT_PULLUP);
  pinMode(LEFT_BUTTON, INPUT_PULLUP);
  pinMode(RIGHT_BUTTON, INPUT_PULLUP);

  // Initialize nRF24L01
  if (!radio.begin()) {
    Serial.println("Transceiver Initialization Failed!");
    while (1);
  }
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_LOW);
  radio.stopListening();
  Serial.println("Remote Control Ready!");
}

void loop() {
  // Check button states
  if (digitalRead(UP_BUTTON) == LOW) {
    command = FORWARD;
  } else if (digitalRead(DOWN_BUTTON) == LOW) {
    command = BACKWARD;
  } else if (digitalRead(LEFT_BUTTON) == LOW) {
    command = LEFT;
  } else if (digitalRead(RIGHT_BUTTON) == LOW) {
    command = RIGHT;
  } else {
    command = STOP;
  }

  // Send command to robot
  bool success = radio.write(&command, sizeof(command));
  if (success) {
    Serial.println("Success!");
  } else {
    Serial.println("Failed!");
  }

  delay(100);
}
