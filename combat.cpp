#include "combat.hpp"
#include<iostream>

Combat::Combat(Character player, Character enemy)
{
    this->player = player;
    this->enemy = enemy;
}

void Combat::execute_combat()
{   
    int p_health = this->player.get_attributes().get_livepoints();
    int e_health = this->enemy.get_attributes().get_livepoints();
    string move = "";
    bool anser_valid = false;

    while (p_health != 0 || e_health != 0)
    {
        int p_health = this->player.get_attributes().get_livepoints();
        int e_health = this->enemy.get_attributes().get_livepoints();

        cout << player.get_name() << " du bist am Zug." << endl;
        while(!anser_valid)
        {
            cout << "Du kannst versuchen anzugreifen [A] oder versuchen zu fliehen [F]." << endl;
            cin >> move;
        
            if (move == "A" || move == "a")
            {
                attack(player, enemy);
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

void Combat::attack(Character attacker, Character defender)
{
    int damage = attacker.get_attributes().get_strength() + rand() %3 + 1; //last part creates random number between 1 and 3
    cout << "Der Angriff verursacht " << damage << " Schaden!" << endl;
    int rem_health = defender.get_attributes().get_livepoints() - damage;
    if (rem_health <= 0)
    {
        if (defender.get_name() == this->player.get_name())
        {
            cout << "Oh NEIN ...du wurdest besiegt...Tja du wirst wohl noch mal von Vorne anfangen müssen" << endl;
            this->player.get_attributes().set_livepoints(0); //will this work? o.O
            //player dead --> what do we do here?
        }else
        {
            cout << "Du hast " << this->enemy.get_name() << " besiegt!" << endl;
            this->enemy.get_attributes().set_livepoints(0);
            //enemy dead -> anything happens?
        }
        
    }else
    {
        if (defender.get_name() == this->player.get_name())
        {

        }else
        {
            cout << defender.get_attributes().get_livepoints();
            this->enemy.get_attributes().set_livepoints(rem_health);
            cout << defender.get_attributes().get_livepoints() << endl;
            cout << "Verbleibende Lebenspunkte " << rem_health << endl;
        }
    }
}

Character Combat::get_player()
{
    return this->player;
}

Character Combat::get_enemy()
{
    return this->enemy;
}