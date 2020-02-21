#include "combat.hpp"
#include<windows.h>
using namespace std;

int main()
{
    Attributes att_player = Attributes(0, 0, 0);
    att_player.initial_attribute_select();
    cout << att_player.get_strength() << att_player.get_health() << att_player.get_livepoints() << att_player.get_dexterty() << endl;

    Attributes att_enemy = Attributes(3,3,3);
    Character player = Character(att_player, "player");
    Character enemy = Character(att_enemy, "enemy");

    //Combat comb = Combat(player, enemy);
    //bool win = false;
    //win = comb.execute_combat();
    player.level_up_system(20);
    player.level_up_system(50);
    Sleep(10000);
}