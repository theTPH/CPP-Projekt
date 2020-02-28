#include "Player.h"

Player::Player()
{
	this->name = "";
	this->level = 0;
	this->xp = 0;
	this->xpToLevelUp = 0;
	
	this->vitality = 0;
	this->strength = 0;
	this->dexterity = 0;
	
	this->health = 0;
	this->healthMax = 0;	
	this->damageMin = 0;
	this->damageMax = 0;

	this->attributePoints = 0;
	this->gold = 0;

	this->posX = 0.0;
	this->posY = 0.0;
}

Player::~Player()
{

}

// functions
void Player::init(const std::string name)
{
	this->name = name;
	this->level = 1;
	this->xp = 0;
	this->xpToLevelUp = 100;
	
	this->vitality = 3;
	this->strength = 3;
	this->dexterity = 3;

	this->health = 12;
	this->healthMax = 12;
	this->damageMin = 3;
	this->damageMax = 6;

	this->attributePoints = 0;
	this->gold = 20;

	this->posX = 0.0;
	this->posY = 0.0;
}

void Player::outputStats() const
{
	std::cout << "++ Charakterwerte ++" << std::endl << std::endl;
	std::cout << "| Name: " << this->name << std::endl;
	std::cout << "| Gold: " << this->gold << std::endl;
	std::cout << "| Level: " << this->level << std::endl;
	std::cout << "| XP: " << this->xp << "/" << this->xpToLevelUp << std::endl;
	std::cout << "| HP: " << this->health << "/" << this->healthMax << std::endl;
	std::cout << std::endl;
	std::cout << "| VIT: " << this->vitality << std::endl;
	std::cout << "| STR: " << this->strength << std::endl;
	std::cout << "| DEX: " << this->dexterity << std::endl;
	std::cout << std::endl;
}	

void Player::levelUp()
{
	while (this->xp >= this->xpToLevelUp)
	{
		this->xp -= xpToLevelUp;
		this->level++;
		this->xp = 0;
		this ->xpToLevelUp = this->level*100;

		this->attributePoints += 3;
	}
}

std::string Player::getAsText() const
{
	return
		name + " "
		+ std::to_string(this->level) + " "
		+ std::to_string(this->xp) + " "
		+ std::to_string(this->vitality) + " "
		+ std::to_string(this->strength) + " "
		+ std::to_string(this->dexterity) + " "
		+ std::to_string(this->health) + " "
		+ std::to_string(this->attributePoints) + " "
		+ std::to_string(this->posX) + " "
		+ std::to_string(this->posY) + " ";
}

void Player::set_gold(int new_value)
{
	this->gold = new_value;
}