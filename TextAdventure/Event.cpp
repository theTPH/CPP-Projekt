#include "Event.h"

// event class for general, npc, poi, init and combat events in game

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
	
	this->is_ev_flag = false;
	this->is_ev_drunk = false;
	this->is_ev_helped = false;
	this->is_ev_combat_forest = false;
	this->is_ev_combat_cave = false;
	this->is_ev_combat_village = false;
	this->is_ev_quest_accepted = false;
	this->is_ev_quest_crafted = false;
	this->is_ev_quest_ship = false;
	this->is_ev_quest_told = false;
	this->is_ev_quest_captain = false;
}

Event::~Event()
{

}

// initialize event with specific id

void Event::init(const int id, Location *activeLocation)
{
	this->id = id;
	this->active_location = activeLocation;
	int number_of_decisions = 0;
	this->is_finished = false;
	this->has_decisions = false;
	this->is_ev_flag = false;

	this->decisions.clear();
	std::ifstream input_file(this->EV_FILE);
	std::string key = "EV" + std::to_string(this->id);

	// open event file and search for specific event
	if (input_file.is_open())
	{
		std::string current_line = "";

		while (std::getline(input_file, current_line))
		{
			std::size_t found = current_line.find(key);

			if (found != std::string::npos)
			{
				std::getline(input_file, this->text);
				input_file >> number_of_decisions;
				input_file.ignore();

				// are there any decisions to make
				if (number_of_decisions > 0)
				{
					std::string option_text = "";
					int option_id = 0;
					
					// read in decisions to map
					while (std::getline(input_file, current_line) && current_line != "END")
					{
						option_text = current_line;
						input_file >> option_id;
						input_file.ignore();
						this->decisions[option_text] = option_id;
					}
					
					this->has_decisions = true;
				}
				// or just passive event
				else
				{
					std::getline(input_file, this->type_of_next);

					// just next event?
					if (this->type_of_next == this->EV) input_file >> this->trigger_ev_id;
					
					// change of location?
					if (this->type_of_next == this->LOC)
					{
						input_file >> this->trigger_loc_id;
						if((*this->active_location).get_location_id() != this->trigger_loc_id)
						(*this->active_location).init(this->trigger_loc_id);
					}

					// going into combat?
					if (this->type_of_next == this->CBT) input_file >> this->trigger_cbt_id;

					// is event finished?
					int finished = 0;
					input_file.ignore();
					input_file >> finished;
					if (finished != 0) this->is_finished = true;

					// is flag event?
					int flag = 0;
					input_file.ignore();
					input_file >> flag;
					if (flag != 0) this->is_ev_flag = true;
				}
				break;
			}
		}
	}
	else
		throw("Event loading error!");
	
	input_file.close();
}

