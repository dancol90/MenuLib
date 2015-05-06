/*
    This item execute an action when selected.
*/

#include <Arduino.h>

#include "MenuItem.h"

#ifndef Action_h
#define Action_h

template <class T> class ParamAction : public MenuItem {
    public:
        typedef void(*ActionCallback)(T);

        ParamAction(MenuItem* parent, const FlashString* text, ActionCallback callback, T data): MenuItem(parent, text) {
            this->callback = callback;

            this->data = data;
        }

        char getTypeId() { return 'a'; }

        // MenuItem fields

        // When activated from parent menu, trigger the callback and don't take control.
        bool activate() { 
            if (this->callback)
                this->callback(this->data);

            return 0;
        }
        void deactivate() {};

        // These three methods do nothing. Since Action doesn't take control, they are never called.
        void doNext() { }
        void doPrev() { }
        MenuItem* action() { return NULL; }
    protected:
        // callback pointer
        ActionCallback callback;

        T data;
};

class Action : public MenuItem {
    public:
        typedef void(*ActionCallback)(void);

        Action(MenuItem* parent, const FlashString* text, ActionCallback callback): MenuItem(parent, text) {
            setCallback(callback);;
        }

        char getTypeId() { return 'a'; }

        // Set the callback to execute.
        void setCallback(ActionCallback callback) { this->callback = callback; }

        // MenuItem fields

        // When activated from parent menu, trigger the callback and don't take control.
        bool activate() { 
            if (this->callback)
                this->callback();

            return 0;
        }
        void deactivate() {};

        // These three methods do nothing. Since Action doesn't take control, they are never called.
        void doNext() { }
        void doPrev() { }
        MenuItem* action() { return NULL; }
    protected:
        // callback pointer
        ActionCallback callback;
};
#endif