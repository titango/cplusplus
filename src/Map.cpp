#include "headers.hpp"

Map::Map(string mapname)
{
    fileread = new Filereader(this);
    grounds = fileread->readFile(mapname);

    //setting all
    componentRendering();
}

Map::~Map()
{
    characters.clearAndDelete();
    delete [] grounds;
}

bool Map::isWall(int x, int y) const
{
   return !grounds[x][y].canWalk;
}

void Map::setWall(int x, int y)
{
    grounds[x][y].canWalk = false;
}

void Map::generate()
{
    static const TCODColor Wall = TCODColor::darkBlue;
    static const TCODColor darkGround = TCODColor::darkerGrey;

    for(int x = 0; x < width; x++)
    {
        for(int y = 0; y < height;y++)
        {
            TCODConsole::root->setCharBackground(x,y,
                    isWall(x,y) ? Wall : darkGround) ;
        }
    }
}

void Map::componentRendering()
{
    for(int i = 0; i < width; i++)
    {
        for(int j = 0; j < height; j++) 
        {
            //setting walls
            if(grounds[i][j].symbol == '#') 
            {
                setWall(i,j);
            }
            //setting characters
            else if(grounds[i][j].symbol == 'O')
            { 
                player = new Character(i,j,'O', TCODColor::white);
                characters.push(player);
            }else if(grounds[i][j].symbol == 'X')
            {
                Character *guard = new Guard(i,j,'X',TCODColor::yellow);
                characters.push(guard);
            }
            
        }
    }
}
