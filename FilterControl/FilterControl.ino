#include <Event.h>
#include <Timer.h>

Timer t;

const int led = 13;
const int waterPump = 3;
const int dosagePump = 4;
const int sensorPin = A0;

int sense = 0;

void setup(){
  Serial.begin(9600);
  //pinMode(buzzer, OUTPUT); // Set buzzer - pin 9 as an output
  pinMode(led, OUTPUT);
  pinMode(waterPump, OUTPUT);
  pinMode(dosagePump, OUTPUT);
  pinMode(sensorPin, INPUT);
  //t.oscillate(dosagePump, 100000, LOW);
  t.every(30000, t.pulse(dosagePump, 5000, HIGH)); 
}
void loop() {
  
  updatePump();
  t.update();
}
boolean senseWater() {
  //Read Pin
  if (analogRead(sensorPin) < 100) {
    sense+=1;
  }else{
    sense-=1;
  }
  //Check Borders
  sense = min(sense , 10000);
  sense = max(sense , 0);
  //Return Boolean
  if (sense >= 10000) {
    return true;
  } else {
    return false;
  }
}
void updatePump() {
  if (senseWater() == true) {
    digitalWrite(waterPump,LOW);
  } else { 
    digitalWrite(waterPump,HIGH);
  }
}
void buzzer() {
  tone(buzzer, 101); // Send 1KHz sound signal...
  delay(100);        // ...for 1 sec
  noTone(buzzer);     // Stop sound...
  delay(100);        // ...for 1sec
}
