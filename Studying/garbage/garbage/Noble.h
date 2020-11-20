#ifndef HW_07_NOBLE_H
#define HW_07_NOBLE_H

#include <iostream>
#include <vector>
#include <string>

namespace WarriorCraft{
    class Protector;
    class Noble{
    public:
        Noble(const std::string& name, double strength);
        double getstrength() const; 
        const std::string& getname() const; 
        bool isAlive() const; 
        void battle(Noble& opponent);
        void updatestrength(double s);
        void updatearmystrength(double c);

        virtual void battlecries() const = 0;
        virtual void wins(double c) = 0; 
        virtual void dies() = 0; 
    private: 
        std::string name; 
        double strength;
        bool alive;
    };

    class Lord : public Noble{
    public:
        Lord(const std::string& name); 
        bool hires(Protector& newProtector); 
        bool fires(Protector& oldProtector); 
        void ranaway(const Protector* runaway);

        void battlecries() const override;
        void wins(double c) override; 
        void dies() override;
        
    private:
        size_t find_protector_i(const Protector* protector) const;

        std::vector<Protector*> army; 
    };
    class PersonWithStrengthToFight : public Noble{
    public: 
        PersonWithStrengthToFight(const std::string& name, double strength); 
        
        void battlecries() const override;
        void wins(double c) override; 
        void dies() override;
    };
};
#endif