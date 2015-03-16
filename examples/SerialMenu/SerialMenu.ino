#include <MenuLib.h>
#include <NokiaLcdDrawer.h>
#include <LightPCD8544.h>

#include <SPI.h>

LightPCD8544 lcd = LightPCD8544(9, 10);

Menu* root = new Menu(NULL, "Menu 1");
NokiaLcdDrawer* dr = new NokiaLcdDrawer(lcd);
MenuController* menu = new MenuController(root, dr);

  
int test = 1010;
char cmd;

void setup() {

  Serial.begin(9600);

  lcd.begin();
  lcd.setContrast(50);

  root->addAction("Do something");
  Menu* sub = root->addMenu("Sub Menu");
      sub->addAction("Aaa");
      sub->addAction("bbb");
      sub->addSelector("Test value", test, 0, 1024);
  
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
