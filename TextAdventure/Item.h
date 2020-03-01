#pragma once

#include<iostream>
#include<iomanip>
#include<string>

// item class
// not implemented in game / first draft
// could be hold by inventory

class Item
{
	private:
		std::string name;
		int count;
		int priceBuy;
		int priceSell;

	public:
		Item(
			std::string name = "NONE",
			int priceBuy = 0,
			int priceSell = 0);
		virtual ~Item();
		virtual Item* clone() const = 0;

		// getters
		inline const std::string& getName() const { return this->name; }
		inline const int& getPriceBuy() const { return this->priceBuy; }
		inline const int& getPriceSell() const { return this->priceSell; }
};

