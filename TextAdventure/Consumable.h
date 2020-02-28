#pragma once

#include"Item.h"

class Consumable : public Item
{
	private:
		int heal;

	public:
		Consumable(
			std::string name = "NONE",
			int priceBuy = 0,
			int priceSell = 0,
			int heal = 5);
		virtual ~Consumable();

	// virtual
	virtual Consumable* clone() const;

	// functions
	
};

