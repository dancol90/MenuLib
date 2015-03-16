/*
    This item execute an action when selected.
*/

#include <Arduino.h>

#include "MenuItem.h"

#ifndef Action_h
#define Action_h

class Action : public MenuItem {
    public:
        typedef void(*ActionCallback)(int);

        Action(MenuItem* parent, const __FlashStringHelper* text, ActionCallback callback = NULL, int data = 0);

        char getTypeId() { return 'a'; }

        void setCallback(ActionCallback callback); // Set the callback to execute.

        // MenuItem fields

        // When activated from parent menu, trigger the callback and don't take control.
        int activate();
        int deactivate() { return 0; };

        // These three methods do nothing. Since Action doesn't take control, they are never called.
        void doNext() { }
        void doPrev() { }
        MenuItem* action() { return NULL; }
    private:
        // callback pointer
        ActionCallback callback;

        int data;
};

#endif