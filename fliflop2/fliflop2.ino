#include <Wire.h>
#include <Time.h>
#include <DS1307RTC.h>

#define switchPin 3
#define relayPin 4
#define misc1Pin 5
#define misc2Pin 6

boolean state = true;
boolean on = true;

void setup() {
  Serial.begin(9600);
  pinMode(relayPin, OUTPUT);
  pinMode(switchPin, OUTPUT);
  pinMode(misc1Pin, OUTPUT);
  pinMode(misc2Pin, OUTPUT);
  digitalWrite(relayPin, LOW);
  digitalWrite(switchPin, LOW);
  digitalWrite(misc1Pin, LOW);
  digitalWrite(misc2Pin, LOW);
}

void loop() {  
  tmElements_t tm;
  RTC.read(tm);
  Serial.println(tm.Hour);
  on = checkClock(tm.Hour);
  if(on==true) { switch1();
  }else{ switch2(); }
  delay(1000);  
}

boolean checkClock(int t) {
  if(t<19 && t>6) return false;
  return true;
}

void switch1() {
  if (state != on) {
  digitalWrite(relayPin, HIGH);
  delay(1000);
  digitalWrite(switchPin, LOW);
  digitalWrite(misc1Pin, LOW);
  digitalWrite(misc2Pin, LOW);
  delay(1000);
  state = true;
  digitalWrite(relayPin, LOW);
  }
}
  
void switch2() { 
  if (state != on) {
  digitalWrite(relayPin, HIGH);
  delay(1000);
  digitalWrite(switchPin, HIGH);
  digitalWrite(misc1Pin, HIGH);
  digitalWrite(misc2Pin, HIGH);
  delay(1000);
  state = false;
  digitalWrite(relayPin, LOW);
  }
} 
