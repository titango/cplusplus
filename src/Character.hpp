#ifndef _CHARACTER_H
#define _CHARACTER_H

class Character
{

    public:
        float x,y; // position on map
        float originalx,originaly; //original positions of x and y
        int symbol; // symbol on map like '@', 'O'
        string name; // Name of character

        TCODColor color; // color on map

        Character(std::string name, int x, int y, 
                int sym, const TCODColor &color);
        void generate() const;
        bool interactCharacter(Character *cha);
        bool interactItem(Item *item);

};
#endif
