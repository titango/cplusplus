#include "headers.hpp"

Item::Item(std::string name, int x, int y, int sym, const TCODColor &color) :
    name(name),x(x),y(y),originalx(x),originaly(y),symbol(sym),color(color)
{    
}

void Item::generate() const {
    TCODConsole::root->setChar(x,y,symbol);
    TCODConsole::root->setCharForeground(x,y,color);
}
