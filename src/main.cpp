#include "headers.hpp"

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
