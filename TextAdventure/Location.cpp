#include "Location.h"

Location::Location(int id)
{
	this->id = id;
	this->name = "NONE";
	this->description = "NONE";
	this->option_decision_id = 0;
	this->init_ev_id = 0;
}

Location::~Location()
{

}

void Location::init(const int id)
{
	this->id = id;
	this->name = "";
	this->description = "";

	std::ifstream inputFile(this->LOC_FILE);
	std::string key = "LOC" + std::to_string(this->id);

	if (inputFile.is_open())
	{
		std::string currentLine = "";

		while (std::getline(inputFile, currentLine))
		{
			std::size_t found = currentLine.find(key);

			if (found != std::string::npos)
			{
				std::getline(inputFile, this->name);
				std::getline(inputFile, this->description);
				break;
			}
		}
	}
	else
		throw("Location loading error!");

	inputFile.close();
	this->setLocationOptions(DEST_FILE, this->DEST, &this->destinations);
	this->setLocationOptions(NPCS_FILE, this->NPCS, &this->npcs);
	this->setLocationOptions(POI_FILE, this->POI, &this->poi);
	this->init_ev_id = this->check_for_init_event();
}

std::string Location::getLocation() 
{
	std::string location = 
		"Ort: " + this->name + "\n"
		+ this->description + "\n";

	return location;
}

void Location::swap_location(int id)
{
	if (this->id != id)
	{
		this->init(id);
	}
}

void Location::setLocationOptions(std::string file, std::string type, std::map<std::string, int> *options)
{
	std::ifstream inputFile(file);
	(*options).clear();

	std::string key = type + std::to_string(this->id);

	std::string option_text = "NONE";
	int option_id = 0;

	if (inputFile.is_open())
	{
		std::string currentLine = "";

		while (std::getline(inputFile, currentLine))
		{
			std::size_t found = currentLine.find(key);

			if (found != std::string::npos)
			{
				while (std::getline(inputFile, currentLine) && currentLine != "END")
				{
					option_text = currentLine;
					inputFile >> option_id;
					inputFile.ignore();
					(*options)[option_text] = option_id;
				}
				break;
			}
		}
	}
	else
		throw("Destination loading error!");

	inputFile.close();
}

int Location::choose_option(std::string type, std::string additional_option)
{
	std::map<std::string, int> *options = nullptr;
	if (type == this->DEST) options = &this->destinations;
	else if (type == this->NPCS) options = &this->npcs;
	else if (type == this->POI) options = &this->poi;

	int next_action_id = 0;

	std::string options_text = "";
	std::map<std::string, int>::iterator it = (*options).begin();

	while (it != (*options).end())
	{
		options_text += it->first + "\n";
		it++;
	}
	
	options_text += std::to_string((*options).size()+1) + ": " + additional_option + "\n";

	std::cout << options_text << std::endl;
	
	int option_decision;
	
	std::cin >> option_decision;
	std::cout << std::endl;

	if (std::cin.fail() || option_decision > (*options).size() + 1)
	{
		std::cout << "Bitte nur eine gueltige Zahl eingeben." << std::endl;
	}

	while (std::cin.fail())
	{
		std::cin.clear();
		std::cin.ignore();
		std::cin >> option_decision;
	}

	if (!(option_decision > (*options).size() + 1) && !(option_decision < 1))
	{
		if (option_decision != (*options).size() + 1)
		{
			// different option types
			if (type == this->DEST)
			{
				this->changeLocation(option_decision);
				if (this->init_ev_id != 0) next_action_id = 5;
			}
			else if (type == this->NPCS) next_action_id = 1;
			else if (type == this->POI)
			{
				next_action_id = 3;
				this->option_decision_id = option_decision;
			}
		}
	}

	return next_action_id;
}

void Location::changeLocation(int dest_id)
{
	std::map<std::string, int>::iterator it = this->destinations.begin();
	for (size_t i = 1; i < dest_id; i++) it++;
	this->swap_location(it->second);
}

void Location::talk_to_npc()
{

}

int Location::look_at()
{
	std::map<std::string, int>::iterator it = this->poi.begin();
	for (size_t i = 1; i < this->option_decision_id; i++) it++;
	return it->second;
}

int Location::check_for_init_event()
{
	int ev_id = 0;
	std::ifstream inputFile(this->INIT_EV_FILE);

	if (inputFile.is_open())
	{
		int current_number = 0;
		inputFile >> current_number;

		while (!inputFile.eof())
		{
			if (current_number == this->id)
			{
				inputFile >> ev_id;
				break;
			}
			
			inputFile.ignore();
			inputFile >> current_number;
		}
	}
	else
		throw("Init check loading error!");
	
	inputFile.close();
	return ev_id;
}