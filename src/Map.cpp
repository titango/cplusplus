#include "headers.hpp"

Map::Map(string mapname) : 
    numberOfKey(0),numberOfDoor(0),doorLocked(true),
    hasPlayer(false),hasDoor(false),hasKey(false),hasGuard(false),
    hasMoney(false),amountOfMoney(0),initialNumberOfKey(0)
{
    fileread = new Maploader(this);
    grounds = fileread->readFile(mapname);

    int nextHeight = 0;

    //setting all
    componentRendering();
}

Map::~Map()
{
    characters.clearAndDelete();
    items.clearAndDelete();
    delete player;
    delete [] grounds;
    delete fileread;
}

bool Map::isWall(int x, int y) const
{
   return !grounds[x][y].canWalk;
}

bool Map::isGround(int x, int y) const
{
    bool iwalk = false;
    bool icha = false;
    bool iti = false;

    if (grounds[x][y].canWalk == true) iwalk = true;

    for(Character ** iterators=characters.begin();
            iterators != characters.end(); iterators++)
    {
        Character *cha = *iterators;
        if(cha->x == x && cha->y == y && cha != player)
        {
            icha = true; 
        }
    }

    for(Item ** iterators=items.begin();
            iterators != items.end(); iterators++)
    {
        Item *item = *iterators;
        if(item->x == x && item->y == y)
        {
            iti = true; 
        }
    }

    if(iwalk && !icha && !iti)
    {
        return true; 
    }else
    {
        return false; 
    }
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
                Character *guard = new Guard("guard",i,j,GUARD,
                        TCODColor::orange);
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
                TCODColor *te = new TCODColor(102,102,0);
                Item *lock = new Item("lock",i,j,LOCK,*te);
                items.push(lock);
            
            }
        }
    }
}
