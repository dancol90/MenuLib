/*
    This item set a variable to a integer value in a range.
*/

#include <Arduino.h>


#include "MenuItem.h"

#ifndef NumericSelector_h
#define NumericSelector_h

class NumericSelector : public MenuItem {
    private:
        uint8_t& variable;
        uint8_t oldValue, min, max;


        char valueStr[5];
    public:
        NumericSelector(MenuItem* parent, const __FlashStringHelper* text, uint8_t& variable, uint8_t min, uint8_t max);

        uint8_t getValue();
        uint8_t getMin();
        uint8_t getMax();

        char getTypeId() { return 's'; };

        const char* getSecondaryText();

        bool activate();
        void deactivate();

        void doNext();
        void doPrev();

        MenuItem* action();
};

#endif