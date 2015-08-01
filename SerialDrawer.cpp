#include <Arduino.h>

#include "SerialDrawer.h"

void SerialDrawer::drawMenu(Menu* menu) {
    Serial.print(F("Menu: "));
    Serial.println(menu->getText());

    ListEntry* e = menu->getCollection();

    if(!e)
        Serial.println(F("  No sub-items"));
    else
        while(e) {
            if(e->item == menu->getSelectedItem())
                Serial.print(F("   ->"));
            else
                Serial.print(F("     "));

            if (e->item->isTextFlash()) {
                const FlashString* text = reinterpret_cast<const FlashString*>(e->item->getText());
                Serial.print(text);
            } else {
                const char* text = e->item->getText();
                Serial.print(text);
            }

            if(e->item->getSecondaryText()) {
                Serial.print(F(" | "));
                Serial.print(e->item->getSecondaryText());
            }

            Serial.println();

            e = e->next;
        }
}

/*void SerialDrawer::drawAction(Action* action) {
    Serial.print(F("Action: "));
    Serial.println(action->getText());
}*/

void SerialDrawer::drawSelector(NumericSelector* selector) {
    Serial.print(F("Selector: "));
    Serial.print(selector->getText());
    Serial.print(F(" <"));
    Serial.print(selector->getValue());
    Serial.println(F(">"));
}

void SerialDrawer::draw(MenuItem* item) {
    if(!item) return;

    switch(item->getTypeId()) {
        case 'm':
            drawMenu((Menu*)item);
            break;

        /*case 'a':                
            drawAction((Action*)item);
            break;
        */
        case 's':
            drawSelector((NumericSelector*)item);
            break;
    }
}