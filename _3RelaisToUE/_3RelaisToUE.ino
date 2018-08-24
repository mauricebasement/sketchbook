#define POTENTIOMETER1 A1
#define POTENTIOMETER2 A2
#define POTENTIOMETER3 A3

void setup() {
  Serial.begin(9600);
  pinMode(POTENTIOMETER1,INPUT);
  pinMode(POTENTIOMETER2,INPUT);
  pinMode(POTENTIOMETER3,INPUT);
}

void loop() {
  Serial.print(getRotation(analogRead(POTENTIOMETER1)));
  Serial.print(getRotation(analogRead(POTENTIOMETER2)));
  Serial.println(getRotation(analogRead(POTENTIOMETER3)));
  delay(200);
}

int getRotation(int value) {
  if (value >= 768) {
    return 1;
  }  else if (value >= 512) {
    return 2;
  }  else if (value >= 256) {
    return 3;
  } else if (value >= 0) {
    return 4;
  }
}

