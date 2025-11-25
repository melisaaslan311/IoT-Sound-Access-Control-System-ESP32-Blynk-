#define BLYNK_TEMPLATE_ID "TMPL6adxTYoFR"
#define BLYNK_TEMPLATE_NAME "final homework"
#define BLYNK_AUTH_TOKEN "kBu2igfuEO6Ep_GHhiETR22Ma9B9IH2i"
#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <SPI.h>
#include <MFRC522.h>
#include <ESP32Servo.h>

char ssid[] = "TURKNET_A079B";
char pass[] = "ts3bRT2f";

#define RST_PIN    22
#define SS_PIN     21
MFRC522 rfid(SS_PIN, RST_PIN);

Servo myServo;
#define SERVO_PIN 27

#define SOUND_SENSOR_PIN 32

#define RED_PIN   26
#define GREEN_PIN 25
#define BLUE_PIN  33

// Blynk virvual pins
#define VPIN_UID       V0
#define VPIN_SOUND     V1
#define VPIN_SERVO     V2
#define VPIN_COLOR_TXT V3
#define VPIN_WARNING   V4

String activeUID = "";
bool cardRegistered = false;

BlynkTimer timer;

void setColor(String level) {
  if (level == "Silence") {
    digitalWrite(RED_PIN, LOW);
    digitalWrite(GREEN_PIN, LOW);
    digitalWrite(BLUE_PIN, HIGH);
  } else if (level == "Middle") {
    digitalWrite(RED_PIN, LOW);
    digitalWrite(GREEN_PIN, HIGH);
    digitalWrite(BLUE_PIN, LOW);
  } else if (level == "High") {
    digitalWrite(RED_PIN, HIGH);
    digitalWrite(GREEN_PIN, LOW);
    digitalWrite(BLUE_PIN, LOW);
  }
}

void checkRFID() {
  if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
    String uid = "";
    for (byte i = 0; i < rfid.uid.size; i++) {
      uid += String(rfid.uid.uidByte[i] < 0x10 ? "0" : "");
      uid += String(rfid.uid.uidByte[i], HEX);
    }
    uid.toUpperCase();

    activeUID = uid;
    cardRegistered = true;
    Serial.println("The card was introduced: " + activeUID);

    delay(1500);
    rfid.PICC_HaltA();
    rfid.PCD_StopCrypto1();
  }
}

void updateSensorAndActuators() {
  if (cardRegistered) {
    int soundVal = analogRead(SOUND_SENSOR_PIN);
    Serial.println("Sound Value: " + String(soundVal));

    String soundLevel;
    int angle;

    if (soundVal < 1) {
      soundLevel = "Silence";
      angle = 0;
      Blynk.virtualWrite(VPIN_WARNING, "🔇 Silence");
    } else if (soundVal >= 1 && soundVal < 2000) {
      soundLevel = "Middle";
      angle = 45;
      Blynk.virtualWrite(VPIN_WARNING, "🟢 Midrange Sound");
    } else {
      soundLevel = "High";
      angle = 90;
      Blynk.virtualWrite(VPIN_WARNING, "⚠️ High Level Sound!");
    }

    myServo.write(angle);
    setColor(soundLevel);

    // Blynk dashboard güncellemesi:
    Blynk.virtualWrite(VPIN_UID,activeUID);
    Blynk.virtualWrite(VPIN_SOUND, soundVal);
    Blynk.virtualWrite(VPIN_SERVO, angle);
    Blynk.virtualWrite(VPIN_COLOR_TXT, soundLevel);
  }
}

void setup() {
  Serial.begin(9600);

  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  myServo.attach(SERVO_PIN);

  SPI.begin();
  rfid.PCD_Init();
  delay(1000);
  Serial.println("Please introduce a card...");

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  timer.setInterval(500L, checkRFID);

  timer.setInterval(1000, updateSensorAndActuators);
}

void loop() {
  Blynk.run();
  timer.run();
}
