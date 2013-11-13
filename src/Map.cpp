#include "headers.hpp"

Map::Map()
{
    fileread = new Filereader(this);
    string map = "map.txt";
    grounds = fileread->readFile(map);

    //setting walls
    for(int i = 0; i < width; i++)
    {
        for(int j = 0; j < height; j++) 
        {
            if(grounds[i][j].symbol == '#') 
            {
                setWall(i,j);
            }
        }
    }
}

Map::~Map()
{
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

void Map::generate() const
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

