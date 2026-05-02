#include "DFRobotDFPlayerMini.h"

// نستخدم UART2
HardwareSerial mySerial(2);

// إنشاء كائن DFPlayer
DFRobotDFPlayerMini player;

void setup() {

  // Serial Monitor
  Serial.begin(9600);
  Serial.println("Starting...");

  // بدء الاتصال مع DFPlayer
  // (baud rate, config, RX, TX)
  mySerial.begin(9600, SERIAL_8N1, 27, 26);

  // تهيئة DFPlayer
  if (player.begin(mySerial)) {
    Serial.println("DFPlayer Mini OK");

    player.volume(20);   // الصوت (0 - 30)
    player.play(1);      // تشغيل أول ملف

  } else {
    Serial.println("DFPlayer Mini Error!");
  }
}

void loop() {
  // فاضي حالياً
}