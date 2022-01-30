#ifndef CHARACTERS_H
#define CHARACTERS_H
#include"Hero.h"
using std::string;
using std::stringbuf;

class Characters
{
	private:
	public:
		virtual void createCharacter(string name)=0;
		virtual void save(string name)=0;
		virtual void load(string name)=0;
        virtual void loadAttributes(string name)=0;

		//virtual ~Characters();
	protected:
		virtual void setAttributes(int str, int dex, int end, int intl, int cha)=0;
		virtual void setAttributes()=0;




};

class AbsAttributes
{
	public:
	    string characterName;
		int strength;
		int dexterity;
		int endurance;
		int intelligence;
		int charisma;
		int experience;
};

#endif
