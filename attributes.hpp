
class Attributes
{
    private:
        int strength = 0;
        int health = 0;
        int dexterty = 0;
    
    public:
        Attributes(int, int, int);
        void set_strenght(int);
        int get_strength();
        void set_health(int);
        int get_health();
        void set_dexterty(int); 
        int get_decterty();
}