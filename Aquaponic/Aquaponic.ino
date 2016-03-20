#include <OneWire.h>
#include <Wire.h>
int val10;
int val11;

#define UVSensorPin 1
#define UVThreshold 4
#define voltageSensorPin 0
#define voltageThreshold 13
#define heaterRelayPin 22
#define pumpRelayPin 23

OneWire  ds(24);

long heaterOn;
long heaterOff;
int heaterState = 0;
long pumpOn;
long pumpOff;
int pumpState = 0;
int printDataState = 0;
long printDataOn;
float wTemperature = 0;
//int binaryOutputs[5] = {28,29,30,31,32};

void setup()
{
  Serial.begin(9600);
  Serial.println("Aquaponic Controll 2015");
  /*    pinMode(binaryOutputs[i],OUTPUT)for (int i = 0; i<5;i++) {
    pinMode(binaryOutputs[i],OUTPUT);
  }*/
  pinMode(heaterRelayPin,OUTPUT);
  pinMode(pumpRelayPin,OUTPUT);
}
void loop()
{
      checkHeater();
      checkPump();
      checkPrint();
      if (readVoltage(voltageSensorPin) >= voltageThreshold & heaterState == 0) triggerHeater(1000,9000);
      if (readUV(UVSensorPin) >= UVThreshold & pumpState == 0) triggerPump(30000,40000);      
      if (printDataState == 0) triggerPrint(4000);
}
void printData() {
  Serial.print("Voltage: ");
  Serial.println(readVoltage(voltageSensorPin));
  Serial.print("UV: ");
  Serial.println(readUV(UVSensorPin));
  if(pumpState == 1) {
    Serial.println("Pump: ON"); 
  } else {
    Serial.println("Pump: OFF");
  }
  if(heaterState == 1) {
    Serial.println("Heater: ON"); 
  } else {
    Serial.println("Heater: OFF");
  }
   while (wTemperature == 0) {
    wTemperature = waterTemperature();
   }
    Serial.print("Water Temperature: ");
    Serial.println(wTemperature);
    //binaryOutput(wTemperature,binaryOutputs);
    wTemperature = 0;

}
float readVoltage(int pin) {
      val10=analogRead(pin);
      return val10/4.092/10;
}
int readUV(int pin) {
  return analogRead(pin);
}
void checkHeater() {
  if (heaterState == 1) {
    digitalWrite(heaterRelayPin,HIGH);
    if(heaterOn<=millis()){
      heaterState=2; 
      digitalWrite(heaterRelayPin,LOW);
    }
  }
  if (heaterState == 2 & heaterOff<=millis()) heaterState=0;
}
void checkPump() {
  if (pumpState == 1) {
    digitalWrite(pumpRelayPin,HIGH);
    if(pumpOn<=millis()){
      pumpState=2; 
      digitalWrite(pumpRelayPin,LOW);
    }
  }
  if (pumpState == 2 & pumpOff<=millis()) pumpState=0;
}
void checkPrint() {
  if (printDataState == 1) {
    printData();
    printDataState = 2;
  }
  if(printDataOn<=millis() & printDataState == 2) printDataState = 0; 
}
void triggerHeater(long on,long off) {
  heaterOn = millis()+on;
  heaterOff = millis()+on+off;
  heaterState = 1;
}
void triggerPump(long on, long off) {
  pumpOn = millis()+on;
  pumpOff = millis()+on+off;
  pumpState = 1;
}
void triggerPrint(int on) {
  printDataOn = millis()+on;
  printDataState = 1;
}
float waterTemperature() {
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
  // we might do a ds.depower() here, but the reset will take care of it.
  
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
void binaryOutput(float output,int binaryOut[5]) {
  int result[5];
  int number =  int(output);
  for (int i=0;i<5;i+=1) {
    if (number%2 == 1) { result[i] = 1; 
      }else{ result[i] = 0; }
      number/=2;
  }
  for (int i=0;i<5;i+=1) {
    Serial.print(result[i]);
    if (result[i] == 1) {
      digitalWrite(binaryOut[i],HIGH);
    }else{
      digitalWrite(binaryOut[i],LOW);
    }
  }

}

