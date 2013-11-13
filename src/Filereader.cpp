#include "Filereader.hpp"

Filereader::Filereader()
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
    ios.open("map.txt");
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

        cout << width << endl;
        cout << height << endl;

        //reset cursor to the beginning
        ios.clear();
        ios.seekg(0,ios::beg);

        //make 2d array
        //g = new Ground*[width];
        //for(int i = 0; i < width; i++)
        //{
            //g[i] = new Ground[height];
        //}

        //loop again and put into the array
        //while(getline(ios,line))
        //{
           //for(int i = 0; i < line.size(); i++) 
           //{
                //if(line.at(i) == '#')
                //{
                     
                //}
           //}
        //}

        ios.close();
    }else{
        cout << "Unable to open" ;
    }

        g = new Ground*[44];
        for(int i = 0; i < 44; i++)
        {
            g[i] = new Ground[13];
        }
    return g;
}
