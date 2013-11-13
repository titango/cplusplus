#ifndef _FILEREADER_H
#define _FILEREADER_H

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Ground.hpp"

using namespace std;

class Filereader
{
    //Map* map;

    public:
        Filereader();
        Ground **readFile(std::string mapname);
};
#endif
