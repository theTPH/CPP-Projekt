#include "Inventory.h"

// inventory class
// not implemented in game / first draft

Inventory::Inventory()
{
	this->size = 5;
	this->amount = 0;
	this->items = new Item*[this->size];
	this->init();
}

Inventory::~Inventory()
{
	for (size_t i = 0; i < this->amount; i++)
	{
		delete this->items[i];
	}

	delete[] items;
}

Inventory::Inventory(const Inventory &obj)
{
	this->size = obj.size;
	this->amount = obj.amount;
	this->items = new Item*[this->size];

	for (size_t i = 0; i < this->amount; i++)
	{
		this->items[i] = obj.items[i]->clone();
	}

	this->init(this->amount);
}

Item& Inventory::operator[](const int index)
{
	if (index < 0 || index >= this->amount)
	{
		throw("Index Error!");
	}
	return *this->items[index];
}

void Inventory::init(const int start)
{
	for (size_t i = start; i < this->size; i++)
	{
		this->items[i] = nullptr;
	}
}

void Inventory::add(const Item &item)
{
	if (this->amount >= this->size)
	{
		extend();
	}

	this->items[this->amount++] = item.clone();
}

void Inventory::remove(int index)
{

}

void Inventory::extend()
{
	this->size *= 2;
	Item **temp = new Item*[this->size];

	for (size_t i = 0; i < this->amount; i++)
	{
		temp[i] = this->items[i];
	}

	delete[] this->items;
	this->items = temp;
	this->init(this->amount);
}

