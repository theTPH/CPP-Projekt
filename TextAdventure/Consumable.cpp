#include "Consumable.h"

// consumable items, not in game / first draft

Consumable::Consumable(std::string name, int priceBuy, int priceSell, int heal)
	: Item(name, priceBuy, priceSell)
{
	this->heal = heal;
}

Consumable::~Consumable()
{

}

Consumable* Consumable::clone() const
{
	return new Consumable(*this);
}