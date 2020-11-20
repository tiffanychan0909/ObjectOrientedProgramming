#ifndef HW_07_NOBLE_H
#define HW_07_NOBLE_H

#include <iostream>
#include <vector>
#include <string>

namespace WarriorCraft{
    class Protector;
    class Noble{
    public:
        Noble(const std::string& name, double strength = 0); 
        double getstrength() const; 
        const std::string& getname() const; 
        bool is_alive() const;
        void battle(Noble& opponent); 
        virtual void defend() const = 0;
        virtual void wins(double c); 
        virtual void dies(); 
        virtual void updatestrength(double c); 
        void increaseStrength(double s);
        
        
    private:
        std::string name; 
        bool alive;
        double strength;
    };

    class Lord : public Noble{
    public:
        Lord(const std::string& name);
        void defend() const override;
        void updatestrength(double c); 
        void wins(double c) override; 
        void dies() override;

        bool hires(Protector& protector);
        bool fires(Protector& protector); 
        bool ranaway(const Protector& runaway);
    
    private:
        size_t find_warrior_i(const Protector* protector) const; 
        std::vector<Protector*> army;
    };

    class PersonWithStrengthToFight : public Noble{
    public:
        PersonWithStrengthToFight(const std::string& name, double strength);
        void defend() const override;
    private:

    };
};
#endif