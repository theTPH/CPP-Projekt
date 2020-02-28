#pragma once
#include "Attributes.h"

class Character
{
private:
	Attributes attributes = Attributes(0, 0, 0);
	string name;
	int xp;
	int xp_lvl_up;
	int lvl;

public:
	//constructors
	Character();
	Character(Attributes, string);
	
	//methods
	void level_up_system(int);
	
	// get and set
	void set_attributes(Attributes);
	Attributes get_attributes();
	void set_name(string);
	string get_name();
	void set_xp(int);
	int get_xp();
	void set_xp_lvl_up(int);
	int get_xp_lvl_up();
	void set_lvl(int);
	int get_lvl();
};

