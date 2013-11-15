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
    static const TCODColor Wall = TCODColor::darkerBlue;
    static const TCODColor blackGround = TCODColor::black;

    for(int x = 0; x < width; x++)
    {
        for(int y = 0; y < height;y++)
        {
            if( isWall(x,y))
            {
                TCODConsole::root->setCharBackground(x,y,blackGround); 
                TCODConsole::root->setCharForeground(x,y,Wall);
                TCODConsole::root->setChar(x,y,'#');
            }else 
            {
                TCODConsole::root->setCharBackground(x,y,blackGround); 
            }
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
                player = new Character("player",i,j,'O', TCODColor::white);
                characters.push(player);
            //setting guards
            }else if(grounds[i][j].symbol == 'X')
            {
                Character *guard = new Guard("guard",i,j,'X',TCODColor::yellow);
                characters.push(guard);
            //setting money
            }else if(grounds[i][j].symbol == '$')
            {
                Item *money = new Item("money",i,j,'$',TCODColor::green);
                items.push(money);
            //setting keys
            }else if(grounds[i][j].symbol == '+')
            {
                Item *key = new Item("key",i,j,'+',TCODColor::cyan);
                items.push(key);
            
            //setting lock
            }else if(grounds[i][j].symbol == '\\')
            {
                Item *lock = new Item("lock",i,j,'\\',TCODColor::red);
                items.push(lock);
            
            }
        }
    }
}
