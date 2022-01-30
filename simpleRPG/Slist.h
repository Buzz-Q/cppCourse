#ifndef SLIST_H
#define SLIST_H

using std::string;
using std::stringbuf;

struct node{
    bool win;
    string monster;
    node * next;

};
class Slist
{
    public:
        unsigned int cnt;
        Slist();
        ~Slist();

        void size();
        void pushHead(node *n);
        //void pushTail(node *n);
        void rmTail();
        void allHistory();
        void saveHistory(string name);
        void loadHistory(string name);
        void explode();

    protected:

    private:
        node *head;
        node *tail;
        //node *curr;
        //node *temp;


};

#endif // SLIST_H

//if the character is loaded, we wanna take his fight history into a new list
//we want each character to have a different list without overlapping.
//we want to save the progress in the file.
//the file is created with the first save, but should it be with the character's creation???
