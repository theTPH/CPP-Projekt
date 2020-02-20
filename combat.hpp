#include "character.hpp"
#include "attributes.hpp"

class Combat
{
    private:
        Character player;
        Character enemy;
    public:
        Combat(Character, Character); // 1v1
        void execute_combat();
};