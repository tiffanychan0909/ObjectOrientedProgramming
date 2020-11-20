#ifndef HW_07_PROTECTOR_H
#define HW_07_PROTECTOR_H

#include <iostream>
#include <vector>
#include <string>

namespace WarriorCraft{
    class Noble;

    class Protector{
    public:
        Protector(const std::string& name, double strength);
        const std::string& getname() const; 
        Lord* getlord() const;
        double getstrength() const; 
        bool isHired() const; 
        bool runaway();
        void newHired(Lord* newboss); 
        void fired(); 
        void updatestrength(double c);
        virtual void battlecry() const = 0;
    
    private:
        std::string name; 
        double strength; 
        Lord* boss;
    };

    class Wizard : public Protector{
    public: 
        Wizard(const std::string& name, double strength);
        void battlecry() const override;
    };
    class Warrior : public Protector{
    public: 
        Warrior(const std::string& name, double strength);
        void battlecry() const override;
    };
    class Archer : public Warrior{
    public: 
        Archer(const std::string& name, double strength);
        void battlecry() const override;
    };
    class Swordsman : public Warrior{
    public: 
        Swordsman(const std::string& name, double strength);
        void battlecry() const override;
    };

};

#endif