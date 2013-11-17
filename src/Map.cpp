#include "headers.hpp"

Map::Map(string mapname) : 
    numberOfKey(0),numberOfDoor(0),doorLocked(true),
    hasPlayer(false),hasDoor(false),hasKey(false),hasGuard(false),
    hasMoney(false),amountOfMoney(0),initialNumberOfKey(0)
{
    fileread = new Filereader(this);
    grounds = fileread->readFile(mapname);

    //setting all
    componentRendering();
}

Map::~Map()
{
    characters.clearAndDelete();
    delete player;
    delete [] grounds;
    delete fileread;
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
                TCODConsole::root->setChar(x,y,WALL);
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
            if(grounds[i][j].symbol == WALL) 
            {
                setWall(i,j);
            }
            //setting characters
            else if(grounds[i][j].symbol == PLAYER)
            { 
                hasPlayer = true;
                player = new Character("player",i,j,PLAYER, TCODColor::white);
                characters.push(player);
            //setting guards
            }else if(grounds[i][j].symbol == GUARD)
            {
                hasGuard = true;
                Character *guard = new Guard("guard",i,j,GUARD,TCODColor::orange);
                characters.push(guard);
            //setting money
            }else if(grounds[i][j].symbol == MONEY)
            {
                hasMoney = true;
                Item *money = new Item("money",i,j,MONEY,TCODColor::green);
                items.push(money);
                amountOfMoney++;
            //setting keys
            }else if(grounds[i][j].symbol == KEY)
            {
                hasKey = true;
                numberOfKey++;
                initialNumberOfKey++;
                Item *key = new Item("key",i,j,KEY,TCODColor::cyan);
                items.push(key);
            
            //setting lock
            }else if(grounds[i][j].symbol == LOCK)
            {
                hasDoor = true;
                numberOfDoor++;
                Item *lock = new Item("lock",i,j,LOCK,TCODColor::red);
                items.push(lock);
            
            }
        }
    }
}
