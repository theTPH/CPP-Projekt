#include "Item.h"

// item class
// not implemented in game / first draft
// could be hold by inventory

Item::Item(std::string name, int priceBuy, int priceSell)
{
	this->name = name;
	this->priceBuy = priceBuy;
	this->priceSell = priceSell;
}

Item::~Item()
{

}