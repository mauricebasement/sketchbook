#define trigPin 13
#define echoPin 12
#define relay 2
#define relay2 3
#define DISTANCE 20

void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(relay, OUTPUT);
  pinMode(relay2, OUTPUT);
}

void loop() {
  long duration, distance;
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  
  if (distance > DISTANCE) {  // This is where the relay On/Off happens
    digitalWrite(relay,HIGH); 
    digitalWrite(relay2,HIGH);
  }
  else {
    digitalWrite(relay,LOW);
    digitalWrite(relay2,LOW);
  }
  
  if (distance >= 200 || distance <= 0){
    Serial.println("Out of range");
  }
  else {
    Serial.print(distance);
    Serial.println(" cm");
  }
  delay(500);
} 
