#include "headers.hpp"

InfoPanel::InfoPanel()
{
    console = new TCODConsole(44,10);
}

InfoPanel::~InfoPanel()
{
    delete console;
    messagelog.clearAndDelete();
}

void InfoPanel::generate()
{
    console->setDefaultBackground(TCODColor::black);
    console->clear();

    //draw life panel
    drawLifePanel();

    //Draw messagebox
    float colorCoef=0.4f;
    int he = 2;
    for (Message **it=messagelog.begin(); it != messagelog.end(); it++) {
        Message *message=*it;
        console->setDefaultForeground(message->color * colorCoef);
        console->print(16,he,message->text.c_str());
        he++;
        if ( colorCoef < 1.0f ) {
                colorCoef+=0.3f;
        }
    }

    TCODConsole::blit(console,0,0,game->map->width,10,
            TCODConsole::root,0,game->map->height - 10);
}

void InfoPanel::drawLifePanel()
{

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
}

void InfoPanel::drawMessageBox()
{
}

void InfoPanel::message(const TCODColor &color, const string text)
{
    //clear old message
    if(messagelog.size() == 7)
    {
        Message *removemes = messagelog.get(0) ;
        messagelog.remove(removemes);
        delete removemes;
    }

    //create new one
    Message *mes = new Message(color, text);
    messagelog.push(mes);
}
