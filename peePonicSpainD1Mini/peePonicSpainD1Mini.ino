#define FLOODING 8
#define WAITING 30
#define PUMP1 D2
#define PUMP2 D3

void setup() {
  pinMode(PUMP1, OUTPUT);
  pinMode(PUMP2, OUTPUT);
}

void loop() {
  pumpOn();
  wait(FLOODING);
  //delay(1000);
  pumpOff();
  wait(WAITING);
  //delay(1000);
}

void wait(int minutes) {
  minutes = minutes * 60000;
  delay(minutes);
}

void pumpOn() {
  digitalWrite(PUMP1, 1);
  digitalWrite(PUMP2, 1);
}

void pumpOff() {
  digitalWrite(PUMP1, 0);
  digitalWrite(PUMP2, 0);
}
