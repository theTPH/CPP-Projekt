#include "Location.h"

// location class, which holds active location and basic location functions

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

// initialize location with specific location id

void Location::init(const int id)
{
	this->id = id;
	this->name = "";
	this->description = "";

	std::ifstream input_file(this->LOC_FILE);
	std::string key = "LOC" + std::to_string(this->id);

	// open location file and search for specific location
	if (input_file.is_open())
	{
		std::string current_line = "";

		while (std::getline(input_file, current_line))
		{
			std::size_t found = current_line.find(key);

			if (found != std::string::npos)
			{
				std::getline(input_file, this->name);
				std::getline(input_file, this->description);
				break;
			}
		}
	}
	else
		throw("Location loading error!");

	input_file.close();
	// set all basic location options: destinations, npcs, pois
	this->set_location_options(DEST_FILE, this->DEST, &this->destinations);
	this->set_location_options(NPCS_FILE, this->NPCS, &this->npcs);
	this->set_location_options(POI_FILE, this->POI, &this->poi);
	// check if location has init event
	this->init_ev_id = this->check_for_init_event();
}

std::string Location::get_location() 
{
	// ouput location data
	std::string location = 
		"Ort: " + this->name + "\n"
		+ this->description + "\n";

	return location;
}

void Location::swap_location(int id)
{
	//swap location based on location id
	if (this->id != id)
	{
		this->init(id);
	}
}

void Location::set_location_options(std::string file, std::string type, std::map<std::string, int> *options)
{
	std::ifstream input_file(file);
	(*options).clear();

	std::string key = type + std::to_string(this->id);

	std::string option_text = "NONE";
	int option_id = 0;

	// open specific options file (destinations, npcs, poi) and read in options
	if (input_file.is_open())
	{
		std::string current_line = "";

		while (std::getline(input_file, current_line))
		{
			std::size_t found = current_line.find(key);

			if (found != std::string::npos)
			{
				while (std::getline(input_file, current_line) && current_line != "END")
				{
					option_text = current_line;
					input_file >> option_id;
					input_file.ignore();
					(*options)[option_text] = option_id;
				}
				break;
			}
		}
	}
	else
		throw("Destination loading error!");

	input_file.close();
}

int Location::choose_option(std::string type, std::string additional_option)
{
	// options based on option type
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
	
	// output options
	options_text += std::to_string((*options).size()+1) + ": " + additional_option + "\n";
	std::cout << options_text << std::endl;
	
	// let player make decision
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

	// choose next action id based on option index and type
	if (!(option_decision > (*options).size() + 1) && !(option_decision < 1))
	{
		if (option_decision != (*options).size() + 1)
		{
			// different option types
			if (type == this->DEST)
			{
				this->change_location(option_decision);
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

void Location::change_location(int dest_id)
{
	//change location based on chosen destination
	std::map<std::string, int>::iterator it = this->destinations.begin();
	for (size_t i = 1; i < dest_id; i++) it++;
	this->swap_location(it->second);
}

int Location::talk_to_npc()
{
	// talk to npc based on chosen npc
	std::map<std::string, int>::iterator it = this->npcs.begin();
	for (size_t i = 1; i < this->option_decision_id; i++) it++;
	return it->second;
}

int Location::look_at()
{
	// look at poi based on chosen poi
	std::map<std::string, int>::iterator it = this->poi.begin();
	for (size_t i = 1; i < this->option_decision_id; i++) it++;
	return it->second;
}

int Location::check_for_init_event()
{
	int ev_id = 0;
	std::ifstream input_file(this->INIT_EV_FILE);

	//open init event file and search for specific init event
	if (input_file.is_open())
	{
		int current_number = 0;
		input_file >> current_number;

		while (!input_file.eof())
		{
			if (current_number == this->id)
			{
				input_file >> ev_id;
				break;
			}
			
			input_file.ignore();
			input_file >> current_number;
		}
	}
	else
		throw("Init check loading error!");
	
	input_file.close();
	return ev_id;
}