#include <UTFT.h>

extern uint8_t SmallFont[];

UTFT myGLCD(ILI9327_8,A2,A1,A3,A4); //3.5" TFTLCD for arduino 2560 from mcufriend.com on UNO

void setup()
{
  randomSeed(analogRead(0));
  pinMode(A0, INPUT_PULLUP);
  
// Setup the LCD
  myGLCD.InitLCD();
  myGLCD.setFont(SmallFont);
  int buf[398];
  int x, x2;
  int y, y2;
  int r;
  myGLCD.show_color_bar();
  myGLCD.clrScr();
}

void loop()
{
  drawFrame();
  drawCrosshairs();
}

void drawFrame() {
  myGLCD.setColor(255, 0, 0);
  myGLCD.fillRect(0, 0, 399, 13);
  myGLCD.setColor(64, 64, 64);
  myGLCD.fillRect(0, 226, 399, 239);
  myGLCD.setColor(255, 255, 255);
  myGLCD.setBackColor(255, 0, 0);
  myGLCD.print("*** Marc hat einen kleinen Penis ***", CENTER, 1);
  myGLCD.setBackColor(64, 64, 64);
  myGLCD.setColor(255,255,0);
  
  myGLCD.setColor(0, 0, 255);
  myGLCD.drawRect(0, 14, 399, 225);
}
void drawCrosshairs() {
    myGLCD.setColor(0, 0, 255);
  myGLCD.setBackColor(0, 0, 0);
  myGLCD.drawLine(199, 15, 199, 224);
  myGLCD.drawLine(1, 119, 398, 119);
  for (int i=9; i<390; i+=10)
    myGLCD.drawLine(i, 117, i, 121);
  for (int i=19; i<220; i+=10)
    myGLCD.drawLine(197, i, 201, i);
}
