#include "Menu.h"

// menu class which holds active menu data

Menu::Menu(std::string name)
{
	this->name = name;
	this->menu_string = "";
	this->id = 1;
}

Menu::~Menu()
{

}

void Menu::init(const std::string name)
{
	this->name = name;
	std::ifstream input_file(this->FILE);

	// open menu file and search for specific menu
	if (input_file.is_open())
	{
		std::string current_line = "";

		while (std::getline(input_file, current_line))
		{
			std::size_t found = current_line.find(this->name);

			if (found != std::string::npos)
			{
				input_file >> this->id;

				while (std::getline(input_file, current_line) && current_line != "END")
				{
					this->menu_string += current_line + "\n";
				}

				break;
			}
		}
	}
	else
		throw("Menu loading error!");

	input_file.close();
}