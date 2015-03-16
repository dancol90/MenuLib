#include "CheckBox.h"

CheckBox::CheckBox(MenuItem* parent, const __FlashStringHelper* text, short& variable) : MenuItem(parent, text), value(variable) {}

int CheckBox::activate() { 
	// Don't use the xor or the not method to avoid strange things if
	// the variable changes outside the menu.
	value = value ? 0 : 1;

    Serial.print("CheckBox checked: ");
    Serial.println(this->getText());

    return 0;
}

const char* CheckBox::getSecondaryText() {
	return value ? "On" : "Off";
}