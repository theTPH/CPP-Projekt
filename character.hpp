#include "attributes.hpp"
#include<iostream>
using namespace std;

class Character
{
    private:
        Attributes attributes = Attributes(0, 0, 0);
        string name;    
        int xp;
        int xp_lvl_up;
    public:
    //constructors
    Character();
    Character(Attributes, string);
    //methods
    void level_up_system();
    // get and set
    void set_attributes(Attributes);
    Attributes get_attributes();
    string get_name();
    void set_xp(int);
    int get_xp();
    void set_xp_lvl_up(int);
    int get_xp_lvl_up();

};