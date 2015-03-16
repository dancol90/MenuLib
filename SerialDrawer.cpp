#include <Arduino.h>

#include "SerialDrawer.h"

void SerialDrawer::drawMenu(Menu* menu) {
    Serial.print("Menu: ");
    Serial.println(menu->getText());

    ListEntry* e = menu->getCollection();

    if(!e)
        Serial.println("  No sub-items");
    else
        while(e) {
            if(e->item == menu->getSelectedItem())
                Serial.print("   ->");
            else
                Serial.print("     ");

            Serial.print(e->item->getText());

            if(e->item->getSecondaryText()) {
                Serial.print(" | ");
                Serial.print(e->item->getSecondaryText());
            }

            Serial.println();

            e = e->next;
        }
}

void SerialDrawer::drawAction(Action* action) {
    Serial.print("Action: ");
    Serial.println(action->getText());
}

void SerialDrawer::drawSelector(NumericSelector* selector) {
    Serial.print("Selector: ");
    Serial.print(selector->getText());
    Serial.print(" <");
    Serial.print(selector->getValue());
    Serial.println(">");
}

void SerialDrawer::draw(MenuItem* item) {
    if(!item) return;

    switch(item->getTypeId()) {
        case 'm':
            drawMenu((Menu*)item);
            break;

        case 'a':                
            drawAction((Action*)item);
            break;

        case 's':
            drawSelector((NumericSelector*)item);
            break;
    }
}