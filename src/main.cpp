#include "libtcod.hpp"
#include "Character.hpp"
#include "Map.hpp"
#include "Game.hpp"

Game game;

int main(){
    TCODConsole::initRoot(80,50,"libtcod C++ tutorial", false);
    while ( !TCODConsole::isWindowClosed()){
        game.update();
        game.generate();
        TCODConsole::flush();

    }
    return 0;
}
