#include "headers.hpp"

Character::Character(std::string name,int x, int y, int sym, 
        const TCODColor &color) :
    name(name),x(x),y(y),originalx(x),originaly(y),symbol(sym),color(color)
{    
}

void Character::generate() const {
    TCODConsole::root->setChar(x,y,symbol);
    TCODConsole::root->setCharForeground(x,y,color);
}

bool Character::interactCharacter(Character *cha)
{
    if(this->x == cha->x && this->y == cha->y) 
    {
        cout << "The player touches the guard!" << endl; 
        return true;
    }

    //this->x = x;
    //this->y = y;
    return false;
}

bool Character::interactItem(Item *item)
{
    if(this->x == item->x && this->y == item->y) 
    {
        cout << "The player touches the item!" << endl; 
        return true;
    }

    //this->x = x;
    //this->y = y;
    return false;
}
