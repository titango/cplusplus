#ifndef _MAP_H
#define _MAP_H

static const char PLAYER = 'O';
static const char MONEY = '$';
static const char GUARD = 'X';
static const char KEY = '+';
static const char LOCK = 'D';
static const char WALL = '#';
static const int MONEY_POINT = 100;
static const int KEY_POINT = 50;

class Map
{

    public:
        int width, height;
        int initialNumberOfKey;
        int numberOfKey;
        int numberOfDoor;
        int amountOfMoney;
        bool doorLocked;
        bool hasPlayer;
        bool hasDoor;
        bool hasKey;
        bool hasGuard;
        bool hasMoney;
        string currentMapName;

        TCODList<Character *> characters;
        TCODList<Item *> items;
        Character *player;
        Map(string mapname);
        ~Map();

        bool isWall(int x, int y) const;
        bool isGround(int x, int y) const;
        void generate();
        void componentRendering();

    protected:
        Filereader *fileread;

        void setWall(int x, int y);
        Ground **grounds;
};
#endif
