void setup() {
  pinMode(7,OUTPUT);
}

void loop() {
  for(int i = 500; i<2000; i++) {
    tone(7, i, 50);
  }
  for(int i = 2000; i>500; i--) {
    tone(7, i, 50);
  }
}
