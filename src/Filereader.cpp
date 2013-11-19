#include "headers.hpp"

Filereader::Filereader(Map* m) : map(m)
{
}

Ground** Filereader::readFile(std::string mapname)
{
    ifstream ios;
    string line; 
    int width = 0;
    int height = 0;
    int nextHeight = 0;
    bool finishCountingWidth = false;
    Ground **g;

    // read map file
    ios.open((char*)mapname.c_str());
    if(ios.is_open())
    {
        while(getline(ios,line))
        {
            //Get map's width
            if(!finishCountingWidth)
            {
                width = line.size(); 
                finishCountingWidth = true;
            }

            //get map's height
            height++;
        }

        map->width = width;
        height = height + 10;
        map->height = height;

        //reset cursor to the beginning
        ios.clear();
        ios.seekg(0,ios::beg);

        //make 2d array
        g = new Ground*[width];
        for(int i = 0; i < width; i++)
        {
            g[i] = new Ground[height];
        }

        //loop again and put into the array
        while(getline(ios,line))
        {
            if(!ios.eof())
            {
                for(int i = 0; i < width; i++) 
                {
                    g[i][nextHeight].symbol = line.at(i);
                }
            }else
            {
                for(int i = 0; i < width; i++) 
                {
                    g[i][nextHeight].symbol = '.';
                }
            
            }
            
            nextHeight++; 
        }


        ios.close();
    }else{
        cout << "Unable to open!\n" ;
        exit(EXIT_FAILURE);
    }

    return g;
}
