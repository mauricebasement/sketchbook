#include <TimeAlarms.h>
#include <LiquidCrystal.h>
#include <Wire.h>
#include <Time.h>
#include <DS1307RTC.h>
#include <SPI.h>
#include <SD.h>
#include <OneWire.h>
#include <dht.h>
#define DHT11_PIN 23

dht DHT;
float waterTemp;
float airTemp;
float airHumidity;
float waterTempAvg;
float airTempAvg;
float airHumidityAvg;
float waterTempTot;
float airTempTot;
float airHumidityTot;
int dataCounter = 0;
String timeStr;
String dateStr;
OneWire ds(22);
File myFile;
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

void setup() {
  pinMode(10, OUTPUT); //SD Card Pin
  lcd.begin(16, 2);
  lcd.print("Welcome to Aqua");
  lcd.setCursor(0,1);
  lcd.print("Controll");
  delay(1000);
  Alarm.timerRepeat(20, writeLog);
  Alarm.timerRepeat(5, getData);
  Alarm.timerRepeat(10, printData);
  getTime();
  getData();
  writeLog();
  initSD();
}
void printData() {
  lcd.clear();
  printTime();
  lcd.setCursor(0,0);
  String printString = String(waterTempAvg).substring(0,4)+":"+String(airTempAvg).substring(0,4)+":"+String(airHumidityAvg).substring(0,4);
  lcd.print(printString);
}
void getData() {
  getDHT();
  waterTemp=waterTemperature();
  dataCounter += 1;
  waterTempTot += waterTemp;
  waterTempAvg = waterTempTot/dataCounter;
  airTempTot += airTemp;
  airTempAvg = airTempTot/dataCounter;
  airHumidityTot += airHumidity;
  airHumidityAvg = airHumidityTot/dataCounter;
}
void loop() {
  int readKey = keyPad(analogRead(0));
  if(readKey != 0) doKey(readKey);
  Alarm.delay(10);
}

void printTime() {
  lcd.setCursor(0,1);
  getTime();
  lcd.print(timeStr+dateStr);
}
int keyPad(int input) {
  if (verifyKeyPad(input,0)) {
    return 1;
  } if (verifyKeyPad(input,131)) {
    return 2;
  } if (verifyKeyPad(input,309)) {
    return 3;
  } if (verifyKeyPad(input,481)) {
    return 4;
  } if (verifyKeyPad(input,722)) {
    return 5;
  } else {
    return 0;
  }
}
void doKey(int key) {
  switch (key) {
  case 1:
  break;
  case 2:
  break;
  case 3:
  break;
  case 4:
  break;
  case 5:
  break;
  default:
  break;
  }
}

boolean verifyKeyPad(int input, int compare) {
  int range = 5;
  if (input >= compare-range && input <= compare+range) {
    return true;
  }else{
    return false;
  }
}
  
String getTime() {
  timeStr = "";
  dateStr = "";
  tmElements_t tm;
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
  String log = dateStr+".log";
  log.replace(":","_");
  char __dataFileName[log.length()+1];
  log.toCharArray(__dataFileName, sizeof(__dataFileName));
  myFile = SD.open(__dataFileName, FILE_WRITE);
  if (myFile) {
    myFile.println(timeStr+" : "+String(waterTempAvg)+" : "+String(airTempAvg)+" : "+String(airHumidityAvg));
    myFile.close();
  } else {
  }
  airTempTot=0;
  airHumidityTot=0;
  waterTempTot=0;
  dataCounter=0;
}
void initSD() {
  while (!SD.begin(10, 11, 12, 13)) {
    lcd.clear();
    lcd.print("Insert SD Card");
  }
  lcd.setCursor(0,0);
  lcd.print("SDInitialization");
  lcd.setCursor(0,1);
  lcd.print("Complete");
  delay(100);
}
float waterTemperature() {
  float tmp = getWaterTemperature();
  while (tmp == 0) { 
    tmp = getWaterTemperature();
  }
  return tmp;
}
  
float getWaterTemperature() {
  byte i;
  byte present = 0;
  byte type_s;
  byte data[12];
  byte addr[8];
  float celsius, fahrenheit;
  if ( !ds.search(addr)) {
    ds.reset_search();
    delay(250);
    return 0;
  }
  if (OneWire::crc8(addr, 7) != addr[7]) {
      return 0;
  }
  type_s = 0;
  ds.reset();
  ds.select(addr);
  ds.write(0x44, 1);        // start conversion, with parasite power on at the end
  delay(1000);     // maybe 750ms is enough, maybe not
  // we might do a ds.depower() here, but the reset will take care of it
  present = ds.reset();
  ds.select(addr);    
  ds.write(0xBE);         // Read Scratchpad
  for ( i = 0; i < 9; i++) {           // we need 9 bytes
    data[i] = ds.read();
  }
  int16_t raw = (data[1] << 8) | data[0];
  if (type_s) {
    raw = raw << 3; // 9 bit resolution default
    if (data[7] == 0x10) {
      // "count remain" gives full 12 bit resolution
      raw = (raw & 0xFFF0) + 12 - data[6];
    }
  } else {
    byte cfg = (data[4] & 0x60);
    if (cfg == 0x00) raw = raw & ~7;  // 9 bit resolution, 93.75 ms
    else if (cfg == 0x20) raw = raw & ~3; // 10 bit res, 187.5 ms
    else if (cfg == 0x40) raw = raw & ~1; // 11 bit res, 375 ms
    //// default is 12 bit resolution, 750 ms conversion time
  }
  celsius = (float)raw / 16.0;
  return celsius;
}
float getDHT() {
  DHT.read11(DHT11_PIN);
  airHumidity = DHT.humidity;
  airTemp = DHT.temperature;
}

