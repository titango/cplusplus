#ifndef _GAME_H
#define _GAME_H

class Game
{
    private: 
        void checkMap();
        void aiNPC();
        void playerKey();
        void reposition();
        void collectingItems();

    public:
        int life;
        double totalTime;
        double totalClockTick;
        int playerPoint;
        bool mapChecked;

        Map *map;
        InfoPanel *infopanel;
        TCODList<Item* >removedItems;

        Game(string mapname);
        ~Game();
        void update();
        void generate();
};

extern Game *game;
#endif
