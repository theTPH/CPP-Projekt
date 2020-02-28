#include"Game.h"

Game::Game()
{
	this->decision = 0;
	this->isRunning = true;
	this->is_game_menu_active = false;
	this->is_final_decision = true;
	this->next_action_id = 0;

	this->game_menu.init("GAME_MENU");
	this->loc_menu.init("LOCATION_MENU");
	this->dest_menu.init("DESTINATION_MENU");
	this->npcs_menu.init("NPCS_MENU");
	this->poi_menu.init("POI_MENU");

	this->main_loc.init(1);
	this->main_ev.init(1, &this->main_loc);
	
	this->active_menu = &this->loc_menu;
	this->active_location = &this->main_loc;
	this->active_event = &this->main_ev;
}

Game::~Game()
{

}

// functions
void Game::init()
{
	Inventory inventory;
	this->createNewCharacter();
	this->main_ev.getEvent(this->active_location);
}


void Game::gameMenu()
{
	if (!this->is_game_menu_active && this->is_final_decision)
	{
		cout << this->active_location->getLocation() << endl;
	}
	
	cout << this->active_menu->getMenu() << endl;

	if (this->is_final_decision)
	{
		// take input and check for non numeric
		cin >> this->decision;
		
		if (cin.fail())
		{
			cout << "Bitte nur eine Zahl eingeben." << endl;
		}
		
		while (cin.fail())
		{
			cin.clear();
			cin.ignore();
			cin >> this->decision;
		}
		
		cout << endl;
	}
		
	switch (this->active_menu->getId())
	{
		// game menu
		case 1:
			switch (this->decision)
			{
				case 1:
					this->is_game_menu_active = false;
					this->active_menu = &this->loc_menu;
					break;
				case 2:
					break;
				case 3:
					break;
				case 4:
					break;
				case 5:
					break;
				case 6:
					cin.ignore();
					this->createNewCharacter();
					break;
				case 7:
					this->isRunning = false;
					break;
				default:
					break;
			}
			break;
		
		// location menu
		case 2:
			switch (this->decision)
			{
				case 1:
					this->active_menu = &this->npcs_menu;
					this->is_final_decision = false;
					break;
				case 2:
					this->active_menu = &this->dest_menu;
					this->is_final_decision = false;
					break;
				case 3:
					this->active_menu = &this->poi_menu;
					this->is_final_decision = false;
					break;
				case 4:
					this->is_game_menu_active = true;
					this->active_menu = &this->game_menu;
					break;
				default:
					break;
			}
			break;

		// destination menu
		case 3:
			// choose where to go and change location
			this->next_action_id = this->main_loc.choose_option(this->DEST, "Hierbleiben");
			this->is_final_decision = true;
			this->active_menu = &this->loc_menu;
			break;
		
		// npcs menu
		case 4:
			// choose with whom to talk
			this->next_action_id = this->main_loc.choose_option(this->NPCS, "Mit niemandem");
			this->is_final_decision = true;
			this->active_menu = &this->loc_menu;
			break;

		// poi menu
		case 5:
			// choose what to look at
			this->next_action_id = this->main_loc.choose_option(this->POI, "Nichts");
			if (this->next_action_id == 0) this->is_final_decision = true;
			this->active_menu = &this->loc_menu;
			break;

		default:
			break;
	}

	this->execute_next_action(this->next_action_id);
}

void Game::createNewCharacter()
{
	Attributes att_player = Attributes(0, 0, 0);
	att_player.initial_attribute_select();
	player_character = Character(att_player, "player");
	std::cout << "Jetzt musst du nur noch deinen Namen eingeben!" << endl;
	string name = "";
	std::cin >> name;
	player_character.set_name(name);
	std::cout << "Alles klar " << player_character.get_name() << " Dann kann es jetzt wirklich los gehen!" << endl;
}

void Game::execute_next_action(int action_id)
{
	switch (action_id)
	{
		// talk to npc
		case 1:
			break;

		// look at poi
		case 3:
			{
				(*this->active_event).swap_event((*this->active_location).look_at());
				this->active_menu = &this->loc_menu;
				this->is_final_decision = true;
				break;
			}
		// load init event
		case 5:
			{
				(*this->active_event).swap_event((*this->active_location).get_init_ev_id());
				this->active_menu = &this->loc_menu;

				// check for combat
				int combat_id = (*this->active_event).get_combat_id();
				if (combat_id != 0)
				{
					this->start_combat();
				}

				this->is_final_decision = true;
				break;
			}
		default:
			break;
	}

	this->next_action_id = 0;
}

// Combat
void Game::start_combat()
{
	// get enemy attributes ny combat id
	Attributes att_enemy = Attributes(0, 0, 0);
	string enemy_name = (*this->active_event).init_combat(&att_enemy);
	Character enemy = Character(att_enemy, enemy_name);
	
	// init and start actual combat
	Combat comb = Combat(player_character, enemy);
	bool win = false;

	win = comb.execute_combat();
	if (!win)
	{
		this->isRunning = false;
	}
	else this->player_character.level_up_system(30);
}