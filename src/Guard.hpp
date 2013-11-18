#ifndef _GUARD_H
#define _GUARD_H

class Guard : public Character
{
    public:

    int alertedGuard;
    int escape;
    Guard(std::string name, int x, int y, int sym, const TCODColor &color);
    void automove();
    void chasePlayer();
    bool detectPlayer();
};

#endif
