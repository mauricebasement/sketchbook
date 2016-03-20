#ifndef MoisutreSensor_h
#define MoistureSensor_h

#include "Arduino.h"

class MoistureSensor
{
  public:
    MoistureSensor(int pin1,int pin2, int pin3);
    int checkMoisture();
    void setCurrent(boolean reverse);
    void sleep();
  private:
    int _pin1;
    int _pin2;
    int _pin3;
};

#endif
