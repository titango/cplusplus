#ifndef _GAME_H
#define _GAME_H

class Game
{
    private: 
        
        int unlockdoor;
        void checkMap();
        void checkMapFile();
        void aiNPC();
        void playerKey();
        void reposition();
        void collectingItems();
        void initializeGame(string mapname);

    public:
        int life;
        double totalTime;
        double totalClockTick;
        int playerPoint;
        bool mapChecked;

        Map *map;
        InfoPanel *infopanel;
        TCODList<Item* >removedItems;
        std::vector<string> allMaps;

        Game(string mapname);
        ~Game();
        void changeLevel();
        void update();
        void generate();
};

extern Game *game;
#endif
