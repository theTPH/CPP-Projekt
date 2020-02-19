#include "attributes.hpp"

Attributes::Attributes(int strength, int health, int dexterty)
 {
     this->strength = strength;
     this->health = health;
     this->dexterty = dexterty;
 }

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