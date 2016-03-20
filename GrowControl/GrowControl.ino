String serialInput;


#include <dht.h>

dht DHT1;
dht DHT2;
dht DHT3;
dht DHT4;


#define DHT1_PIN 10
#define DHT2_PIN 11
#define DHT3_PIN 12
#define DHT4_PIN 13

#define RELAY1_PIN 2
#define RELAY2_PIN 3
#define RELAY3_PIN 4
#define RELAY4_PIN 5
#define RELAY5_PIN 6
#define RELAY6_PIN 7
#define RELAY7_PIN 8
#define RELAY8_PIN 9

int relay1State = 0;
int relay2State = 0;
int relay3State = 0;
int relay4State = 0;
int relay5State = 0;
int relay6State = 0;
int relay7State = 0;
int relay8State = 0;

void setup() {
  
  pinMode(RELAY1_PIN,OUTPUT);
  pinMode(RELAY2_PIN,OUTPUT);
  pinMode(RELAY3_PIN,OUTPUT);
  pinMode(RELAY4_PIN,OUTPUT);
  pinMode(RELAY5_PIN,OUTPUT);
  pinMode(RELAY6_PIN,OUTPUT);
  pinMode(RELAY7_PIN,OUTPUT);
  pinMode(RELAY8_PIN,OUTPUT);
  
  digitalWrite(RELAY1_PIN,HIGH);
  digitalWrite(RELAY2_PIN,HIGH);
  digitalWrite(RELAY3_PIN,HIGH);
  digitalWrite(RELAY4_PIN,HIGH);
  digitalWrite(RELAY5_PIN,HIGH);
  digitalWrite(RELAY6_PIN,HIGH);
  digitalWrite(RELAY7_PIN,HIGH);
  digitalWrite(RELAY8_PIN,HIGH);
  
  Serial.begin(9600);
  Serial.setTimeout(100);
  Serial.println("Connected to GrowControl");
}
void loop() {
  
  DHT1.read22(DHT1_PIN);
  DHT2.read22(DHT2_PIN);
  DHT3.read22(DHT3_PIN);
  DHT4.read22(DHT4_PIN);
  
  serialInput = Serial.readString();
  
  if (serialInput == "getTemperature1") {
    Serial.println(DHT1.temperature);
  }if (serialInput == "getHumidity1") {
    Serial.println(DHT1.humidity); 
  }if (serialInput == "getTemperature2") {
    Serial.println(DHT2.temperature);
  }if (serialInput == "getHumidity2") {
    Serial.println(DHT2.humidity); 
  }if (serialInput == "getTemperature3") {
    Serial.println(DHT3.temperature);
  }if (serialInput == "getHumidity3") {
    Serial.println(DHT3.humidity); 
  }if (serialInput == "getTemperature4") {
    Serial.println(DHT4.temperature);
  }if (serialInput == "getHumidity4") {
    Serial.println(DHT4.humidity);
  }if (serialInput == "relay1On") {
    digitalWrite(RELAY1_PIN, LOW);
    relay1State = 1;
    Serial.println("relay1On");
  }if (serialInput == "relay1Off") {
    digitalWrite(RELAY1_PIN, HIGH);
    relay1State = 0;
    Serial.println("relay1Off");
  }if (serialInput == "relay1State") {
    Serial.println(relay1State);

  }if (serialInput == "relay2On") {
    digitalWrite(RELAY2_PIN, LOW);
    relay2State = 1;
    Serial.println("relay2On");
  }if (serialInput == "relay2Off") {
    digitalWrite(RELAY2_PIN, HIGH);
    relay2State = 0;
    Serial.println("relay2Off");
  }if (serialInput == "relay2State") {
    Serial.println(relay2State);

  }if (serialInput == "relay3On") {
    digitalWrite(RELAY3_PIN, LOW);
    relay3State = 1;
    Serial.println("relay3On");
  }if (serialInput == "relay3Off") {
    digitalWrite(RELAY3_PIN, HIGH);
    relay3State = 0;
    Serial.println("relay3Off");
  }if (serialInput == "relay3State") {
    Serial.println(relay3State);

  }if (serialInput == "relay4On") {
    digitalWrite(RELAY4_PIN, LOW);
    relay4State = 1;
    Serial.println("relay4On");
  }if (serialInput == "relay4Off") {
    digitalWrite(RELAY4_PIN, HIGH);
    relay4State = 0;
    Serial.println("relay4Off");
  }if (serialInput == "relay4State") {
    Serial.println(relay4State);

  }if (serialInput == "relay5On") {
    digitalWrite(RELAY5_PIN, LOW);
    relay5State = 1;
    Serial.println("relay5On");
  }if (serialInput == "relay5Off") {
    digitalWrite(RELAY5_PIN, HIGH);
    relay5State = 0;
    Serial.println("relay5Off");
  }if (serialInput == "relay5State") {
    Serial.println(relay5State);
    
  }if (serialInput == "relay6On") {
    digitalWrite(RELAY6_PIN, LOW);
    relay6State = 1;
    Serial.println("relay6On");
  }if (serialInput == "relay6Off") {
    digitalWrite(RELAY6_PIN, HIGH);
    relay6State = 0;
    Serial.println("relay6Off");
  }if (serialInput == "relay6State") {
    Serial.println(relay6State);
    
      }if (serialInput == "relay7On") {
    digitalWrite(RELAY7_PIN, LOW);
    relay7State = 1;
    Serial.println("relay7On");
  }if (serialInput == "relay7Off") {
    digitalWrite(RELAY7_PIN, HIGH);
    relay7State = 0;
    Serial.println("relay7Off");
  }if (serialInput == "relay7State") {
    Serial.println(relay7State);
    
      }if (serialInput == "relay8On") {
    digitalWrite(RELAY8_PIN, LOW);
    relay8State = 1;
    Serial.println("relay8On");
  }if (serialInput == "relay8Off") {
    digitalWrite(RELAY8_PIN, HIGH);
    relay8State = 0;
    Serial.println("relay8Off");
  }if (serialInput == "relay8State") {
    Serial.println(relay8State);
    
  }if (serialInput == "echo") {
    Serial.println("echo"); 
   
  }
  
}

