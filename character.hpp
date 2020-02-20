#include "attributes.hpp"
#include<iostream>
using namespace std;

class Character
{
    private:
        Attributes attributes = Attributes(0, 0, 0);
        string name = "";    
    public:
    Character();
    Character(Attributes, string);
    // get and set
    void set_attributes(Attributes);
    int get_attributes();
};