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

    stringstream ss;
    string mapname;
    
    //Get map from second argument
    ss << argv[1];
    ss >> mapname;

    game = new Game(mapname);
    
    //Run the game
    while ( !TCODConsole::isWindowClosed()){
        game->update();
        game->generate();
        TCODConsole::flush();
    }
    return 0;
}
