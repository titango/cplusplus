#include "headers.hpp"

Game::Game(string mapname) : totalTime(0.0),totalClockTick(0.0)
{
    map = new Map(mapname);
    TCODConsole::initRoot(map->width,map->height,
            "Lock & Chase: Thief edition", false);
}

Game::~Game()
{
    delete map;
}

void Game::update()
{
    TCOD_key_t key;
    bool touchedGuard = false;
    TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS, &key, NULL);
     
    //Guard automove
    for(Character ** iterators=map->characters.begin();
            iterators != map->characters.end(); iterators++)
    {
        Character *cha = *iterators;
        if(cha != map->player)
        {
            Guard *gua = (Guard*)cha;
            gua->automove();
        }
    }

    //Check for touching items

    for(Item ** iterators=map->items.begin();
            iterators != map->items.end(); iterators++)
    {
        Item *item = *iterators;
        if(map->player->interactItem(item))
        {
            removedItems.push(item);
            map->items.remove(item);
            break;
        }
    }
    
    //Check for touching the guard
    for(Character ** iterators=map->characters.begin();
            iterators != map->characters.end(); iterators++)
    {
        Character *cha = *iterators;
        if(cha != map->player)
        {     
            touchedGuard = map->player->interactCharacter(cha);
            if(touchedGuard)
            {
                break; 
            }
        }
    }

    //Reposition if touched
    if(touchedGuard)
    {
        //reposition player
        map->player->x = map->player->originalx; 
        map->player->y = map->player->originaly;

        //reposition items
        for(Item ** iterators=removedItems.begin();
                iterators != removedItems.end(); iterators++)
        {
            map->items.push(*iterators);
        }
    }

    //Recieve key and check Wall
    switch(key.vk)
    {
        case TCODK_UP : 
            if ( ! map->isWall(map->player->x,map->player->y-1)) { 
                map->player->y--;   
            }
        break;
        case TCODK_DOWN : 
        if ( ! map->isWall(map->player->x,map->player->y+1)) {
            map->player->y++;
        }
        break;
        case TCODK_LEFT : 
        if ( ! map->isWall(map->player->x-1,map->player->y)) {
            map->player->x--;
        }
        break;
        case TCODK_RIGHT : 
        if ( ! map->isWall(map->player->x+1,map->player->y)) {
            map->player->x++;
        }
        break;
        default:break;
    }
}

void Game::generate()
{
    TCODConsole::root->clear();
    map->generate();

    //Generate characters
    for(Character ** iterators=map->characters.begin();
            iterators != map->characters.end(); iterators++)
    {
        (*iterators)->generate();
    }

    //Generate items
    for(Item ** iterators=map->items.begin();
            iterators != map->items.end(); iterators++)
    {
        (*iterators)->generate();
    }

}
