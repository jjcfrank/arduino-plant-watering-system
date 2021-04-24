#include <Wire.h>
#include "Adafruit_seesaw.h"

int unsetPin = 3;
int setPin = 2;
int battery = A0;
float batteryVolts = 0;
float batteryVoltsRaw = 0;
const int greenLEDPin = 9;
const int blueLEDPin = 10;
const int redLEDPin = 11;


Adafruit_seesaw ss;

void setup() {

  pinMode(unsetPin, OUTPUT);
  digitalWrite(unsetPin, LOW);
  pinMode(setPin, OUTPUT);
  digitalWrite(setPin, HIGH);

  pinMode(greenLEDPin, OUTPUT);
  pinMode(redLEDPin, OUTPUT);
  pinMode(blueLEDPin, OUTPUT);
  
  Serial.begin(115200);
  Serial.begin(9600);
     
  Serial.println("seesaw Soil Sensor example!");
  
  if (!ss.begin(0x36)) {
    Serial.println("ERROR! seesaw not found");
    while(1);
  } else {
    Serial.print("seesaw started! version: ");
    Serial.println(ss.getVersion(), HEX);
  }
}

void loop() {

  float tempC = ss.getTemp();
  uint16_t capread = ss.touchRead(0);

  //Serial.print("Temperature: "); Serial.print(tempC); Serial.println("*C");
  //Serial.print("Capacitive: "); Serial.println(capread);

  batteryVoltsRaw = analogRead(battery);
  batteryVolts = (batteryVoltsRaw / 1023);
  Serial.println(batteryVolts);

  if (batteryVolts < 0.25) {
    analogWrite(redLEDPin, 100);
    }
   

  if (capread < 500) {
    //Serial.println("dry");
    digitalWrite(unsetPin, HIGH);
    digitalWrite(setPin, LOW);
    }
  else if (capread > 700) {
    //Serial.println("watered");
    digitalWrite(unsetPin, LOW);
    digitalWrite(setPin, HIGH);
    }

  delay(1000);
}
