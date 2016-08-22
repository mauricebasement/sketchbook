#define RELAY_PIN 2
#define SENSOR_PIN A0
#define COUNT 3600
#define DELAY 1000
#define SENSOR_TIMEOUT 10
#define MAX_PUMP 10000

int counter = 0;
int pumpCounter = 0;

void setup() {
  pinMode(RELAY_PIN,OUTPUT);
  pinMode(SENSOR_PIN,INPUT);
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
  pumpCounter=0;
  digitalWrite(RELAY_PIN,LOW);
  while (checkSensor() == false) {
    delay(100);
    pumpCounter++;
    if(pumpCounter >= MAX_PUMP) {
      digitalWrite(RELAY_PIN,HIGH);
      //error message; sensor timeout!
    }
     
  }
  digitalWrite(RELAY_PIN,HIGH);
  if(pumpCounter <= SENSOR_TIMEOUT) {
    //error message; sensor shorted!
  }
  pumpCounter=0;
  }
}

