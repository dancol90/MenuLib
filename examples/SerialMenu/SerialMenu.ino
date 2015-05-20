#include <Wire.h>

#include <MenuLib.h>

#include <LightLCD.h>
#include <LcdDrawer.h>
#include <LightSSD1306.h>

LightSSD1306 lcd = LightSSD1306();

Menu* root = new Menu(NULL, NULL);
LcdDrawer* dr = new LcdDrawer(lcd);
MenuController* menu = new MenuController(root, dr);

  
uint8_t test = 1010;
char cmd;

void setup() {

  Serial.begin(9600);

  lcd.begin();
  lcd.setContrast(50);

  root->setText(F("Menu"));

  root->addItem(new Action(root, F("Do something"), NULL));
  Menu* sub = new Menu(root, F("Sub Menu"));
      sub->addItem(new Action(sub, F("Aaa"), NULL));
      sub->addItem(new Action(sub, F("bbb"), NULL));
      sub->addItem(new NumericSelector(sub, F("Test value"), test, 0, 1024));
      
      root->addItem(sub);
  
  menu->draw();
}

void loop() {
  if(Serial.available() > 0) {
    cmd = Serial.read();
    
    
    switch(cmd) {
        case 'w': menu->prev(); break;
        case 's': menu->next(); break;
    
        case ' ': menu->select(); break;
        case 'x': menu->back(); break;
    
        default: 
          Serial.print("Unknow command ");
          Serial.println(cmd);
    }
    
    menu->draw();
  }
}