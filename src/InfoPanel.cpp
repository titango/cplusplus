#include "headers.hpp"

InfoPanel::InfoPanel(int screenwidth, int screenheight)
{
    lifepanelWidth = screenwidth * 1/8; 
    lifepanelHeight = 2;
    commandline = "sa";
    commandisplay = "sa";

    width = screenwidth;
    height = 15;
    console = new TCODConsole(width-5,height);
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

    //draw point panel
    drawPointPanel();

    //Draw messagebox
    drawMessageBox();

    //Draw command line space
    drawCommandline();

    TCODConsole::blit(console,0,0,width,height,
            TCODConsole::root,0,game->map->height - height);
}

void InfoPanel::drawLifePanel()
{
    console->setDefaultForeground(TCODColor::white);
    string lifeword = "Life: ";
    console->print(lifepanelWidth,lifepanelHeight, lifeword.c_str());

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
    console->print(lifepanelWidth + 6,lifepanelHeight, lifepanel.c_str());
}

void InfoPanel::drawPointPanel()
{
    console->setDefaultForeground(TCODColor::white);
    string pointword = "Point: ";
    console->print(lifepanelWidth,lifepanelHeight + 3, pointword.c_str());

    console->setDefaultForeground(TCODColor::yellow);
    stringstream ss;
    ss << game->playerPoint;
    console->print(lifepanelWidth + 7,lifepanelHeight + 3,
            ss.str().c_str());
    
}

void InfoPanel::drawMessageBox()
{
    float colorCoef=0.4f;
    int he = lifepanelHeight;
    for (Message **it=messagelog.begin(); it != messagelog.end(); it++) {
        Message *message=*it;
        console->setDefaultForeground(message->color * colorCoef);
        console->print(width *2/4,he,message->text.c_str());
        he++;
        if ( colorCoef < 1.0f ) {
                colorCoef+=0.3f;
        }
    }
}

void InfoPanel::drawCommandline()
{
    console->setDefaultForeground(TCODColor::white);
    console->print(width - (width-1),height- 2,commandisplay.c_str());
}

void InfoPanel::message(const TCODColor &color, const string text)
{
    //clear old message
    if(messagelog.size() == 10)
    {
        Message *removemes = messagelog.get(0) ;
        messagelog.remove(removemes);
        delete removemes;
    }

    //create new one
    Message *mes = new Message(color, text);
    messagelog.push(mes);
}
