#pragma once

#include"Consumable.h"

class Inventory
{
	private:
		int amount;
		int size;
		Item **items;
		void init(const int start = 0);
		void extend();
	
	public:
		Inventory();
		virtual ~Inventory();
		Inventory(const Inventory &obj);

		Item& operator[](const int index);
		inline int count() const { return this->amount; };

		// functions
		void add(const Item &item);
		void remove(int index);
		
		// getter

		// setter

};

