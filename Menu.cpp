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

bool Menu::activate() {
    if (this->enter_cb)
        this->enter_cb(this);

    // Select the first item when entering the menu
    selectedItem = firstEntry;
}

void Menu::doNext() {
    do {

        selectedItem = selectedItem->next;

        if(!selectedItem) selectedItem = firstEntry;

    } while(!selectedItem->item->isEnabled());
}

void Menu::doPrev() {
    do {
        
        selectedItem = selectedItem->prev;

        if(!selectedItem) selectedItem = lastEntry;

    } while(!selectedItem->item->isEnabled());
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