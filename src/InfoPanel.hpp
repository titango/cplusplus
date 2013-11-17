#ifndef _INFOPANEL_H
#define _INFOPANEL_H

class InfoPanel
{
    protected:
        TCODConsole *console;
        
        void generateLifePanel();

    public:
        InfoPanel();
        ~InfoPanel(); 

        void generate();

};
#endif
