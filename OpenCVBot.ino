#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3);  // RX, TX

// Initialize global variables
String inputString = "";
unsigned short x, y, area;
unsigned short strLength;

// Configure motor pin
const int pwmMotorA = 11;
const int pwmMotorB = 10;
const int leftMotorA = 9;
const int leftMotorB = 8;
const int rightMotorA = 7;
const int rightMotorB = 6;

// Adjust motor speed
const int motorSpeed = 140;

void setup() {

  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  Serial.println("OpenCV Bot V1.0");

  // Set the baud rate of (HC-05) Bluetooth module
  mySerial.begin(38400);
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);

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
  register byte idx = 0;
  char buffer[50];

  if (mySerial.available() > 0) {
    delay(10);
    while (mySerial.available() && idx < 50) {
      buffer[idx++] = mySerial.read();
    }

    buffer[idx] = '\0';
    inputString = (char*)buffer;
    strLength = inputString.length();
    // Serial.println(inputString);

    if (inputString.substring(0, 1).equals("X")) {
      uint8_t pos, i = 1;

      while (inputString.substring(i, i + 1) != ("Y")) {
        i++;
      }

      x = inputString.substring(1, i).toInt();
      // Serial.print("X: ");
      // Serial.println(x);

      pos = i + 1;
      while (inputString.substring(i, i + 1) != ("A")) {
        i++;
      }

      y = inputString.substring(pos, i).toInt();
      // Serial.print("Y: ");
      // Serial.println(y);

      area = inputString.substring(i + 1, strLength).toInt();
      // Serial.print("Area: ");
      // Serial.println(area);

      if (x < 750) {
        Serial.println("Left");
        goLeft();
      }
      if (x > 1100) {
        Serial.println("Right");
        goRight();
      }
      if (x >= 750 && x <= 1100) {
        if (area < 150) {
          Serial.println("Forward");
          goForward();
        }
        if (area >= 150 && area <= 250) {
          Serial.println("Stop");
          stop();
        }
        if (area > 250) {
          Serial.println("Back");
          goBack();
        }
      }
    }
  }

  // all data has been sent, and the buffer is empty.
  Serial.flush();
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
