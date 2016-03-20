int input = 11;
int output = 2;

void setup() {
 pinMode(input,INPUT);
 pinMode(output,OUTPUT);
 Serial.begin(9600);
 Serial.println("hello world");
}
void loop() {
  digitalWrite(output,digitalRead(input));
  Serial.println(digitalRead(input));
}
 

 
  
