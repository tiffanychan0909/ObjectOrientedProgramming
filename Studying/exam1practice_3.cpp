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
                os << employee.boss->name << endl;
            }

            os << "Team ... " << endl; 
            for (const Employee* e : employee.team){
                os << "     " << e->name << endl;
            }

            return os;
        }

        string name; 
        Employee* boss; 
        vector<Employee*> team;  //not using dynamic array because you don't know the end
        
    public: 
        Employee(const string& name, Employee* boss) : name(name), boss(boss){}
        Employee(const string& name) : name(name) {boss = nullptr;}
        bool isemployed(){
            if (!boss){
                return false;
            } else {
                return true;
            }
        }

        bool addToTeam(Employee& newhire){
            bool newmember = false;

            if(!(newhire.isemployed()) && (!(&newhire == this)) && (!(&newhire == this->boss))){
                team.emplace_back(&newhire);
                newmember = newhire.gothired(this);
            }

            if (newmember){
                newhire.updateteam(team);
            }

            return newmember;
        }

        bool removeFromTeam(Employee* firedhire){
            for (size_t i = 0; i < team.size(); i++){
                if (team[i] == firedhire){
                    team[i] = team[team.size() - 1];
                    team.pop_back();
                    return true;
                }
            }
            return false;
        }

        bool gothired(Employee* newboss){
            boss = newboss;
            return true;
        }

        bool updateteam(vector<Employee*>& newteam){
            for (Employee* coworker : newteam){
                team.emplace_back(coworker);
            }

            return true;
        }


};

int main(){
    Employee sterling("Professor Sterling");
    Employee yan("Yan", &sterling);
    Employee jeremy("Jeremy");
    Employee mike("Mike");
    yan.addToTeam(jeremy);
    yan.addToTeam(mike);
    cout << yan << endl; 
    cout << sterling << endl; 

}