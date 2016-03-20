#include <Wire.h>
#include <Time.h>
#include <TimeAlarms.h>
#include <DS3231.h>

DS3231  rtc(SDA, SCL);
Time t;
int timeChecker = 1023;

void setup()
{
  Serial.begin(9600);
  rtc.begin();
  checkTime();
  pinMode(2, OUTPUT);
  openDoor();
  if(hour() <= 9) {
    closeDoor();
  }else if(hour() >= 21) {
    closeDoor();
  }
  Alarm.alarmRepeat(9,00,0, openDoor);
  Alarm.alarmRepeat(21,00,0, closeDoor);
} 

void  loop(){  
  digitalClockDisplay();
  Alarm.delay(1000);
  if(timeChecker > 0) { 
    timeChecker--;
  } else {
    timeChecker = 1000;
    checkTime();
  }
}

void openDoor(){
  digitalWrite(2, LOW);
}

void closeDoor(){
   digitalWrite(2, HIGH);
}

void digitalClockDisplay()
{
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  Serial.println(); 
}

void printDigits(int digits)
{
  Serial.print(":");
  if(digits < 10)
    Serial.print('0');
  Serial.print(digits);
}

void checkTime() {  
  t = rtc.getTime();
  setTime(t.hour,t.min,t.sec,t.date,t.mon,t.year);
}
