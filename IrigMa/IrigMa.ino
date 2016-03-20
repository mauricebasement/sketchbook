#include <MoistureSensor.h>
#include <Time.h>
#include <TimeAlarms.h>

int pumpPin = 10;

int moisture = 0;
int moistureThreshold = 40;
int moistureRange = 5;

MoistureSensor sensor1(11,12,1);

void setup() {
  setTime(0,0,0,1,1,15);
  pinMode(pumpPin,OUTPUT);
  digitalWrite(pumpPin,HIGH);
  Alarm.timerRepeat(120, controlMoisture);
  Serial.begin(9600);
  Serial.println("Welcome to IrigMa Debug Mode");
}
void loop() {
  Alarm.delay(100);
  Serial.print("-");
}

void controlMoisture() {
  sensor1.setCurrent(false);
  delay(1000);
  moisture = sensor1.checkMoisture();
  sensor1.setCurrent(true);
  delay(1000);
  moisture += sensor1.checkMoisture();
  moisture = moisture /2;
  sensor1.sleep();
  if (moisture <= moistureThreshold) giveWater();
  Serial.print("Moisture: ");
  Serial.println(moisture);  
}

void giveWater() {
  Serial.println("Giving Water");
  digitalWrite(pumpPin,LOW);
  delay(5000);
  digitalWrite(pumpPin,HIGH);
}


