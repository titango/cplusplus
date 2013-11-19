#ifndef _MAPLOADER_H
#define _MAPLOADER_H

using namespace std;

class Maploader
{
    Map* map;

    public:
        Maploader(Map* map);
        Ground **readFile(std::string mapname);
};
#endif
