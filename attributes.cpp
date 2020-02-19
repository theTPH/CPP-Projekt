#include<iostream>
#include "attributes.hpp"
using namespace std;

//constructor
Attributes::Attributes(int strength, int health, int dexterty)
 {
     this->strength = strength;
     this->health = health;
     this->dexterty = dexterty;
 }


//methods
void Attributes::initial_attribute_select()
{
    int max_attributes = 10;
    int all_attributes = 0;
    int attributes_left = 0;
    int strength = 0;
    int health = 0;
    int dexterty = 0;
    bool points_valid = false;
    string answer_att = "";

    cout << "Heyho herzlich Willkommen in deinem Abenteuer!" << endl;
    cout << "Gleich kann es los gehen. Doch bevor du dich in dein Abenteuer stürzen kannst musst du noch deine Attributspunkte verteilen." << endl;
    cout << "Was Attributspunkte sind weißt du doch oder? [ J ; N ]" << endl;
    cin >> answer_att;
    if (answer_att.compare("J") || answer_att.compare("j"))
    {
        cout << "Super! Dann legen wir direkt los." << endl;
    }else if (answer_att.compare("N") ||  answer_att.compare("j"))
    {
        cout << "Okay. Attribute beschreiben die Kernkompetenzen deines Charakters." << endl;
        cout << "Mithilfe von Attributspunkten kannst du diese Attribute steigern." << endl;
    }else
    {
        cout << "Deine Eingabe war leider ungültig. Bitte gebe 'J' für Ja oder 'N' für Nein ein." << endl;
    }
    cout << "Du kannst insgesammt" << max_attributes << " Abenteuerpunkte vergeben. Die in diesem Abenteuer verwendeten Attribute sind:" << endl;
    cout << "Stärke: Dieses Attribut bestimmt deinen Schaden im Kampf." << endl;
    cout << "Lebenskraft: Bestimmt die Anzahl deiner Lebenspunkte (LE*3)" << endl;
    cout << "Geschicklichkeit: Beieinflusst deine Position im Kampf und die Möglichkeit Gefahren auszuweichen" << endl;
    cout << "Gib jetzt bitte deine Stärke ein [1 bis 8]" << endl;
    cin >> strength;
    if (strength > 1 && strength < 8)
    {
        cout << "Stärke: " << strength << endl;
    }else
    {
        cout << "Deine EIngabe war leider ungültig. Bitte gebe eine Zahl von 1-8 ein." << endl;
    }
    
    




    while(!points_valid)
    {
        all_attributes = strength + health + dexterty;
        if (all_attributes == 10)
        {   
            set_strenght(strength);
            set_health(health);
            set_dexterty(dexterty);
            points_valid = true;
        }else if (all_attributes < 10)
        {
            cout << "Du hast nicht alle deine Attributspunkte vergeben..." << endl;
            cout << "Du solltest alle deine Punkte vergeben wenn du hier eine Chance haben willst!" << endl;
        }else if (all_attributes > 10)
            cout << "Du hast zu viele Attributspunkte vergeben." << endl;
            cout << "Dir stehen nur " << max_attributes << " Punkte zur Verfügung." << endl;
    }
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

int main()
{
    Attributes attr = Attributes(0, 0, 0);
    attr.initial_attribute_select();
}