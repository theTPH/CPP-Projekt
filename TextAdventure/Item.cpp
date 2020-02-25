#include "Item.h"

Item::Item(std::string name, int priceBuy, int priceSell)
{
	this->name = name;
	this->priceBuy = priceBuy;
	this->priceSell = priceSell;
}

Item::~Item()
{

}