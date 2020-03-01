#include "Attributes.h"

//constructors
Attributes::Attributes(int strength, int health, int dexterty)
{
	this->strength = strength;
	this->health = health;
	this->dexterty = dexterty;
	this->lifepoints = health * 3;
}

Attributes::Attributes(int strength, int health, int dexterty, int lifepoints)
{
	this->strength = strength;
	this->health = health;
	this->dexterty = dexterty;
	this->lifepoints = lifepoints;
}

//methods
void Attributes::initial_attribute_select()
{
	/*
	This method is used for the initial attribute select at the beginning of the game.
	The player can select his sreangth, health and dexterty value.
	*/
	int max_attributes = 10;
	int all_attributes = 0;
	int attributes_left = 0;
	int strength = 0;
	int health = 0;
	int dexterty = 0;
	int livepoints = 0;
	bool points_valid = false;
	bool answer_valid = false; // used for user input checks
	bool finished_process = false;
	string answer_att = "";
	string answer_conf = "";

	cout << "Heyho herzlich Willkommen in deinem Abenteuer!" << endl;
	//Sleep(3000); method to slow down text output and make it more rpg like
	cout << "Gleich kann es los gehen. Doch bevor du dich in dein Abenteuer stuerzen kannst musst du noch deine Attributspunkte verteilen." << endl;
	while (!answer_valid)
	{
		cout << "Was Attributspunkte sind weisst du doch oder? [ J ; N ]" << endl;
		cin >> answer_att;
		if (answer_att == "J" || answer_att == "j")
		{
			cout << "Super! Dann legen wir direkt los." << endl;
			answer_valid = true;
		}
		else if (answer_att == "N" || answer_att == "n")
		{
			cout << "Okay. Attribute beschreiben die Kernkompetenzen deines Charakters." << endl;
			cout << "Mithilfe von Attributspunkten kannst du diese Attribute steigern." << endl;
			answer_valid = true;
		}
		else
		{
			cout << "Deine Eingabe war leider ungueltig. Bitte gebe 'J' fuer Ja oder 'N' fuer Nein ein." << endl;
		}
	}
	answer_valid = false;
	while (!finished_process)
	{
		cout << "Du kannst insgesammt " << max_attributes << " Attributspunkte vergeben. Die in diesem Abenteuer verwendeten Attribute sind:" << endl;
		cout << "Staerke: Dieses Attribut bestimmt deinen Schaden im Kampf." << endl;
		cout << "Lebenskraft: Bestimmt die Anzahl deiner Lebenspunkte (LE*3)" << endl;
		cout << "Geschicklichkeit: Beinflusst deine Chance aus einem Kampf zu fliehen und die Moeglichkeit Gefahren auszuweichen" << endl;

		while (!points_valid)
		{
			cout << "Gib jetzt bitte deine Staerke ein. [1 bis 8]" << endl;
			cin >> strength;
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(); //removes the bad input without that the input loops infinite -> took some time to find that
				cout << "Deine Eingabe war leider ungueltig. Bitte gebe eine Zahl von 1-8 ein." << endl;
			}
			else if (strength >= 1 && strength <= 8)
			{
				cout << "Staerke: " << strength << endl;
				points_valid = true;
			}
			else
			{
				cout << "Deine Eingabe war leider ungueltig. Bitte gebe eine Zahl von 1-8 ein." << endl;
			}
		}
		points_valid = false;
		while (!points_valid)
		{
			cout << "Gib jetzt bitte deine Lebenskraft ein. [1 bis " << max_attributes - strength - 1 << "]" << endl;
			cin >> health;
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(); //removes the bad input without that the input loops infinite -> took some time to find that
				cout << "Deine Eingabe war leider ungueltig. Bitte gebe eine Zahl von 1-8 ein." << endl;

			}
			else if (health >= 1 && health <= max_attributes - strength - 1)
			{
				cout << "Lebenskraft: " << health << " Daraus resultierende Lebenspunkte: " << health * 3 << endl;
				livepoints = health * 3;
				points_valid = true;
			}
			else
			{
				cout << "Deine Eingabe war leider ungueltig. Bitte gebe eine Zahl von 1-" << max_attributes - strength - 1 << " ein." << endl;
			}
		}
		points_valid = false;
		cout << "Aufgrund deiner vorherigen Angaben wird dein Geschicklichkeitswert auf " << max_attributes - strength - health << " festgelegt." << endl;
		dexterty = max_attributes - strength - health;
		cout << "Du startest dein Abenteuer also mit folgenden Attributten: " << endl;
		cout << "Staerke: " << strength << endl;
		cout << "Lebenskraft: " << health << endl;
		cout << "Lebenspunkte: " << livepoints << endl;
		cout << "Geschicklichkeit: " << dexterty << endl;
		while (!answer_valid)
		{
			cout << "Punkteverteilung bestaetigen? [J ; N]" << endl;
			cin >> answer_conf;
			if (answer_conf == "J" || answer_conf == "j")
			{
				cout << "Super! Dann kannst du dein Abenteuer jetzt beginnen!" << endl;
				cout << endl;
				set_strenght(strength);
				set_health(health);
				set_lifepoints(livepoints);
				set_dexterty(dexterty);
				answer_valid = true;
				finished_process = true;
			}
			else if (answer_conf == "N" || answer_conf == "n")
			{
				cout << "Doch so unentschlossen?... Na gut dann probieren wir das nochmal" << endl;
				answer_valid = true;
			}
			else
			{
				cout << "Deine Eingabe war leider ungueltig. Bitte gebe 'J' fuer Ja oder 'N' fuer Nein ein." << endl;
			}
		}
		answer_valid = false;
	}
}

void Attributes::print_attributes()
{
	/*
	Prints out all attributes.
	*/
	cout << "Deine Attribute sind momentan:" << endl;
	cout << "Staerke: " << this->get_strength() << endl;
	cout << "Lebenskraft: " << this->get_health() << endl;
	cout << "Lebenspunkte: " << this->get_lifepoints() << endl;
	cout << "Geschicklichkeit: " << this->get_dexterty() << endl;
}

//get and set methods
void Attributes::set_strenght(int strength)
{
	this->strength = strength;
}
int Attributes::get_strength()
{
	return this->strength;
}
void Attributes::set_health(int health)
{
	this->health = health;
}
int Attributes::get_health()

{
	return this->health;
}
void Attributes::set_dexterty(int dexterty)
{
	this->dexterty = dexterty;
}
int Attributes::get_dexterty()
{
	return this->dexterty;
}
void Attributes::set_lifepoints(int livepoints)
{
	this->lifepoints = livepoints;
}
int Attributes::get_lifepoints()
{
	return this->lifepoints;
}