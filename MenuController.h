/*
    Implementation of Menu controller.
*/


#include "NumericSelector.h"
#include "Action.h"
#include "Menu.h"

#include "SerialDrawer.h"

#ifndef MenuController_h
#define MenuController_h

class MenuController {
    private:
        MenuItem* currentItem;
        MenuItemDrawer* drawer;

        int exiting;


    public:
        MenuController();
        MenuController(MenuItem* root, MenuItemDrawer* drawer);

        void next();
        void prev();

        void select();
        void back();

        void draw();

        int canExit();

        void takeControl(MenuItem* item);
};

#endif