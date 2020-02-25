#pragma once

#include"Inventory.h"

class Player
{
	private:
		Inventory inventory;
		Consumable consumable;
		
		std::string name;
		int level;
		int xp;
		int xpToLevelUp;

		int vitality;
		int strength;
		int dexterity;

		int health;
		int healthMax;
		int damageMin;
		int damageMax;

		int attributePoints;
		int gold;

		int posX;
		int posY;

	public:
		Player();
		virtual ~Player();

		// functions
		void init(const std::string name);
		void outputStats() const;
		void levelUp();
		std::string getAsText() const;

		// getters
		inline const std::string& getName() const { return this->name; }
		inline const int& getLevel() const { return this->level; }
		inline const int& getXp() const { return this->xp; }
		inline const int& getXpToLevelUp() const { return this->xpToLevelUp; }
		inline const int& getHealth() const { return this->health; }
		inline const int& getHealthMax() const { return this->healthMax; }
		inline const int& getStrength() const { return this->strength; }
		inline const int& getDexterity() const { return this->dexterity; }
		inline const int& getDamageMin() const { return this->damageMin; }
		inline const int& getDamageMax() const { return this->damageMax; }
		inline const double& getPosX() const { return this->posX; }
		inline const double& getPosY() const { return this->posY; }
		inline const int& get_Gold() const { return this->gold; }
	
		// setters
		void set_gold(int new_value);
};

