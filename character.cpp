#include "character.hpp"

//constructors
Character::Character()
{
    Attributes attr = Attributes(0, 0, 0);
    this->attributes = attr;
    this->name = "";
    this->xp = 0;
    this->xp_lvl_up = 0;
}

Character::Character(Attributes attr, string name)
{
    this->attributes = attr;
    this->name = name;
    this->xp = 0;
    this->xp_lvl_up = 0;
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