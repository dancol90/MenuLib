#include "Menu.h"

Menu::Menu(MenuItem* parent, const __FlashStringHelper* text, MenuEnterCallback enter_cb) : MenuItem(parent, text) {
    this->firstEntry = NULL;
    this->lastEntry = NULL;

    this->enter_cb = enter_cb;
};

MenuItem* Menu::addItem(MenuItem* item) {
    ListEntry* e = new ListEntry(item);

    if(firstEntry) {
        lastEntry->next = e;
        e->prev = lastEntry;
    } else
        firstEntry = e;

    lastEntry = e;

    selectedItem = firstEntry;

    return item;
}

/*
Menu* Menu::addMenu(const char* text, MenuEnterCallback cb) {
    return (Menu*)addItem(new Menu(this, text, cb));
}

Action* Menu::addAction(const char* text) {
    return (Action*)addItem(new Action(this, text));
}

CheckBox* Menu::addCheckBox(const char* text, short& variable) {
    return (CheckBox*)addItem(new CheckBox(this, text, variable));
}

NumericSelector* Menu::addSelector(const char* text, int& variable, int min, int max) {
    return (NumericSelector*)addItem(new NumericSelector(this, text, variable, min, max));
}
*/

int Menu::activate() {
    if (this->enter_cb)
        this->enter_cb(this);

    // Select the first item when entering the menu
    selectedItem = firstEntry;
}

void Menu::doNext() { 
    selectedItem = selectedItem->next;

    if(!selectedItem) 
        selectedItem = firstEntry;
}

void Menu::doPrev() {
    selectedItem = selectedItem->prev;

    if(!selectedItem)
        selectedItem = lastEntry;
}


MenuItem* Menu::action() {
    // Let's the Item do something to start
    int takeControl = selectedItem->item->activate();

    // Then let it take control, or maintain it.
    if(takeControl)
        return selectedItem->item;
    else
        return NULL;
}