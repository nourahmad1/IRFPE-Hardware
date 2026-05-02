#include "BluetoothSerial.h"

// ─────────────────────────────────────────────
//  Safety checks – will throw a compile error
//  if you picked the wrong board in Arduino IDE
// ─────────────────────────────────────────────
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
  #error Bluetooth is not enabled! Go to Tools > Board and select "ESP32 Dev Module"
#endif

#if !defined(CONFIG_BT_SPP_ENABLED)
  #error Classic Bluetooth (SPP) not available on this chip. \
  It only works on the original ESP32 (not S2 / S3 / C3 / C6).
#endif

// ─────────────────────────────────────────────
//  Bluetooth
// ─────────────────────────────────────────────
BluetoothSerial SerialBT;

// ─────────────────────────────────────────────
//  Motor driver pins  (L298N)
//    Motor A  →  IN1 / IN2  +  enA (PWM)
//    Motor B  →  IN3 / IN4  +  enB (PWM)
// ─────────────────────────────────────────────
const int enA = 33;
const int enB = 13;

const int IN1 = 25;
const int IN2 = 26;
const int IN3 = 27;
const int IN4 = 14;

// Speed: 0 – 255
int Speed = 200;

// ─────────────────────────────────────────────
//  Forward declarations
// ─────────────────────────────────────────────
void forward();
void backward();
void turnLeft();
void turnRight();
void stopCar();
void setSpeed(int spd);

// ═════════════════════════════════════════════
//  SETUP
// ═════════════════════════════════════════════
void setup() {
  Serial.begin(115200);
  delay(500);   // let the serial monitor catch up

  // Motor direction pins
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // PWM for speed control (new ESP32 Arduino core style)
  ledcAttach(enA, 5000, 8);   // pin, freq, resolution
  ledcAttach(enB, 5000, 8);

  stopCar();   // make sure motors are off on boot

  // Start Bluetooth
  bool btOK = SerialBT.begin("ESP32_Car");   // device name visible to phone

  if (btOK) {
    Serial.println("=================================");
    Serial.println("  Bluetooth started successfully ");
    Serial.println("  Device name : ESP32_Car        ");
    Serial.println("  Waiting for connection...      ");
    Serial.println("=================================");
  } else {
    Serial.println("[ERROR] Bluetooth failed to start!");
  }
}

// ═════════════════════════════════════════════
//  LOOP
// ═════════════════════════════════════════════
void loop() {
  if (SerialBT.available()) {
    char cmd = SerialBT.read();
    Serial.print("Command received: ");
    Serial.println(cmd);   // debug – visible in Serial Monitor

    switch (cmd) {
      case 'F': forward();   break;
      case 'B': backward();  break;
      case 'L': turnLeft();  break;
      case 'R': turnRight(); break;
      case 'S': stopCar();   break;

      // Optional speed commands sent from the app
      case '0': setSpeed(0);   break;
      case '1': setSpeed(100); break;
      case '2': setSpeed(150); break;
      case '3': setSpeed(200); break;
      case '4': setSpeed(255); break;

      default:
        Serial.print("Unknown command: ");
        Serial.println(cmd);
        break;
    }
  }
}

// ═════════════════════════════════════════════
//  MOTION FUNCTIONS
// ═════════════════════════════════════════════

void forward() {
  ledcWrite(enA, Speed);
  ledcWrite(enB, Speed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  Serial.println(">> FORWARD");
}

void backward() {
  ledcWrite(enA, Speed);
  ledcWrite(enB, Speed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  Serial.println(">> BACKWARD");
}

void turnLeft() {
  ledcWrite(enA, Speed);
  ledcWrite(enB, Speed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  Serial.println(">> LEFT");
}

void turnRight() {
  ledcWrite(enA, Speed);
  ledcWrite(enB, Speed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  Serial.println(">> RIGHT");
}

void stopCar() {
  ledcWrite(enA, 0);
  ledcWrite(enB, 0);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  Serial.println(">> STOP");
}

// ─────────────────────────────────────────────
//  Change speed on the fly
// ─────────────────────────────────────────────
void setSpeed(int spd) {
  Speed = constrain(spd, 0, 255);
  Serial.print(">> Speed set to: ");
  Serial.println(Speed);
 