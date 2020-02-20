#include "attributes.hpp"
#include "character.hpp"

//constructors
Character::Character()
{
    Attributes attr = Attributes(0, 0, 0);
    this->attributes = attr;
}

Character::Character(Attributes attr, string name)
{
    this->attributes = attr;
    this->name = name;
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