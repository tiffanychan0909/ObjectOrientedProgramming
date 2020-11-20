#include <iostream>
#include <string>
#include <vector>
#include "Noble.h"
#include "Protector.h"
using namespace std;
namespace WarriorCraft {
	Protector::Protector(const std::string& name, int strength) :name(name), strength(strength) {}
	const int Protector::getstrength() const { return strength; }
	const std::string& Protector::getname() const { return name; }
	void Protector::setmaster(Lord* themaster) { master = themaster; }
	void Protector::setstrength(int stren) { strength = stren; }
	const Lord* Protector::getmaster() const { return master; }
	void Warrior::display() const {
			cout << getname() << " says: Take that in the name of my lord, " << getmaster()->getname() << endl;
	}
	Warrior::Warrior(const std::string& name, int strength) :Protector(name, strength) {}


	Wizard::Wizard(const std::string& name, int strength) :Protector(name, strength) {}
	void Wizard::display() const {
		if (getmaster() == nullptr) {
			cout << "No master" << endl;
		}
		else {
			cout << "POOF!" << endl;
		}
	}


	Archer::Archer(const std::string& name, int strength) :Warrior(name, strength) {}
	void Archer::display() const {
		if (getmaster() == nullptr) {
			cout << "No master" << endl;
		}
		else {
			cout << "TWANG!  ";
			Warrior::display();
		}
	}


	Swordsman::Swordsman(const std::string& name, int strength) :Warrior(name, strength) {}
	void Swordsman::display() const {
		if (getmaster() == nullptr) {
			cout << "No master" << endl;
		}
		else {
			cout << "Clang!  ";
			Warrior::display();
		}
	}
}