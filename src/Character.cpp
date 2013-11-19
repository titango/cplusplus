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
        //cout << "The player touches the guard!" << endl; 
        game->infopanel->message(TCODColor::red, "The player touch the guard");
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
        cout << "Not in\n";
        if(item->symbol == MONEY)
        {
            stringstream ss;
            ss << MONEY_POINT;
            string textmessage = "Player collects money and gain ";
            textmessage.append(ss.str());
            textmessage.append(" points");
            game->infopanel->message(TCODColor::green,
                    textmessage); 
        }else if(item->symbol == KEY)
        {  
            stringstream ss;
            ss << KEY_POINT;
            string textmessage = "Player collects key and gain ";
            textmessage.append(ss.str());
            textmessage.append(" points");
            game->infopanel->message(TCODColor::cyan,
                    textmessage); 
        }
        return true;
    }

    //this->x = x;
    //this->y = y;
    return false;
}
