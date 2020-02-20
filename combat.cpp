#include "combat.hpp"
#include<iostream>

Combat::Combat(Character player, Character enemy)
{
    this->player = player;
    this->enemy = enemy;
}

void Combat::execute_combat()
{   
    bool combat_over = false;
    string move = "";
    bool anser_valid = false;

    while (!combat_over)
    {   
        //players turn
        if (player.get_attributes().get_health() > 0)
        {
            cout << player.get_name() << " du bist am Zug." << endl;
            while(!anser_valid)
            {
                cout << "Du kannst versuchen anzugreifen [A] oder versuchen zu fliehen [F]." << endl;
                cin >> move;
            
                if (move == "A" || move == "a")
                {
                    anser_valid = true;
                    combat_over = attack(player, enemy);        
                }else if (move == "F" || move == "f")
                {
                    anser_valid = true;
                    combat_over = escape();
                }else
                {
                    cout << "Deine Eingabe war leider ungueltig. Bitte gebe 'A' oder 'F' ein." << endl;
                }
            }
            anser_valid = false;
        }else
        {
            combat_over = true;
        }
        
        //enemys turn
        if (enemy.get_attributes().get_health() > 0)
        {
            cout << enemy.get_name() << " ist am Zug." << endl;
            attack(enemy, player);
        }else
        {
            combat_over=true;
        }
        
        

    }
}

bool Combat::attack(Character attacker, Character defender)
{   
    bool combat_over = false;
    int damage = attacker.get_attributes().get_strength() + rand() %3 + 1; //last part creates random number between 1 and 3

    cout << "Der Angriff verursacht " << damage << " Schaden!" << endl;

    int rem_health = defender.get_attributes().get_livepoints() - damage;
    if (rem_health <= 0)
    {
        if (defender.get_name() == this->player.get_name())
        {
            cout << "Oh NEIN ...du wurdest besiegt...Tja du wirst wohl noch mal von Vorne anfangen müssen" << endl;
            this->player.get_attributes().set_livepoints(0); //will this work? o.O
            combat_over = true;
            //player dead --> what do we do here?
        }else
        {
            cout << "Du hast " << this->enemy.get_name() << " besiegt!" << endl;
            this->enemy.get_attributes().set_livepoints(0);
            combat_over = true;
            //enemy dead -> anything happens?
        }
        
    }else
    {
        if (defender.get_name() == this->player.get_name())
        {

        }else
        {
            cout << defender.get_attributes().get_livepoints() << endl;
            defender.get_attributes().set_livepoints(2);
            cout << defender.get_attributes().get_livepoints() << endl;
            cout << "Verbleibende Lebenspunkte " << rem_health << endl;
        }
    }
    return combat_over;
}

bool Combat::escape()
{   
    bool combat_over = false;
    int escape_value = this->player.get_attributes().get_dexterty()  + rand() %3 + 1;
    int grab_value = this->enemy.get_attributes().get_dexterty() + rand() %3 + 1;
    if ( escape_value > grab_value)
    {
        cout << "Du konntest entkommen!" << endl;
        combat_over = true;
        //What happens next?
    }else
    {
        cout << "Dein Gegner laesst nicht locker. Du wirst weiter kaempfen muessen!" << endl;
    }
    return combat_over;
}

Character Combat::get_player()
{
    return this->player;
}

Character Combat::get_enemy()
{
    return this->enemy;
}