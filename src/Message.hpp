#ifndef _MESSAGE_H
#define _MESSAGE_H

class Message
{
    public:
        string text;
        TCODColor color;

        Message(const TCODColor &color, const string text);
        ~Message();
};
#endif
