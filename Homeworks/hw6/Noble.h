#ifndef HW_06_NOBLE_H
#define HW_06_NOBLE_H

#include <iostream>
#include <vector>
#include <string>

namespace WarriorCraft{
    class Warrior; 

    class Noble{
        friend std::ostream& operator<<(std::ostream& os, const Noble& noble);
    public: 
        explicit Noble(const std::string& name); 
        double getstrength() const; 
        const std::string& getname() const; 
        bool is_alive() const; 

        size_t find_warrior_i(const Warrior* warrior) const; 
        bool hire(Warrior& warrior);
        bool fire(Warrior& warrior); 
        void ranaway(Warrior& runaway);
        void battle(Noble& opponent); 
        void wins(double c); 
        void dies(); 
        void updatearmystrength(double c); 

    private: 
        std::string name; 
        std::vector<Warrior*> army; 
        double army_strength; 
        bool alive = true; 

    };

}

#endif