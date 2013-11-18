#include "headers.hpp"

Game::Game(string mapname) : totalTime(0.0),totalClockTick(0.0),
    playerPoint(0), mapChecked(false), life(3)
{
    map = new Map(mapname);
    infopanel = new InfoPanel();
    TCODConsole::initRoot(map->width,map->height,
            "Lock & Chase: Thief edition", false);
}

Game::~Game()
{
    delete map;
    delete infopanel;
}

void Game::update()
{
    //Check map components
    if(!mapChecked)
    {
        checkMap(); 
    }

    //Guard AI
    aiNPC();

    //Collecting items
    collectingItems();

    //Reposition if touched guards
    reposition();

    //Recieve key and check Wall
    playerKey();
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

    infopanel->generate();

}

void Game::checkMap()
{
    bool exitFailure = false;
    if(!map->hasPlayer)
    {
        cout << "There is no player! System exit." << endl;
        exitFailure = true;
    }

    if(!map->hasDoor)
    {
        cout << "There is no door! System exit." << endl; 
        exitFailure = true;
    }

    if(!map->hasKey)
    {
        cout << "There is no key! System exit." << endl;
        exitFailure = true;
    }

    if(!map->hasGuard)
    {
        cout << "There is no guard! System exit." << endl; 
        exitFailure = true;
    }

    if(map->numberOfDoor == 0 || map->numberOfDoor > 1)
    {
        cout << "No or too many doors. Only allow 1" ;
        exitFailure = true;
    }

    if(exitFailure) exit(EXIT_FAILURE);

}

void Game::playerKey()
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

void Game::aiNPC()
{
    //Guard automove
    for(Character ** iterators=map->characters.begin();
            iterators != map->characters.end(); iterators++)
    {
        Character *cha = *iterators;
        if(cha != map->player)
        {
            Guard *gua = (Guard*)cha;
            bool detected = gua->detectPlayer();

            if(!detected)
            {
                //Guards move auto if not detect
                gua->alertedGuard = 2;
                gua->automove(); 

                if(gua->escape == 2)
                {
                    gua->escape = 1; 
                }
                TCODColor *te = new TCODColor(255,112,77);
                gua->color = *te;
                
                if(gua->escape == 1)
                {
                    te = new TCODColor(51,102,255);
                    game->infopanel->message(*te, 
                            "You escaped from the guard"); 
                }

                gua->escape = 0;
            }else
            {

                //Guards detected player
                gua->escape = 2;
                gua->chasePlayer();
                gua->color = TCODColor::red;

                if(gua->alertedGuard == 2)
                {
                    gua->alertedGuard = 1; 
                }

                if(gua->alertedGuard == 1)
                {
                    game->infopanel->message(TCODColor::red, 
                        "You alerted the guard"); 
                }

                gua->alertedGuard = 0;
            }
        }
    }
}

void Game::reposition()
{
    bool touchedGuard = false;

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
        //reduce player's life
        life--;

        //Life < 0 -> lose the game
        if( life == 0)
        {
            cout << "You lose the game!" << endl; 
            exit(EXIT_SUCCESS);
        }else
        {
            cout << "You still have " << life << " left " <<  endl;
        }

        //reposition characters
        for(Character ** iterators=game->map->characters.begin();
                iterators != game->map->characters.end(); iterators++)
        {
            (*iterators)->x = (*iterators)->originalx; 
            (*iterators)->y = (*iterators)->originaly; 
        }

        //reposition items
        for(Item ** iterators=removedItems.begin();
                iterators != removedItems.end(); iterators++)
        {
            map->items.push(*iterators);
        }

        //Reset color lock
        for(Item ** iterators=map->items.begin();
                iterators != map->items.end(); iterators++)
        {
            Item *item = *iterators;
            if(item->symbol == LOCK)
            {
                item->color = TCODColor::red;
            }
        }

        game->playerPoint = 0;
        map->numberOfKey = map->initialNumberOfKey;
    }

}

void Game::collectingItems()
{
    //Check for touching items

    for(Item ** iterators=map->items.begin();
            iterators != map->items.end(); iterators++)
    {
        Item *item = *iterators;
        if(map->player->interactItem(item))
        {
            if(item->symbol == MONEY)
            {
                game->playerPoint = game->playerPoint + MONEY_POINT; 
                cout << game->playerPoint << "\n";
                removedItems.push(item);
                map->items.remove(item);
                break;
            }else if(item->symbol == KEY)
            {
                game->playerPoint = game->playerPoint + KEY_POINT; 
                map->numberOfKey--; 
                removedItems.push(item);
                map->items.remove(item);
                break;
            }else if(item->symbol == LOCK)
            {
                if(item->color == TCODColor::red) 
                {
                
                }else
                {
                   exit(EXIT_SUCCESS);
                }
            }
        }

    }

    if(game->map->numberOfKey == 0)
    {
        for(Item ** iterators=map->items.begin();
                iterators != map->items.end(); iterators++)
        {
            Item *item = *iterators;
            if(item->symbol == LOCK)    
            {
                item->color = TCODColor::green; 
            }
        }
    }
}
