#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

int entry = 0;
int entries = 4;
int menu = 0;
String menuEntries[4] = {"entry 1","entry 2","entry 3","entry 4"};

void setup() {
  lcd.begin(16, 2);
}
void loop() {
  doKey(keyPad(analogRead(0)));
  displayMenu(entry);
}
int keyPad(int input) {
  if (verifyKeyPad(input,0)) {
    return 1;
  } if (verifyKeyPad(input,131)) {
    return 2;
  } if (verifyKeyPad(input,309)) {
    return 3;
  } if (verifyKeyPad(input,481)) {
    return 4;
  } if (verifyKeyPad(input,722)) {
    return 5;
  } else {
    return 0;
  }
}
void doKey(int key) {
  switch (key) {
  case 1:
    lcd.setCursor(0,1);
    lcd.print("Right");
  break;
  case 2:
    up();
  break;
  case 3:
    down();
  break;
  case 4:
    lcd.setCursor(0,1);
    lcd.print("Left");
  break;
  case 5:
    lcd.setCursor(0,1);
    lcd.print("Select");
  break;
  default:
  break;
  }
}
boolean verifyKeyPad(int input, int compare) {
  int range = 5;
  if (input >= compare-range && input <= compare+range) {
    return true;
  }else{
    return false;
  }
}
void displayMenu(int input) {
  lcd.setCursor(0,0);
  lcd.print(menuEntries[input]);
}
void up() {
  if (entry < entries-1) {  entry += 1; }
  buttonDelay();
}
void down() {
  if (entry > 0) {  entry -= 1; }
  buttonDelay();
}
void buttonDelay() {
  delay(200);
}



