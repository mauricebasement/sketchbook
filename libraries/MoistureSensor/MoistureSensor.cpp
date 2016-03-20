#include "Arduino.h"
#include "MoistureSensor.h"

MoistureSensor::MoistureSensor(int pin1, int pin2, int pin3)
{
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  pinMode(pin3, INPUT_PULLUP);
  
  _pin1 = pin1;
  _pin2 = pin2;
  _pin3 = pin3;
}

int MoistureSensor::checkMoisture() {
  return analogRead(_pin3);
}
void MoistureSensor::setCurrent(boolean reverse) {
  if (reverse == true) {
    digitalWrite(_pin1,HIGH);
    digitalWrite(_pin2,LOW);
  } else {
    digitalWrite(_pin1,LOW);
    digitalWrite(_pin2,HIGH);
  }
}
void MoistureSensor::sleep() {
  digitalWrite(_pin1,LOW);
  digitalWrite(_pin2,LOW);
}



