
#include <OneWire.h>


OneWire  ds(7);  // on pin 10 (a 4.7K resistor is necessary)
#include <dht.h>
dht DHT;
#define DHT11_PIN 8
float values[3];
int counter = 0;
#define UPPERTHRESHOLD 80
#define LOWERTHRESHOLD 15
#define TEMPERATURETHRESHOLD 26
float nfspd = LOWERTHRESHOLD/100;
float ow[4];


void setup(void)
{
  analogWrite(9,nfspd*255);
  Serial.begin(115200);
  checkDHT();
}
  
void loop(void)
{
    readDHT();
    readOW();
    setFanSpeed();
}

int checkDHT()
{
  // READ DATA
  Serial.print("DHT11, \t");
  int chk = DHT.read11(DHT11_PIN);
  switch (chk)
  {
    case DHTLIB_OK:  
    Serial.print("OK,\t"); 
    break;
    case DHTLIB_ERROR_CHECKSUM: 
    Serial.print("Checksum error,\t"); 
    break;
    case DHTLIB_ERROR_TIMEOUT: 
    Serial.print("Time out error,\t"); 
    break;
    case DHTLIB_ERROR_CONNECT:
        Serial.print("Connect error,\t");
        break;
    case DHTLIB_ERROR_ACK_L:
        Serial.print("Ack Low error,\t");
        break;
    case DHTLIB_ERROR_ACK_H:
        Serial.print("Ack High error,\t");
        break;
    default: 
    Serial.print("Unknown error,\t"); 
    break;
  }
}  
int readDHT() {
  DHT.read11(DHT11_PIN);
  values[0] = DHT.humidity;
  values[1] = DHT.temperature;
  Serial.print("DHT Humidity:");
  Serial.println(DHT.humidity);
  Serial.print("DHT Temperature:");
  Serial.println(DHT.temperature);
}
void readOW() {
  byte i;
  byte present = 0;
  byte type_s;
  byte data[12];
  byte addr[8];
  float celsius, fahrenheit;
  
  /*if ( !ds.search(addr)) {
    Serial.println("No more addresses.");
    Serial.println();
    ds.reset_search();
    delay(250);
    return;
  }*/
  ds.search(addr);
  type_s = 0;
    

  ds.reset();
  ds.select(addr);
  ds.write(0x44, 1);        // start conversion, with parasite power on at the end

  delay(1000);
  
  present = ds.reset();
  ds.select(addr);    
  ds.write(0xBE);         // Read Scratchpad

  for ( i = 0; i < 9; i++) {           // we need 9 bytes
    data[i] = ds.read();
  }
  
  // Convert the data to actual temperature
  // because the result is a 16 bit signed integer, it should
  // be stored to an "int16_t" type, which is always 16 bits
  // even when compiled on a 32 bit processor.
  int16_t raw = (data[1] << 8) | data[0];
  if (type_s) {
    raw = raw << 3; // 9 bit resolution default
    if (data[7] == 0x10) {
      // "count remain" gives full 12 bit resolution
      raw = (raw & 0xFFF0) + 12 - data[6];
    }
  } else {
    byte cfg = (data[4] & 0x60);
    // at lower res, the low bits are undefined, so let's zero them
    if (cfg == 0x00) raw = raw & ~7;  // 9 bit resolution, 93.75 ms
    else if (cfg == 0x20) raw = raw & ~3; // 10 bit res, 187.5 ms
    else if (cfg == 0x40) raw = raw & ~1; // 11 bit res, 375 ms
    //// default is 12 bit resolution, 750 ms conversion time
  }
  values[2] = (float)raw / 16.0;
  
  ow[0] = ow[1];
  ow[1] = ow[2];
  ow[2] = ow[3];
  ow[3] = values[2];
  values[2] = 0;
    for(int i = 0; i < 4;i++) {
    values[2]+=ow[i];
  }
  values[2]/=4;
  Serial.print("OW Temperature");
  Serial.println(values[2]);
  Serial.println("(Avaraged over last 4 measurments)");
  
}

void setFanSpeed() {
  if(values[2] <= TEMPERATURETHRESHOLD) {
    nfspd = 0.01 * LOWERTHRESHOLD;
    Serial.println("Lower Threshold Set");
  } else {
    nfspd = max(0.01 * (UPPERTHRESHOLD - LOWERTHRESHOLD) * (values[2] - TEMPERATURETHRESHOLD), 0.01*LOWERTHRESHOLD);
    Serial.println("Fan Speed Set according to algorithm");
  }
  nfspd = max(0.15,min(nfspd,0.9));
  Serial.print("Set Fanspeed to:");
  Serial.println(nfspd);
  analogWrite(9,nfspd*255);
}

