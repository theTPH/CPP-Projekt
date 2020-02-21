
class Attributes
{
    private:
        int strength;
        int health;
        int dexterty;
        int livepoints;
    
    public:
        Attributes(int, int, int);
        Attributes(int, int, int, int);
        void initial_attribute_select();
        //get and set
        void set_strenght(int);
        int get_strength();
        void set_health(int);
        int get_health();
        void set_dexterty(int); 
        int get_dexterty();
        void set_livepoints(int);
        int get_livepoints();
};