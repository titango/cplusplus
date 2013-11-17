#include "headers.hpp"

InfoPanel::InfoPanel()
{
    console = new TCODConsole(44,10);
}

InfoPanel::~InfoPanel()
{
    delete console;
}

void InfoPanel::generate()
{
    console->setDefaultBackground(TCODColor::black);
    console->clear();

    //draw
    console->setDefaultForeground(TCODColor::white);
    string lifeword = "Life: ";
    console->print(2,2, lifeword.c_str());

    console->setDefaultForeground(TCODColor::red);
    string lifepanel = "";

    for(int i = 0; i < game->life; i++)
    {
        char cha[3];
        cha[0] = PLAYER;
        cha[1] = ' ';
        cha[2] = '\0';
        string temp(cha);        
        lifepanel.append(temp);
    }
    console->print(8,2, lifepanel.c_str());

    TCODConsole::blit(console,0,0,game->map->width,10,
            TCODConsole::root,0,game->map->height - 10);
}
