#include<string>
#include<iostream>
#include <fstream>
#include <sstream>
#include <bits/stdc++.h>
#include <cstdlib>
#include "Dlist.h"
#include "Hero.h"

using std::string;
using std::stringbuf;
using namespace std;


Dlist::Dlist()
{
    dhead = NULL;
    dcnt = 0;
}

Dlist::~Dlist()
{
    //dtor
}

void Dlist::pushEnd(dnode *value){
    dnode *curr = new dnode;
    dnode *temp = new dnode;
    bool exist = false;

    curr = dhead;
    temp = curr;
    if(value->item != "Nothing"){
        if(!curr){
            setAdvantage(value);
            dhead = value;
            dhead->quantity = 1;
            dhead->next = NULL;
            dhead->prev = NULL;
            cout<<value->item<<" initiated the list from the end\n";
        }else{
            while(curr->next){
                if(curr->item == value->item){
                    ++curr->quantity;
                    exist = true;
                    cout<<curr->item<<"'s quantity increased"
                    <<" to "<<curr->quantity<<endl;
                    break;
                }
                temp = curr;
                curr = curr->next;
                curr->prev = temp;
            } if(curr->item == value->item){
                ++curr->quantity; exist = true;
                }
            if(!exist){
                setAdvantage(value);
                ++value->quantity;
                curr->next = value;
                curr->prev = temp;
                value->prev = curr;
                value->next = NULL;
                cout<<value->item<<" added to the end\n";
            }

        } ++dcnt;
    }
}

void Dlist::setAdvantage(dnode *value){
    char ch = {value->item[0]};
    switch(ch){
                case 'A': {
                    value->advantage[0] = 0;
                    value->advantage[1] = 2;
                    value->advantage[2] = 0;
                    value->advantage[3] = 0;
                    value->advantage[4] = 2;
                    break;
                }
                case 'S': {
                    value->advantage[0] = 3;
                    value->advantage[1] = 1;
                    value->advantage[2] = 0;
                    value->advantage[3] = 0;
                    value->advantage[4] = 0;
                    break;
                }
                case 'R': {
                    value->advantage[0] = 0;
                    value->advantage[1] = 2;
                    value->advantage[2] = 2;
                    value->advantage[3] = 2;
                    value->advantage[4] = 0;
                    break;
                }
                case 'W': {
                    value->advantage[0] = 0;
                    value->advantage[1] = 1;
                    value->advantage[2] = 1;
                    value->advantage[3] = 2;
                    value->advantage[4] = 0;
                    break;
                };
                default: cout<<"Wrong input\n\n";
            }
}

dnode * Dlist::searchItem(string itemName, dnode* s){
    while(s){
        if(s->item == itemName){
            return s;
        }else{
            return searchItem(itemName, s->next);
        }
    }
    cout<<"Item not found\n";
    return NULL;
}

void Dlist::display(){
    if(!dhead){
        cout<<"Inventory is empty\n";
    }else{
        dnode *curr = new dnode;
        curr = dhead;
        while(curr){
            cout<<"Item "<<curr->item<<
            " Quantity: "<<curr->quantity<<
            " Equipped: "<<curr->equipped<<endl;
            curr = curr->next;
        }
    }
}

void Dlist::pop(string el){
    dnode *temp = new dnode;
    dnode *curr = new dnode;
    curr = dhead;
    temp = curr;
    if(dhead->item == el){
        temp = dhead;
        dhead = dhead->next;
        dhead->prev = NULL;
        cout<<"head deleted\n";
        --dcnt;
        delete(temp);
    }else{
        while(curr->next){
            curr = curr->next;
            if(curr->item == el){
                if(curr->next){
                    curr->next->prev = temp;
                    temp->next = curr->next;
                    delete(curr);
                    cout<<"Mid deleted\n";
                    --dcnt;
                    break;
                }else{
                    temp->next = NULL;
                    curr->prev = NULL;
                    delete(curr);
                    cout<<"End node deleted\n";
                    --dcnt;
                    break;
                }
            }else{
                temp = curr;
            }
        }
    }
}

void Dlist::saveInventory(string name){
    ofstream sv;
    string filename;
    filename=name+"Inventory.txt";
    sv.open(filename.c_str());

        if(sv.good()){
            //cout<<"Success\n";

            dnode *data = new dnode;
            data = dhead;
            for(unsigned j = 1; j <= dcnt; j++){
            sv<<data->item<<" "<<data->quantity<<" "<<data->equipped<<endl;
            //cout<<"7attena "<<data->item<<" f el Dlist!\n";
            if(data->next == NULL){break;}
            data = data->next;
        }
        }else{
            cout<<"Failed, please try again";
        }

        sv.close();

}

void Dlist::loadInventory(string name){

    if(!dhead){
        //cout<<"El list fadya aho\n\n";
        ifstream l;
        string filename, word;
        int k;
        filename=name+"Inventory.txt";
        l.open(filename.c_str(), ios::in | ios::out);

            if(l.good()){
                //cout<<"Success\n";
                //while(cnt != 0){rmTail();}
                while(!l.eof()){
                    dnode *curr = new dnode;
                    l >> curr->item;
                    l >> curr->quantity;
                    l >> curr->equipped;
                    if(!curr->item.empty()){
                        //cout<<"benda5al "<<curr->item<<" w equipped "<<curr->equipped<<endl;
                        pushEnd(curr);
                    }else{break;}
                }
            }else{
                cout<<"Failed to reach hero's history  :'(";
            }

            l.close();
            //display();
    }
}

void Dlist::equip(Hero &h, dnode *p){
    cout<<"Equip function\n\n";
    p->equipped = 1;
    setAdvantage(p);
    h.strength = h.strength + p->advantage[0]; //cout<<p->advantage[0]<<" is advantage inrease\n";
    h.dexterity= h.dexterity + p->advantage[1]; //cout<<p->advantage[1]<<" is advantage inrease\n";
    h.endurance = h.endurance + p->advantage[2]; //cout<<p->advantage[2]<<" is advantage inrease\n";
    h.intelligence = h.intelligence + p->advantage[3]; //cout<<p->advantage[3]<<" is advantage inrease\n";
    h.charisma = h.charisma + p->advantage[4]; //cout<<p->advantage[4]<<" is advantage inrease\n";

    cout<<"New Attributes: strength "<<h.strength<<" Dexterity "<<h.dexterity<<" endurance "<<h.endurance<<endl
    <<" Intelligence "<<h.intelligence<<" charsima "<<h.charisma<<endl;
    h.save(h.characterName);
    saveInventory(h.characterName);
}

void Dlist::disequip(Hero &h, dnode *p){
    cout<<"Disequip function\n\n";
    p->equipped = 0;
    setAdvantage(p);
    h.strength -= p->advantage[0];
    h.dexterity-= p->advantage[1];
    h.endurance-= p->advantage[2];
    h.intelligence-= p->advantage[3];
    h.charisma -= p->advantage[4];

    cout<<"New Attributes: strength "<<h.strength<<" Dexterity "<<h.dexterity<<" endurance "<<h.endurance<<endl
    <<" Intelligence "<<h.intelligence<<" charsima "<<h.charisma<<endl;
    h.save(h.characterName);
    saveInventory(h.characterName);
}
