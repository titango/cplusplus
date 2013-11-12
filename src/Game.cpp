#include "libtcod.hpp"
#include "Character.hpp"
#include "Map.hpp"
#include "Game.hpp"

Game::Game()
{
    TCODConsole::initRoot(80,50,"Lock & Chase: Thief edition", false);
    player = new Character(40,25,'O', TCODColor::white);
    characters.push(player);
    characters.push(new Character(60,13,'X',TCODColor::yellow));
    map = new Map(80,45);
}

Game::~Game()
{
    characters.clearAndDelete();
    delete map;
}

void Game::update()
{
    TCOD_key_t key;
    TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS, &key, NULL);
    switch(key.vk)
    {
        case TCODK_UP : 
            if ( ! map->isWall(player->x,player->y-1)) {
                player->y--;   
            }
        break;
        case TCODK_DOWN : 
        if ( ! map->isWall(player->x,player->y+1)) {
            player->y++;
        }
        break;
        case TCODK_LEFT : 
        if ( ! map->isWall(player->x-1,player->y)) {
            player->x--;
        }
        break;
        case TCODK_RIGHT : 
        if ( ! map->isWall(player->x+1,player->y)) {
            player->x++;
        }
        break;
        default:break;
    }
}

void Game::generate()
{
    TCODConsole::root->clear();
    map->generate();

    for(Character ** iterators=characters.begin();
            iterators != characters.end(); iterators++)
    {
        (*iterators)->generate();
    }
}
