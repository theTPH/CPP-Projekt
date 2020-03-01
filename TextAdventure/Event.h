#pragma once

#include"Location.h"
#include"Character.h"

class Event
{
	private:
		int id;
		std::string text;

		std::string type_of_next;
		
		int trigger_loc_id;
		int trigger_ev_id;
		int trigger_cbt_id;
		
		bool is_finished;
		bool has_decisions;
		bool is_ev_flag;

		Location *active_location;
		std::map<std::string, int> decisions;

		const std::string LOC = "LOC";
		const std::string EV = "EV";
		const std::string CBT = "CBT";

		const std::string EV_FILE = "special_events.txt";
		const std::string CBT_FILE = "combats.txt";

		// special event flags -> could be more dynamically set
		bool is_ev_drunk;
		bool is_ev_helped;
		bool is_ev_combat_forest;
		bool is_ev_combat_cave;
		bool is_ev_combat_village;
		bool is_ev_quest_accepted;
		bool is_ev_quest_crafted;
		bool is_ev_quest_ship;
		bool is_ev_quest_told;
		bool is_ev_quest_captain;
		

	public:
		Event(int id = 0);
		virtual ~Event();
		void init(const int id = 0, Location *active_location = nullptr);

		// functions
		void swap_event(int id, Location *active_location);
		void choose_event(int decision_id);
		std::string init_combat(Attributes *enemy_attributes);
		bool check_for_special_event_execution(int id);

		// getters
		inline int const get_event_id() const { return this->id; }
		void get_event(Location *current_location = nullptr);
		inline bool const get_is_finished() const { return this->is_finished; };
		inline int const get_combat_id() const { return this->trigger_cbt_id; }
		inline bool const get_is_finale() const { return this->is_ev_quest_ship; }
};

