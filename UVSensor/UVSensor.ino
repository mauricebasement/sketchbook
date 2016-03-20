int in = 0;

void setup() {
  pinMode(in,INPUT);
  Serial.begin(9600);
}
void loop() {
  Serial.println(analogRead(in));
  delay(1000);
}
