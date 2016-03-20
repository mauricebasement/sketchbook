#include <SD.h>
#include <SPI.h>
#include <MoistureSensor.h>
#include <Time.h>
//#include <TimeAlarms.h>
#include <LiquidCrystal.h>
#include <DS1307RTC.h>
#include <Wire.h>

int pumpPin = 30;

int moisture[5] = { 0, 0, 0, 0, 0 };
int moistureThreshold = 50;
int moistureRange = 5;

String timeStr;
String dateStr;

MoistureSensor sensor1(22,23,8);
MoistureSensor sensor2(24,25,9);
MoistureSensor sensor3(26,27,10);
MoistureSensor sensor4(28,29,11);
//MoistureSensor sensors[4] = {sensor1,sensor2,sensor3,sensor4};

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
File logFile;

void setup() {
  getTime();
  initSD();
  lcd.begin(16, 2);
  lcd.print("Hello IrigMa");
  lcd.setCursor(0,1);
  lcd.print(dateStr+timeStr);
  delay(500);
  lcd.clear();
  pinMode(pumpPin,OUTPUT);
  digitalWrite(pumpPin,HIGH);
  controlMoisture();
    //Alarm.timerRepeat(20, controlMoisture);
}
void loop() {
  //Alarm.delay(100);
  controlMoisture();
  delay(10000);
}

int getMoisture(MoistureSensor sensor) {
  sensor.setCurrent(false);
  delay(1000);
  int moisture0 = sensor.checkMoisture();
  sensor.setCurrent(true);
  delay(1000);
  moisture0 += sensor.checkMoisture();
  moisture0 = moisture0 /2;
  sensor.sleep();
  return moisture0;
}

void controlMoisture() {
  moisture[1] = getMoisture(sensor1);
  moisture[2] = getMoisture(sensor2);
  moisture[3] = getMoisture(sensor3);
  moisture[4] = getMoisture(sensor4);
  lcd.setCursor(0,0);
  lcd.print(String(moisture[1])+":"+String(moisture[2])+":"+String(moisture[3])+":"+String(moisture[4]));
  moisture[0] = moisture[1] + moisture[2] + moisture[3] + moisture[4];
  moisture[0] = moisture[0] / 4;
  if (moisture[0] <= moistureThreshold) giveWater();
  writeLog();
}

void giveWater() {
  digitalWrite(pumpPin,LOW);
  lcd.setCursor(0,0);
  delay(5000);
  digitalWrite(pumpPin,HIGH);
  writeToLog("Giving Water");
}

String getTime() {
  timeStr = "";
  dateStr = "";
  tmElements_t tm;
  setTime(tm.Hour,tm.Minute,tm.Second,tm.Day,tm.Month,tmYearToCalendar(tm.Year));
  if (RTC.read(tm)) {
    timeStr +=digits(tm.Hour);
    timeStr +=':';
    timeStr +=digits(tm.Minute);
    timeStr +=':';
    timeStr +=digits(tm.Second);
    dateStr +=digits(tm.Day);
    dateStr +=':';
    dateStr +=digits(tm.Month);
    dateStr +=':';
    dateStr +=String(tmYearToCalendar(tm.Year)).substring(2);
    return timeStr+":"+dateStr;
  } else {
    if (RTC.chipPresent()) {
      return "Please set Time!";
    } else {
      return "DS1307 read error!";
    }
  }
}

String digits(int input) {
  if (input<=9) return "0"+String(input);
  else return String(input);
}

void writeLog()
{
  getTime();
  lcd.setCursor(0,1);
  lcd.print(dateStr+timeStr);
  String logName = dateStr+".log";
  logName.replace(":","_");
  char __dataFileName[logName.length()+1];
  logName.toCharArray(__dataFileName, sizeof(__dataFileName));
  logFile = SD.open(__dataFileName, FILE_WRITE);
  if (logFile) {
    logFile.println(timeStr+String(moisture[1])+":"+String(moisture[2])+":"+String(moisture[3])+":"+String(moisture[4]));
    logFile.close();
  } else {
  }
}

void writeToLog(String message) {
  getTime();
  lcd.setCursor(0,1);
  lcd.print(dateStr+timeStr);
  String logName = dateStr+".log";
  logName.replace(":","_");
  char __dataFileName[logName.length()+1];
  logName.toCharArray(__dataFileName, sizeof(__dataFileName));
  logFile = SD.open(__dataFileName, FILE_WRITE);
  if (logFile) {
    logFile.println(timeStr);
    logFile.close();
  } else {
    lcd.setCursor(0,1);
    lcd.print(timeStr+" "+message);
  }
}

void initSD() {
  lcd.print("SD Init");
  pinMode(10, OUTPUT);
  while (!SD.begin(10,11,12,13)) {
    lcd.setCursor(0,0);
    lcd.println("Insert SD Card");
  }
  lcd.setCursor(0,0);
  lcd.println("SD Init Done");
  delay(500);
  lcd.clear();
}

