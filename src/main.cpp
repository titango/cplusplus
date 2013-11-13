#include "libtcod.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "Character.hpp"
#include "Map.hpp"
#include "Game.hpp"

using namespace std;
int main(){
    Game *game = new Game();

    while ( !TCODConsole::isWindowClosed()){
        game->update();
        game->generate();
        TCODConsole::flush();
    }
    return 0;
}
