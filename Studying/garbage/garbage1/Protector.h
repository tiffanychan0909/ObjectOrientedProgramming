#ifndef PROTECTOR
#define PROTECTOR
#include <iostream>
#include <string>
namespace WarriorCraft {
	class Noble;
	class Protector {
	public:
		Protector(const std::string& name, int strength);
		const Lord* getmaster() const;
		const std::string& getname() const;
		const int getstrength() const;
		void setmaster(Lord* themaster);
		void setstrength(int stren);
		virtual void display() const = 0;
	protected:
	private:
		std::string name;
		int strength;
		Lord* master = nullptr;
	};
	class Warrior :public Protector {
	public:
		virtual void display() const = 0;
		Warrior(const std::string& name, int strength);
	private:
	};
	class Wizard :public Protector {
	public:
		Wizard(const std::string& name, int strength);
		void display() const;
	private:
	};
	class Archer :public Warrior {
	public:
		Archer(const std::string& name, int strength);
		void display() const;
	private:
	};
	class Swordsman :public Warrior {
	public:
		Swordsman(const std::string& name, int strength);
		void display() const;
	private:
	};
}
#endif