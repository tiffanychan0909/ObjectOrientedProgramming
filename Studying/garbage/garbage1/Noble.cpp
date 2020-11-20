#include <iostream>
#include <string>
#include <vector>
#include "Noble.h"
#include "Protector.h"
using namespace std;
namespace WarriorCraft {
	Noble::Noble(const std::string& name) :name(name) {}
	const string& Noble::getname() const { return name; }
	const bool Noble::getstatus() const { return status; }
	const float Noble::getstrength() const { return totalstrength; }
	void Noble::setstrength(float strength) { totalstrength = strength; }
	void Noble::setstatus(bool status) { this->status = status; }
	void Noble::defend(float ratio){ totalstrength *= ratio; }
	void Noble::battle(Noble& nob) {
		cout << name << " battles " << nob.name << endl;
		if (status == false && nob.status == false) {
			cout << "Oh, NO!  They're both dead!  Yuck!" << endl;
		}
		else if (totalstrength == nob.totalstrength) {
			cout << "Mutual Annihalation: " << name << " and " << nob.name << " die at each other's hands" << endl;
			defend(0);
			nob.defend(0);
		}
		else if (status == false) {
			cout << "He's dead, " << nob.name << endl;
		}
		else if (nob.status == false) {
			cout << "He's dead, " << name << endl;
		}
		else if (totalstrength > nob.totalstrength) {
			nob.defend(0);
			defend(1 - nob.totalstrength / totalstrength);
			nob.status = false;
			cout << name << " defeats " << nob.name << endl;
		}
		else {
			defend(0);
			nob.defend(1 - totalstrength / nob.totalstrength);
			status = false;
			cout << nob.name << " defeats " << name << endl;
		}
	}

	Lord::Lord(const std::string& name) : Noble(name) {}
	void Lord::setProtectors(float ratio) {
		for (Protector* pro : Protectors) {
			pro->setstrength(int(ratio * pro->getstrength()));
		}
	}
	bool Lord::hires(Protector& pro) {
		if (getstatus() == false) {
			return false;
		}
		else if (pro.getmaster() != nullptr) {
			return false;
		}
		else {
			Protectors.push_back(&pro);
			pro.setmaster(this);
			setstrength (pro.getstrength()+getstrength());
			return true;
		}
	}
	bool Lord::fire(Protector& pro) {
		if (getstatus() == false) {
			return false;
		}
		else if (pro.getmaster() != this) {
			return false;
		}
		else {
			for (size_t i = 0; i < Protectors.size(); ++i) {
				if (Protectors[i] == &pro) {
					while (i < Protectors.size() - 1) {
						Protectors[i] = Protectors[i + 1];//make fired Protectors to the end of vector
					}
					Protectors.pop_back();
					break;
				}
			}
			pro.setmaster(nullptr);//set the Protector avilable for hires
			setstrength(pro.getstrength() - getstrength());
			return true;
		}
	}
	

	void Lord::defend(float ratio) {
		for (size_t i = 0; i < Protectors.size();++i) {
			Protectors[i]->display();
			Protectors[i]->setstrength(ratio * Protectors[i]->getstrength());
		}
		Noble::defend(ratio);
	}

	PersonWithStrengthToFight::PersonWithStrengthToFight(const std::string& name, float strength) :Noble(name) { setstrength(strength); }
	void PersonWithStrengthToFight::defend(float ratio) {
		cout << "UGH!!!" << endl;
		Noble::defend(ratio);
	}
}