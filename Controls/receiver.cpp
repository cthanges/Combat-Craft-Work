#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// Define CE and CSN pins
#define CE_PIN 25
#define CSN_PIN 26

RF24 radio(CE_PIN, CSN_PIN); // Create RF24 object

// Address for communication
const byte address[6] = "00001";

// Commands
enum Commands { STOP = 0, FORWARD, BACKWARD, LEFT, RIGHT };
Commands command;

// Motor control pins
#define MOTOR_LEFT_FORWARD 33
#define MOTOR_LEFT_BACKWARD 32
#define MOTOR_RIGHT_FORWARD 35
#define MOTOR_RIGHT_BACKWARD 34

void setup() {
  Serial.begin(115200);

  // Initialize motor pins
  pinMode(MOTOR_LEFT_FORWARD, OUTPUT);
  pinMode(MOTOR_LEFT_BACKWARD, OUTPUT);
  pinMode(MOTOR_RIGHT_FORWARD, OUTPUT);
  pinMode(MOTOR_RIGHT_BACKWARD, OUTPUT);

  // Initialize nRF24L01
  if (!radio.begin()) {
    Serial.println("nRF24L01 Initialization Failed!");
    while (1);
  }
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_LOW);
  radio.startListening();
  Serial.println("Robot Ready!");
}

void loop() {
  // Check for incoming data
  if (radio.available()) {
    radio.read(&command, sizeof(command));
    Serial.print("Received command: ");
    Serial.println(command);

    // Control motors based on the command
    switch (command) {
      case FORWARD:
        moveForward();
        break;
      case BACKWARD:
        moveBackward();
        break;
      case LEFT:
        turnLeft();
        break;
      case RIGHT:
        turnRight();
        break;
      default:
        stopMotors();
        break;
    }
  }
}

// Movement and Motor controls
void moveForward() {
  digitalWrite(MOTOR_LEFT_FORWARD, HIGH);
  digitalWrite(MOTOR_LEFT_BACKWARD, LOW);
  digitalWrite(MOTOR_RIGHT_FORWARD, HIGH);
  digitalWrite(MOTOR_RIGHT_BACKWARD, LOW);
}

void moveBackward() {
  digitalWrite(MOTOR_LEFT_FORWARD, LOW);
  digitalWrite(MOTOR_LEFT_BACKWARD, HIGH);
  digitalWrite(MOTOR_RIGHT_FORWARD, LOW);
  digitalWrite(MOTOR_RIGHT_BACKWARD, HIGH);
}

void turnLeft() {
  digitalWrite(MOTOR_LEFT_FORWARD, LOW);
  digitalWrite(MOTOR_LEFT_BACKWARD, LOW);
  digitalWrite(MOTOR_RIGHT_FORWARD, HIGH);
  digitalWrite(MOTOR_RIGHT_BACKWARD, LOW);
}

void turnRight() {
  digitalWrite(MOTOR_LEFT_FORWARD, HIGH);
  digitalWrite(MOTOR_LEFT_BACKWARD, LOW);
  digitalWrite(MOTOR_RIGHT_FORWARD, LOW);
  digitalWrite(MOTOR_RIGHT_BACKWARD, LOW);
}

void stopMotors() {
  digitalWrite(MOTOR_LEFT_FORWARD, LOW);
  digitalWrite(MOTOR_LEFT_BACKWARD, LOW);
  digitalWrite(MOTOR_RIGHT_FORWARD, LOW);
  digitalWrite(MOTOR_RIGHT_BACKWARD, LOW);
}
