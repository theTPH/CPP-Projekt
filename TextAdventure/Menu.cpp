#include "Menu.h"

Menu::Menu(std::string name)
{
	this->name = name;
	this->menuString = "";
	this->id = 1;
}

Menu::~Menu()
{

}

void Menu::init(const std::string name)
{
	this->name = name;
	std::ifstream inputFile(this->FILE);

	if (inputFile.is_open())
	{
		std::string currentLine = "";

		while (std::getline(inputFile, currentLine))
		{
			std::size_t found = currentLine.find(this->name);

			if (found != std::string::npos)
			{
				inputFile >> this->id;

				while (std::getline(inputFile, currentLine) && currentLine != "END")
				{
					this->menuString += currentLine + "\n";
				}

				break;
			}
		}
	}
	else
		throw("Menu loading error!");

	inputFile.close();
}