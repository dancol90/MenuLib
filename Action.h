/*
    This item execute an action when selected.
*/

#include <Arduino.h>

#include "MenuItem.h"

#ifndef Action_h
#define Action_h

template <class T> class Action : public MenuItem {
    public:
        typedef void(*ActionCallback)(T);

        Action(MenuItem* parent, const __FlashStringHelper* text, ActionCallback callback, T data): MenuItem(parent, text) {
            setCallback(callback);

            this->data = data;
        }

        char getTypeId() { return 'a'; }

        // Set the callback to execute.
        void setCallback(ActionCallback callback) { this->callback = callback; }

        // MenuItem fields

        // When activated from parent menu, trigger the callback and don't take control.
        int activate() { 
            if (this->callback)
                this->callback(this->data);

            return 0;
        }
        int deactivate() { return 0; };

        // These three methods do nothing. Since Action doesn't take control, they are never called.
        void doNext() { }
        void doPrev() { }
        MenuItem* action() { return NULL; }
    protected:
        // callback pointer
        ActionCallback callback;

        T data;
};

#endif