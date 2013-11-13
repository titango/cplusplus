#include "libtcod.hpp"
#include "Map.hpp"

Map::Map()
{
    //2d array for grounds
    //grounds = new Ground*[width];
    //for(int i = 0; i < width; i++)
    //{
        //grounds[i] = new Ground[height];
    //}
    fileread = new Filereader();
    string map = "map.txt";
    grounds = fileread->readFile(map);
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

