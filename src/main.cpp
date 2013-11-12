#include "libtcod.hpp"
#include <iostream>
#include <string>
#include <fstream>

#include "Character.hpp"
#include "Map.hpp"
#include "Game.hpp"

using namespace std;
int main(){
    Game *game = new Game(100,100);
    ifstream ios;
    string line; 
    ios.open("map.txt");
    if(ios.is_open())
    {
        while (ios)
        {
            getline(ios,line);
            cout << line << "\n";
        }

        ios.close();
    }else{
        cout << "Unable to open" ;
    }

    while ( !TCODConsole::isWindowClosed()){
        game->update();
        game->generate();
        TCODConsole::flush();
    }
    return 0;
}
