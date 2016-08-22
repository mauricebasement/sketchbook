#define RELAY_PIN 2
#define SENSOR_PIN A0
#define COUNT 3600
#define DELAY 1000

int counter = 0;

void setup() {
  pinMode(RELAY_PIN,OUTPUT);
  pinMode(SENSOR_PIN,INPUT);
  pinMode(13,OUTPUT);
  digitalWrite(RELAY_PIN,HIGH);
  flooding();
}

void loop() {
  if (counter==COUNT) {
    counter = 0;
    flooding();
  } else {
    counter++;
  }
  delay(DELAY);
}

boolean checkSensor() {
  int sensor = analogRead(SENSOR_PIN);
  Serial.println(sensor);
  if(sensor>200) {
    return true;
  } else {
    return false;
  }
}

void flooding() {
  digitalWrite(RELAY_PIN,LOW);
  while (checkSensor() == false) {
    digitalWrite(13,HIGH);
    delay(100);
    digitalWrite(13,LOW);
  }
  digitalWrite(RELAY_PIN,HIGH);
}

