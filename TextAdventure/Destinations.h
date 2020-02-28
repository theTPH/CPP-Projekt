#pragma once

#include<string>
#include<iostream>
#include<iomanip>
#include<vector>
#include<fstream>
#include<map>

class Destinations
{
	private:
		int loc_id;
		std::map <std::string, int> destination_details;

	public:
		Destinations(int loc_id = 0);
		virtual ~Destinations();
		void init(const int loc_id);
};

