#include "Menu.h"

Menu::Menu(MenuItem* parent, const FlashString* text, MenuEnterCallback enter_cb) : MenuItem(parent, text) {
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

void Menu::clearItems() {
    ListEntry* e = this->firstEntry;
    ListEntry* next;

    while(e) {
        next = e->next;

        delete e;

        e = next;
    }

    this->firstEntry = NULL;
    this->lastEntry  = NULL;
}

bool Menu::activate() {
    if (this->enter_cb)
        this->enter_cb(this);

    // Select the first item when entering the menu
    selectedItem = lastEntry;

    // And jump to the next. If firstElement is enabled, it will stop there,
    // otherwise it will find the first enabled item.
    doNext();
}

void Menu::doNext() {
    // TODO: infinite loop if all entries are disabled??
    do {

        selectedItem = selectedItem->next;

        if(!selectedItem) selectedItem = firstEntry;

    } while(!selectedItem->item->isEnabled());
}

void Menu::doPrev() {
    // TODO: infinite loop if all entries are disabled??
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