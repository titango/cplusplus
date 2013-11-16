#include "headers.hpp"

using namespace std;

Game *game;

int main(int argc, char *argv[]){

    //Check arguments
    if(argc < 2 )
    {
        cout << "Missing map file. Program exit!" << endl;
        return 1;
    }else if(argc > 2)
    {
        cout << "Too many arguments. Should only be 2" << endl;
        return 1;
    }

    //TCODSystem::setFps(90);
    stringstream ss;
    string mapname;
    
    //Get map from second argument
    ss << argv[1];
    ss >> mapname;

    game = new Game(mapname);
    bool printed = true;
    
    //Run the game
    while ( !TCODConsole::isWindowClosed()){
        clock_t start = clock();
        game->update();
        game->generate();
        TCODConsole::flush();
        clock_t end = clock();
        game->totalClockTick = game->totalClockTick + (end - start) + 115;
        game->totalTime = 
            (game->totalClockTick/CLOCKS_PER_SEC);
        cout << game->totalTime << "\n";
        //if(game->totalTime > 12 && printed)
        //{
            //cout << "Greater than " << game->totalTime <<"\n" ;
            //printed = false;
        //}
    }
    return 0;
}
