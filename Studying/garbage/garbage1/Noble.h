#ifndef NOBLE
#define NOBLE
#include <iostream>
#include <string>
#include <vector>
namespace WarriorCraft {
	class Protector;
	class Noble {
	public:
		Noble(const std::string& name);
		virtual void battle(Noble& nob);
		virtual void defend(float ratio) = 0;
		const std::string& getname() const;
		const bool getstatus() const;
		const float getstrength() const;
		void setstrength(float strength);
		void setstatus(bool status);

	protected:
	private:
		bool status = true;//track dead or alive
		float totalstrength = 0;//total strength of the Protectors
		std::string name;
	};
	class Lord : public Noble {
	public:
		Lord(const std::string& name);
		bool hires(Protector& pro);
		bool fire(Protector& pro);
		void setProtectors(float ratio);
		void defend(float ratio);
		//battle between two Lord object
	private:
		std::vector<Protector*> Protectors;
	};
	class PersonWithStrengthToFight :public Noble {
	public:
		PersonWithStrengthToFight(const std::string& name, float totalstrength);
		void defend(float ratio);
	private:
	};
}


#endif