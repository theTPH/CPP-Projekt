#include "character.hpp"
#include "attributes.hpp"
#include "combat.hpp"
#include<iostream>

Combat::Combat(Character player, Character enemy)
{
    this->player = player;
    this->enemy = enemy;
}

void execute_comba(Character player, Character enemy)
{   
    int p_health = player.get_attributes().get_livepoints();
    int e_health = enemy.get_attributes().get_livepoints();
    string move = "";
    bool anser_valid = false;

    while (p_health != 0 || e_health != 0)
    {
        cout << player.get_name() << " du bist am Zug." << endl;
        while(!anser_valid)
        {
            cout << "Du kannst versuchen anzugreifen [A] oder versuchen zu fliehen [F]." << endl;
            cin >> move;
        
            if (move == "M" || move == "m")
            {
                //attack action
                anser_valid = true;
            }else if (move == "F" || move == "f")
            {
                //escape action
                anser_valid = true;
            }else
            {
                cout << "Deine Eingabe war leider ungueltig. Bitte gebe 'A' oder 'F' ein." << endl;
            }
        }
        anser_valid = false;
    }
}

void main()
{
    Attributes att_player = Attributes(2,4,4);
    Attributes att_enemy = Attributes(3,3,3);
    Character player = Character(att_player, "player");
    Character enemy = Character(att_enemy, "enemy");

    Combat comb = Combat(player, enemy);
    comb.execute_combat(player, enemy);
}

Character Combat::get_player()
{
    return this->player;
}

Character Combat::get_enemy()
{
    return this->enemy;
}