#include "headers.hpp"

Game::Game(string mapname)
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
    TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS, &key, NULL);
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

    for(Character ** iterators=map->characters.begin();
            iterators != map->characters.end(); iterators++)
    {
        (*iterators)->generate();
    }
}
