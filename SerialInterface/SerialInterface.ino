//Interface to set and read pins of an arduino via serial interface

//Variables
int command = 0;
int pinNumber;
int pinState;
int pinValue;
String getInput;

//Settings
#define BAUDRATE 9600

//Setup Serial Connection
//how to take pinmode setting in account?
//-can it be made during setup only?
//or when a pin is used for the first time?

void setup() {
  Serial.begin(BAUDRATE);
  Serial.println("Hello there");
}

//Wait for Message on Serial Connection and act accordingly
void loop() {
  
  //Get and parse Input
    command = Serial.parseInt();
    Serial.println(command);
    pinNumber = Serial.parseInt();    
    if (Serial.read() != '\n') {
      if (Serial.read() == 'v') {  
        pinValue = Serial.parseInt();
      }
      if (Serial.read() == 's') {
        pinState = Serial.parseInt();
      }
    }
 
  //Act accordingly
  if (command == 0) {
    Serial.println("Reached command 0");
    setDigitalPin(pinNumber, pinState);   
  }
  if (command == 1) {
    Serial.println("Reached command 1");
    Serial.println(getDigitalPin(pinNumber));
  }
  if (command == 2) {
    Serial.println("Reached command 2");
    setAnalogPin(pinNumber, pinValue);
  }
  if (command == 3) {
    Serial.println("Reached command 3");
    Serial.println(getAnalogPin(pinNumber));
  }
  command = 4;
}

//Setter / Getter for Digital resp. Analog Pins
void setDigitalPin(int pinNr, boolean state) {
  if (state == true) {
    digitalWrite(pinNr, HIGH);
  }
  if (state == false) {
    digitalWrite(pinNr, HIGH);
  }
}

boolean getDigitalPin(int pinNr) {
  boolean tmpState = digitalRead(pinNr);
  if (tmpState = HIGH) {
    return true;
  }
  if (tmpState = LOW) {
    return false;
  }
}

void setAnalogPin(int pinNr, int value) {
  analogWrite(pinNr, value);
}

int getAnalogPin(int pinNr) {
  return analogRead(pinNr);
}
