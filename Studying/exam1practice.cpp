#include <iostream> 
#include <vector>
using namespace std; 

class Employee{
private: 

    friend ostream& operator<<(ostream& os, const Employee& employee){
        os << "Name: " << employee.name << endl;
        os << "Boss: "; 
        if (!employee.boss){
            os << "I am the boss" << endl; 
        } else{ 
            os << employee.boss-> getname() << endl;
        }
        
        os << "Team: " << endl;
        for (const Employee& e: employee.team){
            os << e.getname() << endl;
        }

        return os;
    }
			
 
	string name; 
	Employee* boss = nullptr; 
	vector<Employee> team; 
public: 
	Employee(const string& name, Employee* boss) : name(name), boss(boss) {}
    Employee(const string& name) : name(name){}
	const string getname() const {return name;}
    bool hasboss() const {return boss;}
    const string getbossname() const {return boss->getname();}
    vector<Employee>& getteam() {return team;}
	
	void addToTeam(Employee& coworker){
		if (!coworker.hasboss()){
			coworker.hired(boss);
            team.emplace_back(coworker);
        } else if (coworker.getbossname() == boss->getname()){
            bool inteam = false;
            for (Employee& e : team){
                for (Employee& c : coworker.getteam()){
                    if (e.getname() == c.getname()){
                        inteam = true;
                    }
                }
                if (!inteam){
                    coworker.addToTeam(e);
                }
            }
		} else {
			cout << coworker.getname() << " has a boss already" << endl;
		} 
	}
	void hired(Employee* newboss){
		boss = newboss; 
	}

    void fired(){
        boss = nullptr; 
        team.clear();
    }

    void removeFromTeam(Employee& fired){
        fired.fired();
        bool firedbool = false;
        for (size_t i = 0; i < team.size() ; i++){ 
            if (firedbool){
                team[i-1] = team[i];
            } else if (team[i].getname() == fired.getname()){
                firedbool = true;
            }
        }
        team.pop_back();
    }
};

int main(){
    Employee sterling("Professor Sterling"); 
    Employee yan("Yan", &sterling);
    Employee jeremy("Jeremy");
    Employee mike("Mike");
    Employee will("Will");

    yan.addToTeam(jeremy); 
    yan.addToTeam(mike);
    yan.addToTeam(will);

    cout << yan << endl;
    cout << sterling << endl;
    yan.removeFromTeam(mike);
    cout << yan << endl;
}