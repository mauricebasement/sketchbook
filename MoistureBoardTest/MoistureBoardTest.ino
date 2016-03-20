void setup() {
  pinMode(2,INPUT);
  pinMode(A0,INPUT);
  Serial.begin(9600);
}

void loop() {
  Serial.println((1023-analogRead(A0))/10.24);
  Serial.println(digitalRead(2));
  delay(1000);
}
