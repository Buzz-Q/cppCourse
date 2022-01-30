#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <bits/stdc++.h>
#include <cstdlib>
#include <ctime>
#include <cmath>

#include"Hero.h"
#include"cushion.h"
#include"Characters.h"
#include "Slist.h"
#include "Dlist.h"

using namespace std;

int main(){

	int in, loop = 1;
	int pro;

	// For inventroy
	std::string drops[8] = {"Armor", "Ring ", "Wand" ,"Wand", "Sword", "Ring", "Nothing", "Nothing"};
    srand(time(0));
    std::string pickedItem;


	cushion cu;
    Slist s;
    Dlist d;

	string username, filename, name, data;
	//for fights
	string heroName, monsterName;

	cout<<"Welcome!\n";

	while(loop){

        Hero h;
        Monsters m;
        //Slist s;

		cout<<"What would you like to do?\n";
		cout<<"1. New Character\n"<<"2. Load Data\n"<<"3. Create monsters\n"<<
        "4. Begin a fight\n"<<"5. Equip/Disequip/drop items\n"<<"0. Quit\n";
		in = cu.intPut();

		switch (in){
			case 0:
				cout<<"shutdown!\n";
				loop = 0;
				break;
			case 1:
			{
				ofstream c;

				cout<<"Enter character's name"<<endl;
				cin>>username;
				name = username;
				filename=username+".txt";
				c.open(filename.c_str());

				if(c.good()){
					cout<<"Character created successfully\n";
				}else{
					cout<<"Failed, please try again";
					break;
				}

				c.close();

				Characters *username = &h;
				username->createCharacter(name);

				cout<<"Select your hero's profession\n"<<
				"1. Mage\n"<<"2. Warrior\n"<<"3. Berserker\n"<<"4. Thief\n";
				pro = cu.intPut();

				switch (pro){
					case 1:
						{
							Mage p(h);
							break;
						}
					case 2:
						{
							Warrior p(h);
							break;
						}
					case 3:
						{
							Berserker p(h);
							break;
						}
					case 4:
						{
							Thief p(h);
							break;
						}
					default:
						{
							cout<<"invalid input";
							break;
						}

				}

				int x;
				cout<<"Would you like to save your character?\n"<<"1. Yes\n"<<"2. No\n";
				x = cu.intPut();

				switch (x){
					case 1: {
						username->save(name);
						cout<<"Character saved\n";
						break;
					}
					case 2: {
						cout<<"Changes not saved\n";
						break;
					}
					default : {
						//cout<<"Wrong input\n";
						break;
					}
				}
				break;
			}

			case 2:
			{
				cout<<"Enter character's name\n";
				cin>>username;
				name = username;
                Characters *username = & h;
                username->load(name);
                username->loadAttributes(name);
				break;
			}
			case 3:
			{
				m.addMonsters();
				cout<<"Monsters saved\n";
				break;
			}
			case 4:
            {
                Characters *name1 = &h;
                Characters *name2 = &m;

                cout<<"Pick your hero\n";
                cin>>heroName;
                name1->loadAttributes(heroName);
                s.loadHistory(heroName);
                d.loadInventory(heroName);


                cout<<"Pick a Monster to fight\n";
                cin>>monsterName;
                name2->loadAttributes(monsterName);

                Fight <float> f;
                node *result = new node;

                result->monster = monsterName;
                result->win = f.duel(h, m);

                if(result->win){
                    string dropped = drops[rand()%8];
                    cout<<monsterName<<" Dropped: "<<dropped<<endl;
                    if(dropped != "Nothing"){
                        cout<<"Would you like to pick it up?\n1.Yes\n2.No\n";
                        if(cu.intPut() == 1){
                            dnode *value = new dnode;
                            value->item = dropped;
                            d.pushEnd(value);
                        }
                    }
                }

                int pick;
                cout<<"Would you like to save progress?\n";
                cout<<"1. Yes\n"<<"2. No\n";


                if(cu.intPut() != 1){
                    continue;
                }else{
                    name1->save(heroName);
                    d.loadInventory(h.characterName);
                    s.pushHead(result);
                    s.saveHistory(h.characterName);
                    s.allHistory();

                    d.saveInventory(h.characterName);
                    //s.size();

                }
                break;
            }
            case 5:
            {
                int l = 1;
                int a;
                while(l != 0){
                    cout<<"Pick a Hero: ";
                    cin>>name;
                    h.loadAttributes(name);
                    d.loadInventory(name);
                    d.display();
                    cout<<"Pick an item\n";
                    cin>>pickedItem;

                    dnode *p = new dnode;
                    p = d.searchItem(pickedItem, d.dhead);
                    //if((pickedItem != "Armor") || (pickedItem != "Sword") || (pickedItem != "Wand") || (pickedItem != "Ring")){
                    if(p){
                        cout<<"You have picked "<<pickedItem<<endl;
                        cout<<"1. Equip\n 2. Disequip\n 3. Drop\n";
                        a = cu.intPut();
                        switch (a){
                        case 1: {
                            d.equip(h, p);
                            break;
                        }
                        case 2: {
                            d.disequip(h, p);
                            break;
                        }
                        case 3: {
                            d.pop(p->item);
                            break;
                        }
                        default:{} //cout<<"Wrong entry\n";
                        }
                    }else{cout<<"\nThere seem to be a typo or inexistent item, please try again\n";}
                    cout<<"Press 0 to exit or any other number to continue";
                    l = cu.intPut();
                }
                break;
            }
			default:
				//cout<<"\ninvalid input!\n";
				break;
		}
        h.~Hero();
        m.~Monsters();
        //s.~Slist();

	}

	return 0;
}
