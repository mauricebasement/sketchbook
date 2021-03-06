//Interface to set and read pins of an arduino via serial interface

//Variables
String command;
int pinNumber;
boolean pinState;
String getInput;

//Settings
#define BAUDRATE 250000

//Setup Serial Connection
void setup() {
  while(!Serial) {
    Serial.begin(BAUDRATE);
  }
  Serial.println("Arduino Serial Interface V.2");
}

//Wait for Message on Serial Connection and act accordingly
void loop() {
  //Get and parse Input
  getInput = Serial.readString();
  //Parse String for command and pinNumber
  command = getValue(getInput,':',0);
  pinNumber = getValue(getInput,':',1).toInt();
 
  //Act accordingly
  if (command == "sdp") {
    Serial.println("sdp");
    pinMode(pinNumber, OUTPUT);
    String tmp = getValue(getInput, ':', 2);
    if (tmp == "H") {
      pinState = true;
    } if (tmp == "L") {
      pinState = false;
    } else { 
      error();
    }
    setDigitalPin(pinNumber, pinState);   
  }
  if (command == "gdp") {
    pinMode(pinNumber, INPUT);
    Serial.println("gdp");
    Serial.println(getDigitalPin(pinNumber));
  }
  if (command == "sap") {
    Serial.println("sap");
    int pinValue = getValue(getInput, ':', 2).toInt();
    setAnalogPin(pinNumber, pinValue);
  }
  if (command == "gap") {
    Serial.println("gap");
    Serial.println(getAnalogPin(pinNumber));
  }
}

//Setter / Getter for Digital resp. Analog Pins
void setDigitalPin(int pinNr, boolean state) {
  digitalWrite(pinNr, state);
}

boolean getDigitalPin(int pinNr) {
  return  digitalRead(pinNr);
}

void setAnalogPin(int pinNr, int value) {
  analogWrite(pinNr, value);
}

int getAnalogPin(int pinNr) {
  return analogRead(pinNr);
}

//Parsing string by seperator method
String getValue(String data, char seperator, int index) {
  int found = 0;
  int strIndex[] = { 0, -1 };
  int maxIndex = data.length() -1;

  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (data.charAt(i) == seperator || i == maxIndex) {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  }
  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
void error() {
  Serial.println("An error occured");
}
