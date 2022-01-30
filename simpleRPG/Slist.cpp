#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <bits/stdc++.h>

#include "Slist.h"

using std::string;
using std::stringbuf;
using namespace std;

Slist::Slist()
{
    head = NULL;
    tail = NULL;
    cnt = 0;
}

Slist::~Slist(){
    node *curr = new node;
    curr = head;
    while(head != NULL){
        curr = head->next;
        delete head;
        head = curr;
    }
    //cout<<"List terminated\n";
}

void Slist::explode(){
    while(head){
        rmTail();
    }
}

void Slist::size(){cout<<"\nlist size: "<<cnt<<endl;}

void Slist::pushHead(node *n){
    if(head != NULL){
        node *curr = head;
        head = n;
        head->next = curr;
    }else{
        head = n;
        tail = n;
    }
    cout<<"Fight result was added to the head of the list\n";
    if(cnt++ >= 10){rmTail();}

}

void Slist::rmTail(){
    node *curr = new node;
    curr = head;
    node *temp = tail;
    if(tail){
        while(curr){
            if(curr->next!=tail){
                curr = curr->next;
            }else{
                tail = curr;
                tail->next = NULL;
                //cout<<"oldest fight is deleted\n";
                delete temp;
                --cnt;
            }
        }
    }
}

void Slist::allHistory(){
    node *curr = new node;
    curr = head;
    int i = 1;
    //case 1: if the history is empty
    if(!curr){
        cout<<"This hero doesn't have a fight history\n";
    }else{
        while(curr != NULL){
            cout<<"Fight "<<i<<" against "<<curr->monster
            <<" Hero win: "<<curr->win<<endl;
            if(curr == tail){break;}
            curr = curr->next;
            ++i;
        }

    }
}

void Slist::saveHistory(string name){
    ofstream sv;
    string filename;
    filename=name+"History.txt";
    sv.open(filename.c_str());

        if(sv.good()){
            cout<<"Success\n";

            node *data = new node;
            data = head;
            for(unsigned j = 1; j <= cnt; j++){
            sv<<data->monster<<" "<<data->win<<endl;
            //cout<<"7attena "<<data->monster<<" f om el list!\n";
            if(data == tail){break;}
            data = data->next;
        }
        }else{
            cout<<"Failed, please try again";
        }

        sv.close();
}

void Slist::loadHistory(string name){

    if(!head){
        ifstream l;
        string filename, word;
        int k;
        filename=name+"History.txt";
        l.open(filename.c_str(), ios::in | ios::out);

            if(l.good()){
                //cout<<"Success\n";
                //while(cnt != 0){rmTail();}
                while(!l.eof()){
                    node *curr = new node;
                    l >> curr->monster;
                    l >> curr->win;
                    if(!curr->monster.empty()){
                        //cout<<"benda5al "<<curr->monster<<" w "<<curr->win<<endl;
                        pushHead(curr);
                    }else{break;}
                }
            }else{
                cout<<"Failed to reach hero's history  :'(";
            }

            l.close();
            allHistory();
    }
}
