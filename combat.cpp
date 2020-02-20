#include "character.hpp"
#include "attributes.hpp"
#include "combat.hpp"

Combat::Combat(Character player, Character enemy)
{
    this->player = player;
    this->enemy = enemy;
}

void execute_combat()
{
    
}

void main()
{
    Attributes att_player = Attributes(2,4,4);
    Attributes att_enemy = Attributes(3,3,3);
    Character player = Character(att_player, "player");
    Character enemy = Character(att_enemy, "enemy");

    Combat comb = Combat(player, enemy);
    comb.execute_combat();
}