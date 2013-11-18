#ifndef _INFOPANEL_H
#define _INFOPANEL_H

class InfoPanel
{
    private: 
        void drawLifePanel();
        void drawMessageBox();

    protected:
        TCODConsole *console;
        TCODList<Message *> messagelog;
        
        void generateLifePanel();

    public:
        InfoPanel();
        ~InfoPanel(); 

        void generate();
        void message(const TCODColor &color, const string text);

};
#endif
