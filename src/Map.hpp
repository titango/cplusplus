#ifndef _MAP_H
#define _MAP_H

#include "Ground.hpp"

class Map
{
    int width, height;

    public:
        Map(int width, int height);
        ~Map();
        bool isWall(int x, int y) const;
        void generate() const;

    protected:
        void setWall(int x, int y);
        Ground **grounds;
};
#endif
