/* Some headings */ 

#include "MenuItem.h"

#ifndef MenuItemDrawer_h
#define MenuItemDrawer_h

//  Abstract class

class MenuItemDrawer {
    public:
        virtual void draw(MenuItem* item) = 0;
};

#endif