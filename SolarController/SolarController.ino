#include <Wire.h>
int val10;
int val20;
int val11;
int val21;
int Relay = 2;

void setup()
{
  pinMode(Relay,OUTPUT);
  Serial.begin(9600);
  Serial.println("Voltage: ");
}
void loop()
{
      float temp0;
      float temp1;
      val10=analogRead(0);
      val11=analogRead(1);
      temp0=val10/4.092/10;
      temp1=val11/4.092/10;
      Serial.println("V1");
      Serial.println(temp0);
      Serial.println("V2");
      Serial.println(temp1);
      if (temp0 > temp1) {
        digitalWrite(Relay,HIGH);
      } else {
        digitalWrite(Relay,LOW);
      }    
      delay(1000);
}
