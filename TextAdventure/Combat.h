#pragma once

#include"Character.h"

class Combat
{
private:
	Character player;
	Character enemy;
public:
	Combat(Character, Character); // 1v1
	bool execute_combat();
	bool attack(Character, Character);
	bool escape();
	Character get_player();
	Character get_enemy();
};

