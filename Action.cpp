#include "Action.h"

Action::Action(MenuItem* parent, const __FlashStringHelper* text, ActionCallback callback, int data) : MenuItem(parent, text) {
	setCallback(callback);

	this->data = data;
}

int Action::activate() { 
	if (this->callback)
    	this->callback(this->data);

    return 0;
}

void Action::setCallback(ActionCallback callback) {
    this->callback = callback;
}