#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <bits/stdc++.h>
#include <cstdlib>
#include <ctime>
#include <cmath>

#include"cushion.h"
#include"Hero.h"
#include"Characters.h"
#include "Slist.h"
//#include "Dlist.h"
using namespace std;


void Hero::setAttributes(int str, int dex, int end, int intl, int cha){
    strength = str;
    dexterity =dex;
    endurance =end;
    intelligence = intl;
    charisma = cha;
}

Hero::Hero(){
    points = 15;

    strength = 0;
    dexterity =0;
    endurance =0;
    intelligence = 0;
    charisma = 0;

    level = 1;
    experience = 0;
}
Hero::~Hero(){}

void Hero::createCharacter(string name){
    int str, dex, end, intl, cha;
    cushion cu;

    characterName = name;
    cout<<"\nYou got 15 points to split in all attributes, use them wisely\n";
    cout<<"\nSelect desired strength: 1:10"<<endl;
    str = cu.intPut();
    while((str<0) || (str>points) || (str>10)){
        cout<< "That's out of range, please, try again\n";
        str = cu.intPut();
    }
//	strength += str;
    points -= str;

    cout<<"\nYou got "<<points<<" points left.\n";
    cout<<"\nDexterity: "<<endl;
    dex = cu.intPut();
    while((dex<0) || (dex>points) || (dex>10)){
        cout<< "That's out of range, please, try again\n";
        dex = cu.intPut();
    }
//	dexterity += dex;
    points -= dex;

    cout<<"\nYou got "<<points<<" points left.\n";
    cout<<"\nendurance: "<<endl;
    end = cu.intPut();
    while((end<0) || (end>points) || (end>10)){
        cout<< "That's out of range, please, try again\n";
        end = cu.intPut();
    }
//	endurance += end;
    points -= end;

    cout<<"\nYou got "<<points<<" points left.\n";
    cout<<"\nintelligence: "<<endl;
    intl = cu.intPut();
    while((intl<0) || (intl>points) || (intl>10)){
        cout<< "That's out of range, please, try again\n";
        intl = cu.intPut();
    }
//	intelligence += intl;
    points -= intl;

    cout<<"\nYou got "<<points<<" points left.\n";
    cout<<"\ncharisma"<<endl;
    cha = cu.intPut();
    while((cha<0) || (cha>points) || (cha>10)){
        cout<< "That's out of range, please, try again\n";
        cha = cu.intPut();
    }
//	charisma += cha;
    points -= cha;

    setAttributes(str, dex, end, intl, cha);
}

void Hero::save(string name){
    characterName = name;
    ofstream sv;
    string filename;
    filename=name+".txt";
    sv.open(filename.c_str());

        if(sv.good()){
            cout<<"Success\n";

            sv<<name<<"\nstrength: "<<strength<<
            "\ndexterity: "<<dexterity<<"\nEndurance: "<<endurance<<
            "\nintelligence: "<<intelligence<<"\nCharisma: "<<charisma<<
            "\nLevel: "<<level<<"\nExperience: "<<experience<<endl;
        }else{
            cout<<"Failed, please try again";
        }

        sv.close();

}

void Hero::load(string name){
    string filename, data;
    ifstream l;
    filename=name+".txt";
    l.open(filename.c_str());
    if(l.good()){
        characterName = name;
        cout<<"Data loaded successfully\n";

        while(!l.eof()){
            getline(l, data);
            cout<<data<<endl;
        }
    }else{
        cout<<"Character doesn't exist, please check your spelling and try again\n";
        }
    l.close();
}



void Hero::setAttributes(){
    srand(time(0));
    strength = 1+(rand()%10);
    dexterity =1+(rand()%10);
    endurance =1+(rand()%10);
    intelligence = 1+(rand()%10);
    charisma = 1+(rand()%10);
}

void Hero::loadAttributes(string filename){
    string data;
    filename = filename + ".txt";
    int i = 0, k;
    ifstream r;
    r.open(filename.c_str());
    if(r.good()){
        while(!r.eof()){
            r>>data;
            if(i == 0){characterName = data; i++;}
            istringstream(data)>>k;
            if((k != 0) || data == "0"){
                switch (i){
                    case 1:{strength = k;   break;}
                    case 2:{dexterity = k;  break;}
                    case 3:{endurance = k;  break;}
                    case 4:{intelligence= k;break;}
                    case 5:{charisma = k;  break;}
                    case 6:{level = k;     break;}
                    case 7:{experience = k;break;}
                    default:{break;}
                }
                ++i;
            }
        }
    }
    r.close();
    cout<<"characterName: "<<characterName<<endl;
    cout<<"Strength: "<<strength<<endl;
    cout<<"Dexterity: "<<dexterity<<endl;
    cout<<"Endurance: "<<endurance<<endl;
    cout<<"Intelligence: "<<intelligence<<endl;
    cout<<"Charisma: "<<charisma<<endl;
    cout<<"Level: "<<level<<endl;
    cout<<"Experience: "<<experience<<endl;
}

Mage::Mage(Hero &m){
    m.intelligence += 3;
}


Warrior::Warrior(Hero &w){
    w.endurance += 3;
}

Berserker::Berserker(Hero &b){
    b.strength += 3;
}

Thief::Thief(Hero &th){
    th.dexterity += 3;
}

void Monsters::addMonsters(){
    string monsterName;
    for(int i = 0; i<5; i++){
        cout<<"give the monster a name: ";
        cin>>monsterName;
        cout<<endl;

        setAttributes();
        save(monsterName);
    }
}
Monsters::~Monsters(){}

template <class T>
bool Fight<T>::duel(Hero &fighter1, Monsters &fighter2){

    int end1 = fighter1.endurance;
    int end2 = fighter2.endurance;

    int str1 = fighter1.strength;
    int str2 = fighter2.strength;

    int attackPower1, attackPower2;
    //Strength and intelligence increase attack power
    //Dextriety and intelligence decrease the damage received
    //Endurance affects how many times the character can attack before they're out of energy

    while((end1 > 0) && (end2 > 0) && (str1 > 0) && (str2 >0)){
        attackPower1 = attackPower(str1, fighter1.intelligence);
        attackPower2 = attackPower(str2, fighter2.intelligence);

        str1 -= damage(attackPower2, fighter1.dexterity, fighter1.intelligence);
        str2 -= damage(attackPower1, fighter2.dexterity, fighter2.intelligence);
    }
    if((end1 < 0) || (str1 < 0)){
        cout<<fighter2.characterName<<" won\n";
        cout<<fighter1.characterName<<" lost\n";
        return false;
    }else{
        cout<<fighter1.characterName<<" won\n";
        cout<<fighter2.characterName<<" lost\n";
        if (fighter1.experience < 90){
            fighter1.experience = fighter1.experience + 10;
        }else{
            ++fighter1.level;
            ++fighter1.strength;
            ++fighter1.dexterity;
            ++fighter1.endurance;
            ++fighter1.intelligence;
            ++fighter1.charisma;
            fighter1.experience = fighter1.experience + 10 - 100;

        }
        cout<<fighter1.characterName<<"'s current level is "<<fighter1.level
        <<" with "<<fighter1.experience<<" experience\n\n--------\n\n";
        return true;
    }


}


template <class T>
T Fight<T>::attackPower(int strength, int intelligence){
return floor(strength + 0.75 * intelligence);
}

template <class T>
T Fight<T>::damage(int attack, int dexterity, int intelligence){
return floor(attack/(dexterity+intelligence));
}

template class Fight<float>;
template class Fight<double>;
template class Fight<int>;

