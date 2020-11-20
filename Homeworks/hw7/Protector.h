#ifndef HW_07_PROTECTOR_H
#define HW_07_PROTECTOR_H

#include <iostream>
#include <vector>
#include <string>

namespace WarriorCraft{
    class Noble;
    class Lord;
    class Protector{
    public:
        Protector(const std::string& name, double strength);
        virtual void battlecry() const = 0;
        const std::string& getname() const; 
        const std::string& getbossname() const;
        // Lord* getboss() const;
        double getstrength() const;
        bool isHired() const;
        bool isAlive() const;
        bool quit();
        void gotHired(Lord* newboss);
        void fired();
        void updatestrength(double c);


    private:
        std::string name; 
        bool hired;
        bool alive;
        double strength;
        Lord* boss;

    };

    class Wizard : public Protector{
    public:
        Wizard(const std::string& name, double strength);
        void battlecry() const override;
    private:

    };

    class Warrior : public Protector{
    public:
        Warrior(const std::string& name, double strength);
        virtual void battlecry() const = 0;
    private:

    };

    class Archer : public Warrior{
    public:
        Archer(const std::string& name, double strength);
        void battlecry() const override;
    private:

    };

    class Swordsman : public Warrior{
    public:
        Swordsman(const std::string& name, double strength);
        void battlecry() const override;
    private:

    };
};
#endif