#ifndef _ITEM_H
#define _ITEM_H

#include <string>

using namespace std;
class Item
{

    public:
        string name;
        int x,y; // position on map
        int originalx,originaly; //original positions of x and y
        int symbol; // symbol on map like '@', 'O'

        TCODColor color; // color on map

        Item(string name,int x, int y, int sym, const TCODColor &color);
        void generate() const;

};

#endif
