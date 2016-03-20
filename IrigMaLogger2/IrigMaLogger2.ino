#include <SD.h>
#include <SPI.h>
#include <MoistureSensor.h>
#include <Time.h>
#include <LiquidCrystal.h>
#include <DS1307RTC.h>
#include <Wire.h>

#define BACKLIGHT_PIN 31
#define BACKLIGHT_TIME 20
#define PUMP_PIN 30
#define PUMP_TIME 10
#define INTERVAL 60

boolean backLightOn = true;
boolean pumpOn = false;
boolean waterLog = false;
int backLightCounter = 0;
int pumpCounter = 0;

int moisture[5] = { 0, 0, 0, 0, 0 };
int moistureThreshold = 50;

String time[2];

MoistureSensor sensor1(22, 23, 8);
MoistureSensor sensor2(24, 25, 9);
MoistureSensor sensor3(26, 27, 10);
MoistureSensor sensor4(28, 29, 11);
MoistureSensor sensor5(30, 31, 11);
MoistureSensor sensors[5] = {sensor1, sensor2, sensor3, sensor4, sensor5};

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
File logFile;

void setup() {
  pinMode(BACKLIGHT_PIN, OUTPUT);
  pinMode(PUMP_PIN, OUTPUT);
  digitalWrite(BACKLIGHT_PIN, HIGH);
  digitalWrite(PUMP_PIN, LOW);
  
  getTime();
  initSD();
  
  lcd.begin(16, 2);
  lcd.print("Hello IrigMa");
  lcd.setCursor(0, 1);
  lcd.print(time[0] + time[1]);
  delay(500);
}

void loop() {
  controlMoisture();
  for (int i = 0; i < INTERVAL; i++) {
    getTime();
    lcd.setCursor(0, 1);
    lcd.print(time[1] + time[0]);
    int key = keyPad(analogRead(0));
    if (key == 1) {
      backLightOn = true;
    }
    if (key == 2) {
      pumpOn = true;
      lcd.setCursor(0, 1);
      lcd.print("Manual Watering");
      writeToLog("Manually Giving Water");
    }
    if (key == 5) {
      waterLog = true;
      lcd.setCursor(0, 1);
      lcd.print("External Watering");
    }
    checkTimers();
    delay(1000);
  }
}

void checkTimers() {
  if (backLightOn) {
    backLightCounter = BACKLIGHT_TIME;
    backLightOn = false;
  }
  if (backLightCounter > 0) {
    digitalWrite(BACKLIGHT_PIN, HIGH);
    backLightCounter -= 1;
  }
  if (backLightCounter == 0) digitalWrite(BACKLIGHT_PIN, LOW);
  
  if (waterLog) {
    waterLog = false;
    writeToLog("Giving Water from external source");
    lcd.setCursor(0, 1);
    lcd.print("External Watering");
  }
  
  if (pumpOn) {
   pumpOn = false;
   pumpCounter = 10;
   digitalWrite(PUMP_PIN, HIGH);
  }
  if (pumpCounter > 0) pumpCounter--;
  if (pumpCounter == 0) digitalWrite(PUMP_PIN, LOW);
}

int keyPad(int input) {
  if (verifyKeyPad(input, 0)) {
    return 1;
  } if (verifyKeyPad(input, 131)) {
    return 2;
  } if (verifyKeyPad(input, 309)) {
    return 3;
  } if (verifyKeyPad(input, 481)) {
    return 4;
  } if (verifyKeyPad(input, 722)) {
    return 5;
  } else {
    return 0;
  }
}

void getMoisture(MoistureSensor sensors[]) {
  int numberOfSensors = sizeof(sensors) / sizeof(MoistureSensor);
  //to be tested
  
  for (int i = 0; i < numberOfSensors; i++)sensors[i].setCurrent(false);
  delay(1000);
  for (int i = 0; i < numberOfSensors; i++)moisture[i + 1] =1023 - sensors[i].checkMoisture();
  for (int i = 0; i < numberOfSensors; i++)sensors[i].setCurrent(true);
  delay(1000);
  for (int i = 0; i < numberOfSensors; i++)moisture[i + 1] += sensors[i].checkMoisture();
  for (int i = 0; i < numberOfSensors; i++)moisture[i + 1] = moisture[i + 1] / 20.48;
  for (int i = 0; i < numberOfSensors; i++)sensors[i].sleep();
}

void controlMoisture() {
  getTime();
  getMoisture(sensors);
  moisture[0] = moisture[1] + moisture[2] + moisture[3] + moisture[4];
  moisture[0] = moisture[0] / 4;
  writeLog();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(String(moisture[0]) + ":" + String(moisture[1]) + ":" + String(moisture[2]) + ":" + String(moisture[3]) + ":" + String(moisture[4]) + String(moistureThreshold));
  lcd.setCursor(0, 1);
  lcd.print(time[1] + time[0]);
  if (moisture[0] <= moistureThreshold) giveWater();
}

void giveWater() {
  pumpOn = true;
}

String getTime() {
  time[0] = "";
  time[1] = "";
  tmElements_t tm;
  setTime(tm.Hour, tm.Minute, tm.Second, tm.Day, tm.Month, tmYearToCalendar(tm.Year));
  if (RTC.read(tm)) {
    time[0] += digits(tm.Hour);
    time[0] += ':';
    time[0] += digits(tm.Minute);
    time[0] += ':';
    time[0] += digits(tm.Second);
    time[1] += digits(tm.Day);
    time[1] += ':';
    time[1] += digits(tm.Month);
    time[1] += ':';
    time[1] += String(tmYearToCalendar(tm.Year)).substring(2);
    return time[0] + ":" + time[1];
  } else {
    if (RTC.chipPresent()) {
      return "Please set Time!";
    } else {
      return "DS1307 read error!";
    }
  }
}

String digits(int input) {
  if (input <= 9) return "0" + String(input);
  else return String(input);
}

void writeLog()
{
  String logName = time[1] + ".log";
  logName.replace(":", "_");
  char __dataFileName[logName.length() + 1];
  logName.toCharArray(__dataFileName, sizeof(__dataFileName));
  logFile = SD.open(__dataFileName, FILE_WRITE);
  if (logFile) {
    logFile.println(time[0] + " " + String(moisture[1]) + ":" + String(moisture[2]) + ":" + String(moisture[3]) + ":" + String(moisture[4]));
    logFile.close();
  } else {
    lcd.setCursor(0, 1);
    lcd.print("SD Error");
  }
}

void writeToLog(String message) {
  getTime();
  String logName = time[1] + ".log";
  logName.replace(":", "_");
  char __dataFileName[logName.length() + 1];
  logName.toCharArray(__dataFileName, sizeof(__dataFileName));
  logFile = SD.open(__dataFileName, FILE_WRITE);
  if (logFile) {
    logFile.println(time[0] + " j" + message);
    logFile.close();
  } else {
    lcd.setCursor(0, 1);
    lcd.print("SD Error");
  }
}

void initSD() {
  lcd.print("SD Init");
  pinMode(10, OUTPUT);
  while (!SD.begin(10, 11, 12, 13)) {
    lcd.setCursor(0, 0);
    lcd.println("Insert SD Card");
  }
  lcd.setCursor(0, 0);
  lcd.println("SD Init Done");
  delay(500);
  lcd.clear();
}

boolean verifyKeyPad(int input, int compare) {
  int range = 5;
  if (input >= compare - range && input <= compare + range) {
    return true;
  } else {
    return false;
  }
}
