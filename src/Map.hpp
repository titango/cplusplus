#ifndef _MAP_H
#define _MAP_H

class Map
{

    public:
        int width, height;
        TCODList<Character *> characters;
        TCODList<Item *> items;
        Character *player;
        Map(string mapname);
        ~Map();

        bool isWall(int x, int y) const;
        void generate();
        void componentRendering();

    protected:
        Filereader *fileread;

        void setWall(int x, int y);
        Ground **grounds;
};
#endif
