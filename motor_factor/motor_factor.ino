#include <ArduinoRobot.h> // import the robot library

void setup(){
  Robot.begin();
  Robot.beginTFT();
}

void loop(){
  int val=map(Robot.knobRead(),0,1023,-255,255);
  Robot.motorsWrite(val,val/1.4);
  delay(10);
  Robot.debugPrint(val);
}
