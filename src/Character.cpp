#include "headers.hpp"

Character::Character(int x, int y, int sym, const TCODColor &color) :
    x(x),y(y),symbol(sym),color(color)
{    
}

void Character::generate() const {
    TCODConsole::root->setChar(x,y,symbol);
    TCODConsole::root->setCharForeground(x,y,color);
}
