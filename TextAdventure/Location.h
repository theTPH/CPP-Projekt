#pragma once

#include<string>
#include<iostream>
#include<iomanip>
#include<vector>
#include<fstream>
#include<map>

class Location
{
	private:
		int id;
		std::string name;
		std::string description;
		
		std::map<std::string, int> destinations;
		std::map<std::string, int> npcs;
		std::map<std::string, int> poi;

		int option_decision_id;
		int init_ev_id;

		const std::string DEST = "DEST";
		const std::string NPCS = "NPCS";
		const std::string POI = "POI";
		const std::string EV = "EV";

		const std::string LOC_FILE = "locations.txt";
		const std::string DEST_FILE = "destinations.txt";
		const std::string NPCS_FILE = "npcs.txt";
		const std::string POI_FILE = "poi.txt";
		const std::string INIT_EV_FILE = "init_events.txt";

	public:
		Location(int id = 1);
		virtual ~Location();
		void init(const int id = 1);
		
		// functions
		void swap_location(int id);
		int choose_option(std::string type, std::string additional_option);
		void changeLocation(int dest_id);
		void talk_to_npc();
		int look_at();
		int check_for_init_event();

		// getters
		std::string getLocation();
		inline int const get_init_ev_id() const { return this->init_ev_id; };

		// setters
		void setLocationOptions(std::string file, std::string type, std::map<std::string, int> *options);
};

