#include "combat.hpp"
#include<iostream>
#include<windows.h>

Combat::Combat(Character player, Character enemy)
{
    this->player = player;
    this->enemy = enemy;
}

bool Combat::execute_combat()
{   
    /*
    This is the main method to execute a combat situation. It defines the turn order and tells when the combat is over.
    returns combat_result: bool - the result of the combat situation false -> player dead; true -> player won
    */
    bool combat_over = false;
    bool combat_result = false; //false = player lost combat
    string move = "";
    bool anser_valid = false;

    while (!combat_over)
    {   
        //players turn
        if (this->player.get_attributes().get_health() > 0)
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
        if (this->enemy.get_attributes().get_livepoints() > 0)
        {
            cout << enemy.get_name() << " ist am Zug." << endl;
            combat_over = attack(enemy, player);
        }else
        {
            combat_over=true;
            combat_result = true;
        }
    }
    return combat_result;
}

bool Combat::attack(Character attacker, Character defender)
{   
    /*
    Attack method that can be used by the player and the enemy. Damage dealt will be handeld here.
    param attacker: Character - the player / npc that attacks
    param defender: Character - the player / npc that is attacked
    returns combat_over: bool - true-> player or npc is dead; false -> the combat continues
    */
    bool combat_over = false;
    int damage = attacker.get_attributes().get_strength() + rand() %3 + 1; //last part creates random number between 1 and 3

    cout << "Der Angriff verursacht " << damage << " Schaden!" << endl;

    int rem_health = defender.get_attributes().get_livepoints() - damage;
    if (rem_health <= 0)
    {
        if (defender.get_name() == this->player.get_name())
        {
            cout << "Oh NEIN ...du wurdest besiegt...Tja du wirst wohl noch mal von Vorne anfangen muessen" << endl;
            Attributes attr = Attributes(defender.get_attributes().get_strength(), defender.get_attributes().get_health(), defender.get_attributes().get_dexterty(), 0);
            this->player.set_attributes(attr);
            combat_over = true;
        }else
        {
            cout << "Du hast " << this->enemy.get_name() << " besiegt!" << endl;
            Attributes attr = Attributes(defender.get_attributes().get_strength(), defender.get_attributes().get_health(), defender.get_attributes().get_dexterty(), 0);
            this->enemy.set_attributes(attr);
            combat_over = true;
        }
        
    }else
    {
        if (defender.get_name() == this->player.get_name())
        {
            Attributes attr = Attributes(defender.get_attributes().get_strength(), defender.get_attributes().get_health(), defender.get_attributes().get_dexterty(), rem_health);
            this->player.set_attributes(attr);
            cout << "Verbleibende Lebenspunkte " << rem_health << endl;
        }else
        {
            Attributes attr = Attributes(defender.get_attributes().get_strength(), defender.get_attributes().get_health(), defender.get_attributes().get_dexterty(), rem_health);
            this->enemy.set_attributes(attr);
            cout << "Verbleibende Lebenspunkte " << rem_health << endl;
        }
    }
    return combat_over;
}

bool Combat::escape()
{   
    /*
    Method for the escape skill check. Players dexterty + w3 mus be greater then enemys dexterty +w3.
    Enemys cant use this action.
    returns combat_over: bool - true -> player escaped; false ->player stays in combat
    */
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