#include <SoftwareSerial.h>

#define DEBUG 0  // Enable/Disable Debugging

// Configure motor pin
const unsigned int pwmMotorA = 11;
const unsigned int pwmMotorB = 10;
const unsigned int leftMotorA = 9;
const unsigned int leftMotorB = 8;
const unsigned int rightMotorA = 7;
const unsigned int rightMotorB = 6;

// Adjust motor speed
const unsigned int motorSpeed = 140;

char buffer[64];
const int BUFFER_SIZE = 15;
unsigned short x, y, area;

SoftwareSerial mySerial(2, 3);  // RX, TX

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  Serial.println("OpenCV Bot V1.0");

  // Set the baud rate of (HC-05) Bluetooth module
  mySerial.begin(38400);

  // Setup pins
  pinMode(pwmMotorA, OUTPUT);
  pinMode(pwmMotorB, OUTPUT);
  pinMode(leftMotorA, OUTPUT);
  pinMode(leftMotorB, OUTPUT);
  pinMode(rightMotorA, OUTPUT);
  pinMode(rightMotorB, OUTPUT);

  analogWrite(pwmMotorA, motorSpeed);
  analogWrite(pwmMotorB, motorSpeed);
}

void loop() {
  if (mySerial.available() > 0) {
    // Wait delay to allow all data to arrive
    for (byte i = 0; i < BUFFER_SIZE; i++) delay(1);

    // Read data from the serial buffer
    size_t index = 0;
    while (mySerial.available() && index < BUFFER_SIZE) {
      buffer[index++] = (char)mySerial.read();
    }
    buffer[index] = '\0';

    // Receive Sussessfull
    if (sscanf(buffer, "X%uY%uA%u", &x, &y, &area) != 0) {

      if (DEBUG) {
        Serial.print(F("X: "));
        Serial.print(x);
        Serial.print(F(" | Y: "));
        Serial.print(y);
        Serial.print(F(" | A: "));
        Serial.println(area);
      }

      if (x < 750) {
        Serial.println(F("Left"));
        goLeft();
      } else if (x > 1100) {
        Serial.println(F("Right"));
        goRight();
      } else {
        if (area < 150) {
          Serial.println(F("Forward"));
          goForward();
        } else if (area <= 250) {
          Serial.println(F("Stop"));
          stop();
        } else {
          Serial.println(F("Back"));
          goBack();
        }
      }
    }
  }
}

void goLeft() {
  digitalWrite(leftMotorA, LOW);
  digitalWrite(leftMotorB, HIGH);
  digitalWrite(rightMotorA, HIGH);
  digitalWrite(rightMotorB, LOW);
}

void goRight() {
  digitalWrite(leftMotorA, HIGH);
  digitalWrite(leftMotorB, LOW);
  digitalWrite(rightMotorA, LOW);
  digitalWrite(rightMotorB, HIGH);
}

void goForward() {
  digitalWrite(leftMotorA, HIGH);
  digitalWrite(leftMotorB, LOW);
  digitalWrite(rightMotorA, HIGH);
  digitalWrite(rightMotorB, LOW);
}

void goBack() {
  digitalWrite(leftMotorA, LOW);
  digitalWrite(leftMotorB, HIGH);
  digitalWrite(rightMotorA, LOW);
  digitalWrite(rightMotorB, HIGH);
}

void stop() {
  digitalWrite(leftMotorA, LOW);
  digitalWrite(leftMotorB, LOW);
  digitalWrite(rightMotorA, LOW);
  digitalWrite(rightMotorB, LOW);
}
