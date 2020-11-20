
#include <iostream>
#include <vector>

using namespace std;

// struct date{
//     int day; 
//     int month; 
//     int year;
// }; 

// int main(){
//     date* tomorrow = new date();
//     (*tomorrow).day = 10;
//     tomorrow->month = 20;
//     tomorrow->year = 2020;

//     cout << (tomorrow->day) << endl;
// }
// class Base{
//     friend ostream& operator<<(ostream& os, const Base& base){
//         os<<base.b<<endl;
//         return os;
//     }
// public: 
//     Base() : b(0){}
//     Base(const Base& rhs){
//         b = rhs.b;
//     }
//     void change(int x){
//         b = x;
//     }
// private: 
//     int b;
// };

// int main(){
//     vector<Base*> bases; 

//     Base b1; 
//     Base b2;
//     Base b3; 

//     bases.emplace_back(new Base(b1));
//     bases.emplace_back(&b2);
//     bases.emplace_back(new Base());

//     b3.change(8);
//     Base b4 = b3;
//     cout << b3 << " " << b4 << endl;

//     b3.change(10);
//     cout << b3 << " " << b4 << endl;

// }

// class Food{
//     public: 
//     virtual void output_type() = 0;
// };
// class Vegetable : public Food{
//     public: 
//     void output_type() override{cout << "Veggie";}
// };
// class Potato : public Vegetable{};

// int main(){
//     Potato gc; 
//     Food* pp = &gc; 
//     pp->output_type();
//     gc.output_type();
// }

// class Location{
//     public:
//     Location(string loc, int count) : name(loc), size(count){}
//     void display() {cout << name << " : " << size << endl;}

//     private: 
//     string name; 
//     int size; 
// };
// int main(){
//     Location thingone("Tandon", 5212); 
//     string s = "CSE"; 
//     thingone = s; 
//     thingone.display();
// }

// class Salad{
//     public: 
//     Salad(){ cout << "1 ";}
//     ~Salad(){ cout << "2 ";}
// }; 
// class FoodItem{
//     public: 
//     FoodItem(){ cout<< "3 ";}
//     ~FoodItem(){ cout<< "4 ";}
    
//     private: 
//     Salad green_stuff;

// };
// class DinnerEntree : public FoodItem{
//     public:
//     DinnerEntree() { cout << "5 ";}
//     ~DinnerEntree() { cout << "6 ";}

// };

// int main(){
//     DinnerEntree my_dinner;
// }

// class RebelShip{
//     public: 
//     RebelShip(){}
//     void attack(string weapon){
//         cout << "Rebel ship firing" << weapon;
//     }
// };
// class XWingFighter : public RebelShip{
//     public: 
//     virtual void transport() { cout << "jump to hyperspace";}
//     void attack() {cout << "XWingFighter firing laser cannons";}
// };

// int main(){
//     XWingFighter* red_leader = new XWingFighter();
//     red_leader->attack("proton torpedoes");
// }

// class Player{
//     protected: 
//     void score_touchdown(){}
// };
// class FootballPlayer : public Player{
//     public: 
//     void win_game(){ score_touchdown(); }
// };
// int main(){
//     FootballPlayer fp; 
//     fp.score_touchdown();
//     // fp.win_game();
// }

// class Product{
//     public:
//     Product(){}
//     virtual void fly() { cout << "In product fly ";}

// };
// class Drone : public Product{
//     public: 
//     virtual void crash() { cout << "In drone crashing";}
//     void fly() {cout << "In drone fly";}
// };

// int main(){
//     Drone drone; 
//     Product item; 
//     item = drone; 
//     // item.fly();
//     item.crash();
//     // drone = item;
// }

class Book{
    public:
    virtual void read() { cout << "Book read\n";}

};
class Novel : public Book{
    public :
    void read() { cout << "Novel read\n";}
};

int main(){
    Book* book = new Novel(); 
    Novel* harrypotter = book;
    harrypotter->read();
}

// void Object(const int& x){
//     const int* p = &x; 
//     int y = x; 
//     cout << *p << endl; 
//     y = 32;
// }

// int main(){
//     int y = 23; 
//     Object(y); 
//     cout << y << endl;
// }

// class Child; 
// class Parent{
//     public: 
//     virtual void invokeme(Parent& arg){
//         cout << "Parent::invokeme(parent)\n";
//     }
//     virtual void invokeme(Child& arg){
//         cout << "Parent::invokeme(child)\n";
//     }
// };
// class Child : public Parent{
//     public:
//     virtual void invokeme(Parent& arg){
//         cout << "Child::invokeme(parent)\n";
//     }
//      virtual void invokeme(Child& arg){
//         cout << "Child::invokeme(child)\n";
//     }
// };
// void somefunc(Parent& a, Parent& b ){
//     a.invokeme(b);
// }
// int main(){
//     Child thechild; 
//     Parent theparent; 
//     somefunc(theparent, thechild);
// }