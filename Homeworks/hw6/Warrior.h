#ifndef HW_06_WARRIOR_H
#define HW_06_WARRIOR_H

#include <iostream>
#include <vector>
#include <string>

namespace WarriorCraft{
    class Noble;

    class Warrior{
        friend std::ostream& operator<<(std::ostream& os, const Warrior& warrior);

    public: 
        Warrior(const std::string& name, double strength);
        const std::string& getname() const;
        double getstrength() const;
        bool isHired() const; 
        bool runaway();
        void newhired(Noble* newboss); 
        void fired(); 
        void updatestrength(double c);

    private: 
        std::string name; 
        double strength; 
        bool hired = false; 
        Noble* boss = nullptr; 

    };

}

#endif