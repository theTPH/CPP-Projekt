#include "character.hpp"

//constructors
Character::Character()
{
    Attributes attr = Attributes(0, 0, 0);
    this->attributes = attr;
    this->name = "";
    this->xp = 0;
    this->xp_lvl_up = 50;
    this->lvl = 1;
}

Character::Character(Attributes attr, string name)
{
    this->attributes = attr;
    this->name = name;
    this->xp = 0;
    this->xp_lvl_up = 50;
    this->lvl = 1;
}

//methods
void Character::level_up_system(int xp)
{
    /*
    This is the method for the level up system in the game. It can be called wehnever the player gets experience.
    The method ads that experience and checks if a level up available.
    params xp: int - amount of xp given to the character
    */
    int current_xp = this->get_xp() + xp;
    int lvl =  this->get_lvl();
    int xp_lvl_up = this->get_xp_lvl_up() + 50; //sets the amount of xp needed for next lvl up
    bool answer_valid = false;
    string answer = "";

    this->set_xp(current_xp);
    if (current_xp >= this->get_xp_lvl_up())
    {
        lvl = lvl + 1; 
        this->set_lvl(lvl);
        this->set_xp_lvl_up(xp_lvl_up);
        this->set_xp(current_xp - this->get_xp_lvl_up());
        cout << "YAY du bis ein LVL Aufgestiegen! Du bist jetzt LVL " << lvl << "." << endl;
        cout << "Du kannst jetzt einen Attributspunkt vergeben." << endl;
        while(!answer_valid)
        {
            cout << "In welches Attribut moechtest du deine Punkt investieren?" << endl;
            cout << "Staerke [S], Lebenskraft [L], Geschicklichkeit [G]" << endl;
            cin >> answer;
            if (answer == "S" || answer == "s")
            {
                int old_st = this->get_attributes().get_strength();
                int new_st = old_st + 1;
                Attributes new_att = Attributes(new_st, this->get_attributes().get_health(), this->get_attributes().get_dexterty(), this->get_attributes().get_livepoints());
                this->set_attributes(new_att);
                this->get_attributes().print_attributes();
                answer_valid = true;
            }else if (answer == "L" || answer == "l")
            {
                int old_he = this->get_attributes().get_health();
                int new_he = old_he + 1;
                int new_le = this->get_attributes().get_livepoints() + 3;
                Attributes new_att = Attributes(this->get_attributes().get_strength(), new_he, this->get_attributes().get_dexterty(),new_le);
                this->set_attributes(new_att);
                this->get_attributes().print_attributes();
                answer_valid = true;
            }else if (answer == "G" || answer == "g")
            {
                int old_de = this->get_attributes().get_dexterty();
                int new_de = old_de + 1;
                Attributes new_att = Attributes(this->get_attributes().get_strength(), this->get_attributes().get_health() , new_de, this->get_attributes().get_livepoints());
                this->set_attributes(new_att);
                this->get_attributes().print_attributes();
                answer_valid = true;
            }else
            {
                cout << "Deine Eingabe war leider ungueltig. Bitte gebe 'S', 'L' oder 'G' ein." << endl;
            }  
        }
    }else
    {
        cout << "Glueckwunsch! du hast " << xp << " Erfahrungspunkte verdient." << endl;
        cout << "Dir fehlen noch " << this->get_xp_lvl_up() - current_xp << " Erfahrungspunkte zum naechsten LVL." << endl;
        this->set_xp(current_xp);
    }
}


// get and set
void Character::set_attributes(Attributes attr)
{
    this->attributes = attr;
}

Attributes Character::get_attributes()
{
    return this->attributes;
}

string Character::get_name()
{
    return this->name;
}

void Character::set_xp(int xp)
 {
     this->xp = xp;
 }

 int Character::get_xp()
 {
     return this->xp;
 }

 void Character::set_xp_lvl_up(int xp)
 {
     this->xp_lvl_up = xp;
 }

 int Character::get_xp_lvl_up()
 {
     return this->xp_lvl_up;
 }

 void Character::set_lvl(int lvl)
 {
     this->lvl = lvl;
 }

 int Character::get_lvl()
 {
     return this->lvl;
 }