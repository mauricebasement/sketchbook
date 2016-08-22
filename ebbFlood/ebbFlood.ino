#define RELAY_PIN 2
#define SENSOR_PIN A0
#define COUNT 21600
#define DELAY 1000

int counter = 0;

void setup() {
  Serial.begin(115200); //debugging
  pinMode(RELAY_PIN,OUTPUT);
  pinMode(SENSOR_PIN,INPUT);
  digitalWrite(RELAY_PIN,HIGH);
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
    Serial.println("Flooding");
  }
  digitalWrite(RELAY_PIN,HIGH);
}

