#include "Noble.h"
#include "Protector.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std; 
namespace WarriorCraft{
    Noble::Noble(const string& name, double strength): 
        name(name), strength(strength), alive(true){}
    double Noble::getstrength() const{return strength;}
    const string& Noble::getname() const{return name;}
    bool Noble::isAlive() const {return alive;}
    void Noble::updatestrength(double s){
        if (s == 0){
            alive = false; 
        }
        strength *= s;
    }
    void Noble::updatearmystrength(double c){
        strength += c;
    }
    void Noble::battle(Noble& opponent){
        cout << name << " battles " << opponent.getname() << endl;
        if ((!opponent.isAlive()) && (!isAlive())){
            cout << "Oh, NO! They're both dead! Yuck!" << endl;
        } else if(!opponent.isAlive() && isAlive()){
            battlecries();
            cout << "He's dead, " << name << endl;
        } else if(!isAlive() && opponent.isAlive()){
            opponent.battlecries();
            cout << "He's dead, " << opponent.getname() << endl;
        } else if(opponent.getstrength() > getstrength()){
            battlecries();
            opponent.battlecries();
            cout << opponent.getname() << " defeats " << getname() << endl;
            // r = 1 - oppon/self and is multiplied
            double r = 1 - ((getstrength())/(opponent.getstrength()));
            dies();
            opponent.wins(r);
        } else if(getstrength() > opponent.getstrength()){
            battlecries(); 
            opponent.battlecries();
            cout << getname() << " defeats " << opponent.getname() << endl;
            // r = 1 - oppon/self and is multiplied
            double r = 1 - ((opponent.getstrength())/(getstrength()));
            wins(r); 
            opponent.dies();
        } else{            
            battlecries(); 
            opponent.battlecries();
            cout << "Mutual Annihilation: " << getname() << " and " << opponent.getname() 
            << " die at each other's hands" <<  endl;
            dies(); 
            opponent.dies();
        }
    }

    // Lord 
    Lord::Lord(const string& name) : Noble(name, 0){}
    bool Lord::hires(Protector& newProtector){
        if(newProtector.isHired()){
            return false; 
        }

        this->army.__emplace_back(&newProtector);
        updatearmystrength(newProtector.getstrength());
        return true;
    }
    bool Lord::fires(Protector& oldProtector){
        if(!oldProtector.isHired()){
            return false; 
        }
        size_t i = find_protector_i(&oldProtector); 
        if (i < army.size()){
            return false; 
        } 
        Protector* temp; 
        while (i < army.size()){
            temp = army[i];
            army[i] = army[i+1];
            temp = army[i+1];
            i++;
        }
        cout << "You don't work for me anymore, " << oldProtector.getname() << endl;
        updatearmystrength(oldProtector.getstrength() * -1); 
        army.pop_back();
        return true; 
    }
    void Lord::ranaway(const Protector* runaway){
        size_t i = find_protector_i(runaway); 
        Protector* temp;
        while (i < army.size()){
            temp = army[i]; 
            army[i] = army[i+1]; 
            temp = army[i+1]; 
            i++;
        }
        updatearmystrength(runaway->getstrength() * -1); 
        army.pop_back(); 
    }
    void Lord::battlecries() const{
        for (Protector* p : army){
            cout << "In lord battlecry" << endl;
            p->battlecry();
        }
    }
    void Lord::wins(double c){ 
        for (Protector* p : army){
            p->updatestrength(c);
        }
        updatestrength(c);
    }
    void Lord::dies(){
        for (Protector* p : army){
            p->updatestrength(0);
        }
        updatestrength(0);
    }

    size_t Lord::find_protector_i(const Protector* protector) const{
        for (size_t i = 0; i < army.size(); i++){
            if (army[i] == protector){
                return i;
            }
        }
        return army.size();
    }

    // PersonWithStrengthToFight
    PersonWithStrengthToFight::PersonWithStrengthToFight(const std::string& name, double strength)
        : Noble(name, strength) {}
    void PersonWithStrengthToFight::battlecries() const{
        cout << "UGH!!!" << endl;
    }
    void PersonWithStrengthToFight::wins(double c){
        updatestrength(c);
    }
    void PersonWithStrengthToFight::dies(){
        updatestrength(0);
    }

}