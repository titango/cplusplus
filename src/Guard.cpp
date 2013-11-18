#include "headers.hpp"

Guard::Guard(string name,int x, int y, int sym, const TCODColor &color) :
    Character(name,x,y,sym,color), alertedGuard(0)
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
        std::vector<int> coorx;
        std::vector<int> coory;
        std::vector<string> posi;
        string label = "";

        //Left
        coorx.push_back(this->x-1);
        coory.push_back(this->y);

        //Top
        coorx.push_back(this->x);
        coory.push_back(this->y-1);

        //Right
        coorx.push_back(this->x+1);
        coory.push_back(this->y);

        //Down
        coorx.push_back(this->x);
        coory.push_back(this->y+1);

        //Top-left
        coorx.push_back(this->x-1);
        coory.push_back(this->y-1);

        //Top-right
        coorx.push_back(this->x+1);
        coory.push_back(this->y-1);

        //Down-left
        coorx.push_back(this->x-1);
        coory.push_back(this->y+1);

        //Down-right
        coorx.push_back(this->x+1);
        coory.push_back(this->y+1);

        //Position
        posi.push_back("left");
        posi.push_back("top");
        posi.push_back("right");
        posi.push_back("down");
        posi.push_back("topleft");
        posi.push_back("topright");
        posi.push_back("downleft");
        posi.push_back("downright");

        for(int i = 0; i < coorx.size(); i++)
        {
            tempma.insert(std::pair<string,double>(
                        posi.at(i),
                        (abs(coorx.at(i) - game->map->player->x)*
                         abs(coorx.at(i) - game->map->player->x)+
                         abs(coory.at(i) - game->map->player->y)*
                         abs(coory.at(i) - game->map->player->y)
                        ))); 
        }

        double tempvalue = tempma.at("left");
        label = "left";

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
            if ( ! game->map->isWall(this->x,this->y-1)) {
                this->y--; 
            }
        }else if(label.compare("down") == 0)
        {
            if ( ! game->map->isWall(this->x,this->y+1)) {
                this->y++; 
            }
        }else if(label.compare("left") == 0)
        {
            if ( ! game->map->isWall(this->x-1,this->y)) {
                this->x--; 
            }
        }else if(label.compare("right") == 0)
        {
            if ( ! game->map->isWall(this->x+1,this->y)) {
                this->x++; 
            }
        }else if(label.compare("topleft") == 0)
        {
            if ( ! game->map->isWall(this->x-1,this->y-1)) {
                this->x--; 
                this->y--;
            }
        }else if(label.compare("topright") == 0)
        {
            if ( ! game->map->isWall(this->x+1,this->y-1)) {
                this->x++; 
                this->y--;
            }
        }else if(label.compare("downleft") == 0)
        {
            if ( ! game->map->isWall(this->x-1,this->y+1)) {
                this->x--; 
                this->y++;
            }
        }else if(label.compare("downright") == 0)
        {
            if ( ! game->map->isWall(this->x+1,this->y+1)) {
                this->x++; 
                this->y++;
            }
        }
        game->totalClockTick = 0;

    }
}