void Event::get_event(Location *current_location)
{
	//check for flags -> look for more dynamic solution with files maybe?
	switch (this->id)
	{
		// drinking event
		case 2:
			if (this->is_ev_drunk)
			{
				this->swap_event(80, this->active_location);
				return;
			}
			break;
		// talk with fisher
		case 5:
			if (this->is_ev_helped)
			{
				this->swap_event(81, this->active_location);
				return;
			}
			break;
		// take/update quest 
		case 12:
			if (this->is_ev_quest_accepted)
			{
				if (this->is_ev_quest_crafted)
				{
					if (this->is_ev_quest_ship)
					{
						if (this->is_ev_quest_captain) this->swap_event(19, this->active_location);
						else this->swap_event(18, this->active_location);
					}
					else this->swap_event(17, this->active_location);
				}
				else this->swap_event(16, this->active_location);
				return;
			}
			break;
		// able to craft pots?
		case 25:
			// already crafted pots
			if (this->is_ev_quest_accepted)
			{
				if (is_ev_quest_crafted) this->swap_event(30, this->active_location); 
				else this->swap_event(26, this->active_location);
				return;
			}
			break;
		// crafted pots? ship already landed
		case 40:
			if (this->is_ev_quest_ship) this->swap_event(46, this->active_location);
			else if (this->is_ev_quest_crafted) this->swap_event(41, this->active_location);
			return;
			break;
		// got robbed before?
		case 70:
			if (this->is_ev_quest_told || (!this->is_ev_drunk && !this->is_ev_quest_told))
			{
				this->swap_event(73, this->active_location);
				return;
			}
			break;
		default:
			break;
	}
	
	std::cout << this->text << std::endl;
	std::cout << std::endl;
	std::cout << "Weiter ..." << std::endl;
	std::cout << std::endl;
	std::cin.ignore();

	// if option has decisions...
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

	// is there a follow up event?
	else if (!this->is_finished && this->type_of_next == this->EV)
	{
		this->swap_event(this->trigger_ev_id, this->active_location);
	}

	// check for flag events -> should be done more dynamically
	else if (this->is_ev_flag)
	{
		switch (this->id)
		{
			case 8:
				this->is_ev_helped = true;
				break;
			case 10:
				this->is_ev_drunk = true;
				break;
			case 14:
				this->is_ev_quest_accepted = true;
				break;
			case 18:
				/*this->is_ev_quest_told = true;*/
				break;
			case 28:
				this->is_ev_quest_crafted = true;
				break;
			case 44:
				this->is_ev_quest_ship = true;
				break;
			case 57:
				this->is_ev_quest_captain = true;
				break;
			case 72:
				this->is_ev_quest_told = true;
				break;
			default:
				break;
		}
	}
}

void Event::swap_event(int id, Location *active_location)
{
	// swapping the active event by id and location

	if (this->id != id)
	{
		this->init(id, active_location);
	}
	std::cin.clear();
	this->get_event(this->active_location);
}

void Event::choose_event(int decision_id)
{
	// swap event based on decision
	std::map<std::string, int>::iterator it = this->decisions.begin();
	for (size_t i = 1; i < decision_id; i++) it++;
	this->swap_event(it->second, this->active_location);
}

std::string Event::init_combat(Attributes *enemy_attributes)
{
	// set combat flag
	switch (this->trigger_cbt_id)
	{
		case 1:
			this->is_ev_combat_forest = true;
			break;
		case 2:
			this->is_ev_combat_cave = true;
			break;
		case 3:
			this->is_ev_quest_captain = true;
			break;
		default:
			break;
	}
	
	// set attributes by id
	std::ifstream input_file(this->CBT_FILE);
	std::string key = this->CBT + std::to_string(this->trigger_cbt_id);

	std::string enemy_name = "";
	std::string enemy_text = "";
	int enemy_str = 0;
	int enemy_hp = 0;
	int enemy_dxt = 0;

	// open file and search for specific combat data
	if (input_file.is_open())
	{
		std::string currentLine = "";

		while (std::getline(input_file, currentLine))
		{
			std::size_t found = currentLine.find(key);

			if (found != std::string::npos)
			{
				std::getline(input_file, enemy_name);
				std::getline(input_file, enemy_text);
				input_file >> enemy_str;
				input_file >> enemy_hp;
				input_file >> enemy_dxt;
				input_file.ignore();
				break;
			}
		}
	}
	else
		throw("Combat loading error!");
	
	//set enemy attributes and return enemy name
	(*enemy_attributes).set_strenght(enemy_str);
	(*enemy_attributes).set_health(enemy_hp);
	(*enemy_attributes).set_dexterty(enemy_dxt);
	(*enemy_attributes).set_lifepoints(enemy_hp * 3);

	input_file.close();

	std::cout << enemy_text << std::endl;
	std::cout << std::endl;

	return enemy_name;
}
bool Event::check_for_special_event_execution(int id)
{
	bool is_already_executed = false;

	// check if event already executed
	switch (id)
	{
		case 11:
			if (this->is_ev_combat_forest) return true;
			break;
		case 44:
			if (this->is_ev_combat_cave) return true;
			break;
		case 53:
			if (this->is_ev_combat_village) return true;
			break;
		default:
			break;
	}
	return is_already_executed;
}