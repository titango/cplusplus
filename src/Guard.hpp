#ifndef _GUARD_H
#define _GUARD_H

class Guard : public Character
{
    public:
        Guard(std::string name, int x, int y, int sym, const TCODColor &color);
        void automove();
        bool detectPlayer();
};

#endif
