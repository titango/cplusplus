#ifndef _GAME_H
#define _GAME_H

class Game
{
    public:
        TCODList<Character *> characters;
        Character *player;
        Map *map;

        Game();
        ~Game();
        void update();
        void generate();
};

#endif
