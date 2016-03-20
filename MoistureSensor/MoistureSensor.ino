#include <MoistureSensor.h>

MoistureSensor probe(2,3,0);

void setup() {
  Serial.begin(9600);
  Serial.println("Moisture Probe Example");
}

void loop() {
  probe.setCurrent(false);
  int moisture = probe.checkMoisture() / 10.24;
  delay(1000);
  probe.setCurrent(true);
  moisture += (1023 - probe.checkMoisture() ) / 10.24;
  moisture /= 2;
  Serial.println(moisture);
  delay(1000);
  probe.sleep();
  delay(1000);
}
