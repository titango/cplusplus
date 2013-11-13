#ifndef _FILEREADER_H
#define _FILEREADER_H

using namespace std;

class Filereader
{
    Map* map;

    public:
        Filereader(Map* map);
        Ground **readFile(std::string mapname);
};
#endif
