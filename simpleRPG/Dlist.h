#ifndef DLIST_H
#define DLIST_H

#include<string>
#include"Hero.h"
using std::string;
using std::stringbuf;

struct dnode{

    string item;
    int quantity = 0;
    bool equipped = false;
    int advantage[5];

    dnode * next;
    dnode * prev;

};

class Dlist
{
    public:
        Dlist();
        dnode * dhead;

        virtual ~Dlist();

        void pushEnd(dnode *value);
        void pushTop(dnode *value);
        void pop(string el);

        void setAdvantage(dnode *value);
        dnode * searchItem(string itemName, dnode * s);
        void equip(Hero &h, dnode *p);
        void disequip(Hero &h, dnode *p);

        void display();

        void saveInventory(string name);
        void loadInventory(string name);

    protected:

    private:
        int dcnt;
};

#endif // DLIST_H
