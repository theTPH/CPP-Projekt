#include "attributes.hpp"
#include "character.hpp"

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

void Character::set_attributes(Attributes attr)
{
    this->attributes = attr;
}

int Character::get_attributes()
{
    return this->get_attributes;
}