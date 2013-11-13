#ifndef _MAP_H
#define _MAP_H

class Map
{

    public:
        int width, height;
        Map();
        ~Map();
        bool isWall(int x, int y) const;
        void generate() const;

    protected:
        Filereader *fileread;
        void setWall(int x, int y);
        Ground **grounds;
};
#endif
