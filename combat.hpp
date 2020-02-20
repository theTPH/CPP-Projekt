#include "character.hpp"

class Combat
{
    private:
        Character player;
        Character enemy;
    public:
        Combat(Character, Character); // 1v1
        void execute_combat();
        void attack(Character, Character);
        Character get_player();
        Character get_enemy();
};