#include "attributes.hpp"
#include "character.hpp"

Character::Character(Attributes attr)
{
    this->attributes = attr;
}

void Character::set_attributes(Attributes attr)
{
    this->attributes = attr;
}

int Character::get_attributes()
{
    return this->get_attributes;
}