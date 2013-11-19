#include "headers.hpp"

Game::Game(string mapname) : playerPoint(0), life(3), unlockdoor(1)
{
    initializeGame(mapname);
    checkMapFile();
}

Game::~Game()
{
    delete map;
    delete infopanel;
    delete &allMaps;
}

void Game::initializeGame(string mapname)
{
    totalTime = 0.0;
    totalClockTick = 0.0;
    mapChecked = false;

    map = new Map(mapname);
    map->currentMapName = mapname;

    //Check map components
    if(!mapChecked)
    {
        checkMap(); 
    }

    infopanel = new InfoPanel(map->width, map->height);
    cout << "ITEM SIZE" << map->items.size() << "\n";

    //for(Item ** iterators=map->items.begin();
            //iterators != map->items.end(); iterators++)
    //{
        //Item* item = *iterators;
        //cout << "ITEM NAME " << item->name << "\n";
    //}

    TCODConsole::initRoot(map->width,map->height,
            "Lock & Chase: Thief edition", false);

    for(Item ** iterators=map->items.begin();
            iterators != map->items.end(); iterators++)
    {
        Item* item = *iterators;
        cout << "ITEM NAME " << item->name << "\n";
    }
}

void Game::update()
{

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

    if( unlockdoor != 1)
    {
        if (map->isGround(map->player->x, map->player->y))
        {
            unlockdoor = 1; 
        }   
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
                gua->alertedGuard = 1;
                gua->automove(); 

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
                gua->escape = 1;
                gua->chasePlayer();
                gua->color = TCODColor::red;

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
            game->infopanel->message(TCODColor::red,
                    "You lose the game");
        }else
        {
            stringstream ss;
            ss << life;
            string mes = "You still have ";
            mes.append(ss.str());
            mes.append(" left");
            game->infopanel->message(TCODColor::orange,
                    mes);
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
                TCODColor *te = new TCODColor(102,102,0); 
                item->color = *te;
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

        //cout << "Total name: " << item->name << "\n";
        //cout << "position items: " << item->x << " - " << item->y << " \n";
        //cout << "TOTAL KEY SIZE: " << map->numberOfKey << "\n";
        if(map->player->interactItem(item))
        {
            cout <<"Interacted \n";
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
                TCODColor *te = new TCODColor(102,102,0); 

                if(item->color == *te) 
                {
                    if(unlockdoor == 1)
                    {
                        game->infopanel->message(TCODColor::yellow,
                                "You need to collect all keys to unlock\
                                the door"); 
                    }

                    unlockdoor = 0;
                }else
                {                    

                    //if(unlockdoor == 1)
                    //{
                        //game->infopanel->message(TCODColor::green,
                             //"You win the game"); 
                    //}

                    //unlockdoor = 0;
                    //changeLevel();
                    if(allMaps.size() == 0)
                    {
                        exit(EXIT_SUCCESS); 
                    }else{
                        removedItems.clear();
                        initializeGame(allMaps[0]);
                        cout << "Next map: " << allMaps[0] << "\n";
                        allMaps.erase(allMaps.begin(),allMaps.begin()+1);

                        break;
                    }
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

void Game::checkMap()
{
    bool exitFailure = false;

    //Check map symbol
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

void Game::checkMapFile()
{
    bool exitFailure = false;
    //Check map number; 
    std::size_t found = map->currentMapName.find("_1");

    //If found map
    if(found!= std::string::npos)
    {
        //put into game->allMaps
        string nextmapName = map->currentMapName.substr(0,found);
        int numberForMap = 2;
        bool existed = true;

        while(existed)
        {
            //get the string for <mapname>_<nextlevel>
            stringstream ss;
            ss << numberForMap;
            string tempnextmap = nextmapName.substr(0,nextmapName.size());
            tempnextmap.append("_");
            tempnextmap.append(ss.str());
            tempnextmap.append(".txt");
            ifstream my_file(tempnextmap.c_str());

            //If file existed
            if(my_file.good())
            {
                cout << "There is next map: " << tempnextmap << "\n";
                //string te = tempnextmap;
                allMaps.push_back(tempnextmap);
                numberForMap++;
                my_file.close();
            }else
            {
                existed = false; 
            }
            //std::size_t foundnext = map->tempnextmap.find 
        }
         
    //If not found map
    }else
    {
        cout << "Map doesn't in the right format type. It should be " ;
        cout << "<mapname>_1.txt\n";
        cout << "Example: forest_1.txt\n";
        exitFailure = true;
    }

    if(exitFailure) exit(EXIT_FAILURE);
}

void Game::changeLevel()
{

}
