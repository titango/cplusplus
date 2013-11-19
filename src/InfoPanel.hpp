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
        void drawPointPanel();
        void drawLifePanel();
        void drawMessageBox();
        void drawCommandline();

    protected:
        TCODConsole *console;
        TCODList<Message *> messagelog;
        
        void generateLifePanel();

    public:
        string commandline;
        string commandisplay;
        InfoPanel(int screenwidth, int screenheight);
        ~InfoPanel(); 

        void generate();
        void message(const TCODColor &color, const string text);

};
#endif
