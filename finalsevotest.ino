#include <ESP32Servo.h>
#include <ESP32Servo.h>

#define SERVO_PIN 4

Servo myServo;

void setup() {
  myServo.attach(SERVO_PIN); 
}

void loop() {
  myServo.write(0);
  delay(500);

  myServo.write(90);   
  delay(500);

  myServo.write(180);
  delay(500);
}


