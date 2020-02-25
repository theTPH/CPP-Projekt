#pragma once

#include<string>
#include<iostream>
#include<fstream>
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

		Location *activeLocation;
		std::map<std::string, int> decisions;

		const std::string LOC = "LOC";
		const std::string EV = "EV";
		const std::string CBT = "CBT";

		const std::string EV_FILE = "special_events.txt";
		const std::string CBT_FILE = "combats.txt";


	public:
		Event(int id = 0);
		virtual ~Event();
		void init(const int id = 0, Location *activeLocation = nullptr);

		// functions
		void swap_event(int id);
		void choose_event(int decision_id);
		std::string init_combat(Attributes *enemy_attributes);

		// getters
		void getEvent(Location *current_location = nullptr);
		inline bool const get_is_finished() const { return this->is_finished; };
		inline int const get_combat_id() const { return this->trigger_cbt_id; }

		
};

