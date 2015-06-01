#include "NumericSelector.h"

NumericSelector::NumericSelector(MenuItem* parent, const FlashString* text, uint8_t& variable, uint8_t min, uint8_t max, NumberSelectedCallback callback) : MenuItem(parent, text), variable(variable) {
    this->min = min;
    this->max = max;

    this->callback = callback;

    oldValue = variable;
};

uint8_t NumericSelector::getValue() { return variable; }
uint8_t NumericSelector::getMin()   { return min; }
uint8_t NumericSelector::getMax()   { return max; }

const char* NumericSelector::getSecondaryText() {
    snprintf_P(valueStr, 5, PSTR("<%d>"), variable);

    return valueStr;
}

bool NumericSelector::activate() {
    oldValue = variable;

    return 1;
}

void NumericSelector::deactivate() {
    variable = oldValue;

    // On cancel restore the value
    if (this->callback)
        this->callback(false);
}

void NumericSelector::doNext() {
    if(variable == this->max)
        variable = this->min;
    else
        variable++;

    if (this->callback)
        this->callback(false);

}
void NumericSelector::doPrev() {
    if(variable == this->min)
        variable = this->max;
    else
        variable--;

    if (this->callback)
        this->callback(false);
}

MenuItem* NumericSelector::action() {
    if (this->callback)
        this->callback(true);

    return this->getParent(); 
}