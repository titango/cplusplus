#ifndef _GAME_H
#define _GAME_H

class Game
{
    public:
        Map *map;

        Game(string mapname);
        ~Game();
        void update();
        void generate();
};

#endif
