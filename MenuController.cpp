#include "MenuController.h"

void MenuController::takeControl(MenuItem* item) {
    if (!item) { return; }

    currentItem = item;

    currentItem->activate();

    exiting = 0;
}

MenuController::MenuController() {}
MenuController::MenuController(MenuItem* root, MenuItemDrawer* drawer) {
    // TODO: check if root is NULL and throw an error
    currentItem = root;
    this->drawer = drawer;
};


void MenuController::next() {
	if(exiting) exiting = 0;

    if(currentItem) 
        currentItem->doNext();
}

void MenuController::prev() {
	if(exiting) exiting = 0;
    
	if(currentItem)
        currentItem->doPrev();
}


void MenuController::select() {
    if(!currentItem) return;

    MenuItem* ret = currentItem->action();

    if (ret)
        takeControl(ret);
}

void MenuController::back() {
    if(!currentItem) return;
    
    currentItem->deactivate();

    if (currentItem->getParent())
        takeControl(currentItem->getParent());
    else
        exiting = 1;
}

void MenuController::draw() { drawer->draw(currentItem); }

int MenuController::canExit() { return exiting; }