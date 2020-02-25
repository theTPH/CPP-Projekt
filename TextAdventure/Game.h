#pragma once

#include<ctime>
#include<fstream>
#include"Funcs.h"
#include"Player.h"
#include"Combat.h"
#include"Event.h"
#include"Menu.h"
#include"Location.h"

using namespace std;

class Game
{
	private:
		int decision;
		bool isRunning;
		bool is_game_menu_active;
		bool is_final_decision;

		int next_action_id;

		const std::string LOC = "LOC";
		const std::string DEST = "DEST";
		const std::string NPCS = "NPCS";
		const std::string POI = "POI";

		Menu game_menu;
		
		// location menus
		Menu loc_menu;
		Menu dest_menu;
		Menu npcs_menu;
		Menu poi_menu;


		Menu people_menu;
		Location main_loc;
		Event main_ev;
		
		Menu *active_menu;
		Location *active_location;
		Event *active_event;

		// player
		Character player_character;
	
	public:
		Game();
		virtual ~Game();

		// functions
		void init();
		void gameMenu();
		void createNewCharacter();
		void execute_next_action(int action_id);
		void start_combat();

		// operators

		// accessors
		inline bool getIsRunning() const { return this->isRunning; }

		// modifiers

};