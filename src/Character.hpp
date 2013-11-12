#ifndef _CHARACTER_H
#define _CHARACTER_H

class Character
{

    public:
        int x,y; // position on map
        int symbol; // symbol on map like '@', 'O'

        TCODColor color; // color on map

        Character(int x, int y, int sym, const TCODColor &color);
        void generate() const;

};
#endif
