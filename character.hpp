#include "attributes.hpp"

class Character
{
    private:
        Attributes attributes = Attributes(0, 0, 0);    
    public:
    Character(Attributes);
    // get and set
    void set_attributes(Attributes);
    int get_attributes();
};