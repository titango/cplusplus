#include "headers.hpp"

Guard::Guard(string name,int x, int y, int sym, const TCODColor &color) :
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

bool Guard::detectPlayer()
{
    if(abs(this->x - game->map->player->x) < 6 && 
            abs(this->y - game->map->player->y) < 6)
    {
        return true; 
    }

    return false;
}

void Guard::chasePlayer()
{
    if(game->totalTime > 0.3)
    {
        std::map<string,double> tempma;
        string label = "";
        tempma.insert(std::pair<string,double>(
                    "right",
                    (abs(this->x+1-game->map->player->x)*
                     abs(this->x+1-game->map->player->x)+
                     abs(this->y - game->map->player->y)*
                     abs(this->y - game->map->player->y)
                    )));
        tempma.insert(std::pair<string,double>(
                    "left",
                    (abs(this->x-1-game->map->player->x)*
                     abs(this->x-1-game->map->player->x)+
                     abs(this->y - game->map->player->y)*
                     abs(this->y - game->map->player->y)
                    )));
        tempma.insert(std::pair<string,double>(
                    "top",
                    (abs(this->y-1-game->map->player->y)*
                     abs(this->y-1-game->map->player->y)+
                     abs(this->x - game->map->player->x)*
                     abs(this->x - game->map->player->x)
                    )));
        tempma.insert(std::pair<string,double>(
                    "down",
                    (abs(this->y+1-game->map->player->y)*
                     abs(this->y+1-game->map->player->y)+
                     abs(this->x - game->map->player->x)*
                     abs(this->x - game->map->player->x)
                    )));

        double tempvalue = tempma.at("right");
        label = "right";

        for(std::map<string,double>::iterator it=tempma.begin();
                it != tempma.end(); ++it)
        {
            if(it->second < tempvalue) 
            {
                tempvalue = it->second;
                label = it->first;
            }
        }

        if(label.compare("top") == 0)
        {
            this->y--; 
        }else if(label.compare("down") == 0)
        {
            this->y++; 
        }else if(label.compare("left") == 0)
        {
            this->x--; 
        }else if(label.compare("right") == 0)
        {
            this->x++; 
        }
        game->totalClockTick = 0;

    }
}
