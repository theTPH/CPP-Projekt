#pragma once

#include<string>
#include<iostream>
#include<fstream>

// menu header

class Menu
{
	private:
		std::string name;
		std::string menu_string;
		int id;
		const std::string FILE = "menues.txt";

	public:
		Menu(std::string name = "GAME_MENU");
		virtual ~Menu();
		void init(const std::string name);

		// getters
		int const get_id() const { return this->id; };
		std::string const get_menu() const { return this->menu_string; };

};

