#define relayPin 4
#define switchPin 3
#define readPin 1

boolean on = true;
boolean state = true;
int debounce1 = 0;
int debounce2 = 0;
int debounceLimit = 10;

void setup() {
  //Serial.begin(9600);
  pinMode(relayPin, OUTPUT);
  pinMode(switchPin, OUTPUT);
}

void loop() {
  digitalWrite(relayPin, LOW);
  on = checkClock();
  if (on == true) {
    if(debounce1 >= debounceLimit) {
      debounceReset();
      switch1();
    }else {
      debounce1 += 1;
    }
  } else {
    if(debounce2 >= debounceLimit) {
      debounceReset();
      switch2();
    }else {
      debounce2 += 1;
    }
  }
  if (debounce1+debounce2 >= debounceLimit*1.5) {
    debounceReset();
  }
  delay(1000);
}

boolean checkClock() {
  //Serial.println(analogRead(readPin));
  if (analogRead(readPin) <= 600) {
    return false;
  } else {
    return true;
  }
  
}

void switch1() {
  if (state != on) {
  digitalWrite(relayPin, HIGH);
  delay(1000);
  digitalWrite(switchPin, LOW);
  delay(1000);
  state = true;
  }
}
  
void switch2() { 
  if (state != on) {
  digitalWrite(relayPin, HIGH);
  delay(1000);
  digitalWrite(switchPin, HIGH);
  delay(1000);
  state = false;
  }
} 
 
void debounceReset() {
      debounce1 = 0;
      debounce2 = 0;
}
