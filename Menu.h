/*
    This item contains other items.
*/

#include "MenuItem.h"

#include "NumericSelector.h"
#include "Action.h"
#include "CheckBox.h"

#ifndef Menu_h
#define Menu_h

struct ListEntry {
    ListEntry(MenuItem* i) : item(i) {
        next = NULL; prev = NULL;
    }

    ListEntry* next;
    ListEntry* prev;

    MenuItem* item; 
};

class Menu : public MenuItem {
    public:
        typedef void(*MenuEnterCallback)(Menu*);

        Menu(MenuItem* parent, const __FlashStringHelper* text, MenuEnterCallback enter_cb = NULL);

        char getTypeId() { return 'm'; }

        
        MenuItem* addItem(MenuItem* item);
        /*
        Menu*   addMenu(const char* text, MenuEnterCallback cb = NULL);
        Action* addAction(const char* text);
        NumericSelector* addSelector(const char* text, int& variable, int min, int max);
        CheckBox* addCheckBox(const char* text, short& variable);
        */

        ListEntry* getCollection() { return firstEntry; }
        MenuItem*  getSelectedItem() { return selectedItem->item; }

        ListEntry* getSelectedListEntry() { return selectedItem; }
        //void removeItem(int id) {}


        // MenuItem fields

        int activate();
        int deactivate() { return 1; }

        // Selects the next item in the list
        void doNext();
        // Selects the prev item in the list
        void doPrev();

        MenuItem* action();
        
    private:
        ListEntry *firstEntry, *lastEntry, *selectedItem;

        MenuEnterCallback enter_cb;

};

#endif