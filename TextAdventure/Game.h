#pragma once

#include"Combat.h"
#include"Event.h"
#include"Menu.h"

using namespace std;

class Game
{
	private:
		int decision;
		bool is_running;
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

		// main location and event
		Location main_loc;
		Event main_ev;
		
		// active pointers
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
		void game_Menu();
		void create_new_character();
		void execute_next_action(int action_id);
		void start_combat();

		// getter
		inline bool get_is_running() const { return this->is_running; }
};