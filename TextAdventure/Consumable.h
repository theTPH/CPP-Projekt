#pragma once

#include"Item.h"

// consumable items, not in game / first draft
// is an item

class Consumable : public Item
{
	private:
		int heal;

	public:
		Consumable(
			std::string name = "NONE",
			int price_buy = 0,
			int price_sell = 0,
			int heal = 5);
		virtual ~Consumable();

	// virtual
	virtual Consumable* clone() const;

};

