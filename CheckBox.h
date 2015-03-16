/*
    This item represent a "Yes\No" or "On\Off" option.
*/

#include <Arduino.h>

#include "MenuItem.h"

#ifndef CheckBox_h
#define CheckBox_h

class CheckBox : public MenuItem {
    public:
        CheckBox(MenuItem* parent, const __FlashStringHelper* text, short& variable);

        char getTypeId() { return 'c'; }

        const char* getSecondaryText();

        // MenuItem fields

        // When activated from parent menu, trigger the callback and don't take control.
        int activate();
        int deactivate() { return 0; };

        // These three methods do nothing. Since CheckBox doesn't take control, they are never called.
        void doNext() { }
        void doPrev() { }
        MenuItem* action() { return NULL; }
    private:
        short& value;
        // callback pointer
};

#endif