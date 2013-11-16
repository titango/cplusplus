#include "headers.hpp"

Guard::Guard(std::string name,int x, int y, int sym, const TCODColor &color) :
    Character(name,x,y,sym,color)
{    
}

void Guard::automove()
{
    TCODRandom *ran = TCODRandom::getInstance();
    int moveCounter = ran->getInt(0,4);

    if(game->totalTime > 0.3)
    {
        if(moveCounter == 1)
        {
            if ( ! game->map->isWall(this->x-1,this->y)) { 
                this->x = this->x - 1;  
            }
        }else if(moveCounter == 2)
        {
            if ( ! game->map->isWall(this->x+1,this->y)) { 
                this->x = this->x + 1;  
            }
        }else if(moveCounter == 3)
        {
            if ( ! game->map->isWall(this->x,this->y+1)) { 
                this->y = this->y + 1;  
            }
        }else if(moveCounter == 4)
        {
            if ( ! game->map->isWall(this->x,this->y-1)) { 
                this->y = this->y - 1;  
            }
        }

        game->totalClockTick = 0;
    }
}
