#include <MoistureSensor.h>

MoistureSensor sensor1(22,23,8);

void setup() {
  Serial.begin(9600);
}

void loop() {
  sensor1.setCurrent(true);
  delay(1000);
  Serial.println(sensor1.checkMoisture());
  sensor1.setCurrent(false);
  delay(1000);
  Serial.println(1023-sensor1.checkMoisture());
}
