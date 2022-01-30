#ifndef HERO_H
#define HERO_H
#include"Characters.h"
#include "Slist.h"
//#include "Dlist.h"

using std::string;
using std::stringbuf;

class Hero : public Characters, public AbsAttributes{

	private:
		int points;
		int level;

		void setAttributes(int str, int dex, int end, int intl, int cha);


	public:
		Hero();
		void createCharacter(string name);
		void save(string name);
		void load(string name);
        void setAttributes();
        void loadAttributes(string name);
        ~Hero();


	friend class Mage;
	friend class Warrior;
	friend class Berserker;
	friend class Thief;

    template <class T>
    friend class Fight;

    friend class Dlist;
};

class Mage : public AbsAttributes{
	public:
		Mage(Hero &m);
};

class Warrior : public AbsAttributes{
	public:
		Warrior(Hero &w);
};

class Berserker : public AbsAttributes{
	public:
		Berserker(Hero &b);
};

class Thief : public AbsAttributes{
	public:
		Thief(Hero &th);
};

class Monsters : public Hero {
	public:
		void addMonsters();
		~Monsters();
    //template <class T>
    //friend class Fight;
};

template <class T>
class Fight{
     public:
        //Fight(Hero &fighter1, Monsters &fighter2);
        bool duel(Hero &fighter1, Monsters &fighter2);
        T attackPower(int strength, int intelligence);
        T damage(int attack, int dexterity, int intelligence);
};

#endif // HERO_H

