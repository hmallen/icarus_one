/*
   Servo driver for in-flight photo shoot

   Test Values:
   - Servo MIN = ~20
   - Servo MAX = ~160

   Positions:
   - Retracted = 20
   - Deployed = 100
*/

#include <Servo.h>

const bool debugMode = true;

const int controlInput = 2;
const int servoPin = 3;

int servoPosRetract = 20;
int servoPosDeploy = 100; // Need to test to obtain proper value

Servo camServo;

void setup() {
  pinMode(controlInput, INPUT_PULLUP);
  camServo.attach(servoPin);

  Serial.begin(9600);

  int servoPosition = camServo.read();
  if (debugMode) {
    Serial.print("Servo position: ");
    Serial.println(servoPosition);
    Serial.print("Moving servo to start position...");
  }

  if (servoPosition > servoPosRetract) {
    for (int x = servoPosition; x >= servoPosRetract; x--) {
      camServo.write(x);
      delay(25);
    }
  }
  else if (servoPosition < servoPosRetract) {
    for (int x = servoPosition; x <= servoPosRetract; x++) {
      camServo.write(x);
      delay(25);
    }
  }
  servoPosition = camServo.read();
  if (debugMode) {
    Serial.println("complete.");
    Serial.print("Servo position: ");
    Serial.println(servoPosition);
  }

  for (int x = 20; x <= servoPosDeploy; x++) {
    camServo.write(x);
    delay(25);
  }

  while (true) {
    ;
  }
} 

void loop() {
  delay(100);
  if (digitalRead(controlInput) == LOW) {
    if (debugMode) Serial.print("Positioning photo...");
    positionPhoto();
  }
}

void positionPhoto() {
  for (int x =  servoPosRetract; x <= servoPosDeploy; x++) {
    camServo.write(x);
    delay(25);
  }
  while (digitalRead(controlInput) == LOW) {
    ;
  }
  for (int x = servoPosDeploy; x >= servoPosRetract; x--) {
    camServo.write(x);
    delay(25);
  }
  if (debugMode) Serial.println("capture complete.");
}
