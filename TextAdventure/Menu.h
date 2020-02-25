#pragma once

#include<string>
#include<iostream>
#include<fstream>

class Menu
{
	private:
		std::string name;
		std::string menuString;
		int id;
		const std::string FILE = "menues.txt";

	public:
		Menu(std::string name = "GAME_MENU");
		virtual ~Menu();
		void init(const std::string name);

		// getters
		int const getId() const { return this->id; };
		std::string const getMenu() const { return this->menuString; };

};

