#include "Event.h"

Event::Event(int id)
{
	this->id = id;
	this->text = "NONE";
	this->type_of_next = "NONE";
	this->is_finished = false;
	this->has_decisions = false;

	this->trigger_loc_id = 0;
	this->trigger_ev_id = 0;
	this->trigger_cbt_id = 0;
}

Event::~Event()
{

}

void Event::init(const int id, Location *activeLocation)
{
	this->id = id;
	this->activeLocation = activeLocation;
	int number_of_decisions = 0;
	this->is_finished = false;
	this->has_decisions = false;

	this->decisions.clear();
	std::ifstream inputFile(this->EV_FILE);
	std::string key = "EV" + std::to_string(this->id);

	// open file and search for specific event
	if (inputFile.is_open())
	{
		std::string currentLine = "";

		while (std::getline(inputFile, currentLine))
		{
			std::size_t found = currentLine.find(key);

			if (found != std::string::npos)
			{
				std::getline(inputFile, this->text);
				inputFile >> number_of_decisions;
				inputFile.ignore();

				// are there any decisions to make
				if (number_of_decisions > 0)
				{
					std::string option_text = "";
					int option_id = 0;
					
					// read in decisions to map
					while (std::getline(inputFile, currentLine) && currentLine != "END")
					{
						option_text = currentLine;
						inputFile >> option_id;
						inputFile.ignore();
						this->decisions[option_text] = option_id;
					}
					
					this->has_decisions = true;
				}
				// or just passive event
				else
				{
					std::getline(inputFile, this->type_of_next);

					// just next event ?
					if (this->type_of_next == this->EV)
					{
						inputFile >> this->trigger_ev_id;
					}
					
					// change of location ?
					if (this->type_of_next == this->LOC)
					{
						inputFile >> this->trigger_loc_id;
					}

					// going into combat?
					if (this->type_of_next == this->CBT)
					{
						inputFile >> this->trigger_cbt_id;
					}
					
					int finished = 0;
					inputFile.ignore();
					inputFile >> finished;
					if (finished != 0) this->is_finished = true;
				}
				break;
			}
		}
	}
	else
		throw("Event loading error!");
	
	inputFile.close();
}

void Event::getEvent(Location *current_location)
{
	std::cout << this->text << std::endl;
	std::cout << std::endl;
	std::cout << "Weiter ..." << std::endl;
	std::cout << std::endl;
	std::cin.ignore();

	if (this->has_decisions)
	{
		// display decisions
		std::string decisions_text = "";
		std::map<std::string, int>::iterator it = this->decisions.begin();

		while (it != this->decisions.end())
		{
			decisions_text += it->first + "\n";
			it++;
		}

		std::cout << decisions_text << std::endl;

		// make decision
		int decision_id;

		std::cin >> decision_id;
		std::cout << std::endl;

		if (std::cin.fail() || decision_id > this->decisions.size())
		{
			std::cout << "Bitte nur eine gueltige Zahl eingeben." << std::endl;
		}

		while (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore();
			std::cin >> decision_id;
		}

		// init new event based on decision
		if (!(decision_id > this->decisions.size()) && !(decision_id < 1))
		{
			this->choose_event(decision_id);
		}
	}

	/*else if (this->type_of_next == this->CBT)
	{
		
	}*/

	// is there a follow up event?
	else if (!this->is_finished && this->type_of_next == this->EV)
	{
		this->swap_event(this->trigger_ev_id);
	}

}

//void Event::trigger_next(Location *current_location)
//{
//	if (this->type_of_next == this->LOC)
//	{
//		(*current_location).swap_location(this->trigger_loc_id);
//	}
//	else if (this->type_of_next == this->EV)
//	{
//		/*this->swap_event(this->trigger_ev_id);*/
//	}
//	else if (this->type_of_next == this->CBT)
//	{
//		// implement combat trigger
//	}
//}

void Event::swap_event(int id)
{
	if (this->id != id)
	{
		this->init(id);
	}
	std::cin.clear();
	this->getEvent(this->activeLocation);
}

void Event::choose_event(int decision_id)
{
	std::map<std::string, int>::iterator it = this->decisions.begin();
	for (size_t i = 1; i < decision_id; i++) it++;
	this->swap_event(it->second);
}

std::string Event::init_combat(Attributes *enemy_attributes)
{
	// set attributes by id
	std::ifstream inputFile(this->CBT_FILE);
	std::string key = this->CBT + std::to_string(this->trigger_cbt_id);

	std::string enemy_name = "";
	std::string enemy_text = "";
	int enemy_str = 0;
	int enemy_hp = 0;
	int enemy_dxt = 0;

	// open file and search for specific combat data
	if (inputFile.is_open())
	{
		std::string currentLine = "";

		while (std::getline(inputFile, currentLine))
		{
			std::size_t found = currentLine.find(key);

			if (found != std::string::npos)
			{
				std::getline(inputFile, enemy_name);
				std::getline(inputFile, enemy_text);
				inputFile >> enemy_str;
				inputFile >> enemy_hp;
				inputFile >> enemy_dxt;
				inputFile.ignore();
				break;
			}
		}
	}
	else
		throw("Combat loading error!");
	
	(*enemy_attributes).set_strenght(enemy_str);
	(*enemy_attributes).set_health(enemy_hp);
	(*enemy_attributes).set_dexterty(enemy_dxt);
	(*enemy_attributes).set_livepoints(enemy_hp * 3);

	inputFile.close();

	std::cout << enemy_text << std::endl;
	std::cout << std::endl;

	return enemy_name;
}