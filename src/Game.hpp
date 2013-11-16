#ifndef _GAME_H
#define _GAME_H

class Game
{
    public:
        double totalTime;
        double totalClockTick;
        Map *map;
        TCODList<Item* >removedItems;

        Game(string mapname);
        ~Game();
        void update();
        void generate();
};

extern Game *game;
#endif
