#ifndef _INFOPANEL_H
#define _INFOPANEL_H

class InfoPanel
{
    private: 
        int width;
        int height;
        int lifepanelWidth;
        int lifepanelHeight;
        int messageboxWidth;
        void drawLifePanel();
        void drawMessageBox();

    protected:
        TCODConsole *console;
        TCODList<Message *> messagelog;
        
        void generateLifePanel();

    public:
        InfoPanel(int screenwidth, int screenheight);
        ~InfoPanel(); 

        void generate();
        void message(const TCODColor &color, const string text);

};
#endif
