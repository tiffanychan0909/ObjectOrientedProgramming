/*
  Recitation 06
  CS2124
 
  Focus: Dynamic arrays and copy control
 */

#include <string>
#include <iostream>
using namespace std;

class Position {
    friend ostream& operator<<(ostream& os, const Position& rhs) {
        os << '[' << rhs.title << ',' << rhs.salary << ']';
        return os;
    }
public:
    Position(const string& aTitle, double aSalary)
        : title(aTitle), salary(aSalary) {}
    const string& getTitle() const { return title; }
    double getSalary() const { return salary; }
    void changeSalaryTo(double d) { salary = d; }
private:
    string title;
    double salary;
}; // class Position

class Entry {
    friend ostream& operator<<(ostream& os, const Entry& rhs) {
        os << rhs.name << ' ' << rhs.room
           << ' ' << rhs.phone << ", " << *rhs.pos;
        return os;
    }
public:
    Entry(const string& name, unsigned room, unsigned phone, Position& position)
        : name(name), room(room), phone(phone), pos(&position) {
    }
    const string& getName() const { return name; }
    unsigned getPhone() const { return phone; }
private:
    string name;
    unsigned room;
    unsigned phone;
    Position* pos;
}; // class Entry

class Directory {
    // Overload output operator
    friend ostream& operator<<(ostream& os, const Directory& directory){
        for (size_t i = 0; i < size ; i++){
            os << 
        }
    }
public:
    // Of course the first function you need to write for this (or
    // any) class is...
    // ???
    // ...

    Directory(): size(0), capacity(5), entries(new Entry*[capacity]); {}

    Directory(const Directory* rhs){ // copy
        size = rhs.size; 
        capacity = rhs.size; 
        entries = new Entry*[2 * capacity]; 
        for (size_t i = 0; i < rhs.capacity; i++){
            entries[i] = new Entry(*rhs.entries[i]);
        }
    }

    ~Directory(){ 
        delete[] entries; 
    }
    
    // We'll get you started with the add method, but obviously you
    // have a lot of work to do here.
    void add(const string& name, unsigned room, unsigned ph, Position& pos) {
        if (size == capacity)	{
            // something is missing!!!  Add it!
            Entry** oldentries = entries; 
            entries = new Entry*[2 * capacity];
            
            for (size_t i = 0; i < size; i++){
                entries**[i] = oldentries;
            }
            delete[] oldentries;
            capacity *= 2;

        } // if
        entries[size] = new Entry(name, room, ph, pos);
        ++size;
    } // add

    int operator[](size_t index) const{
        return entries[index]-> getPhone();
    }

    int& operator[](size_t index) const{
        return entries[index];
    }

    Directory& operator=(const Directory rhs){
        if (this != rhs){
            delete[] entries; 

            data = new Entry*[rhs.capacity];

            size = rhs.size; 
            capacity = rhs.capacity; 
            for (size_t i = 0; i < rhs.size; i++){
                entries[i] = new Entry(*rhs.entries[i]);
            }
        }

        return *this;
    }

    int* begin(){
        return entries;
    }

    int* end(){
        return entries + capacity;
    }

    const int* begin() const{ 
        return entries;
    }

    const int* end() const{ 
        return entries + capacity;
    }


private:	
    Entry** entries; // pointer to pointer to an int, pointer array
    size_t size;
    size_t capacity;
}; // class Directory

void doNothing(Directory dir) { cout << dir << endl; }

int main() {
	
    // Note that the Postion objects are NOT on the heap.
    Position boss("Boss", 3141.59);
    Position pointyHair("Pointy Hair", 271.83);
    Position techie("Techie", 14142.13);
    Position peon("Peonissimo", 34.79);
	
    // Create a Directory
    Directory d;
    d.add("Marilyn", 123, 4567, boss);
    cout << d << endl;

    Directory d2 = d;	// What function is being used??
    d2.add("Gallagher", 111, 2222, techie);
    d2.add("Carmack", 314, 1592, techie);
    cout << d << endl;

    cout << "Calling doNothing\n";
    doNothing(d2);
    cout << "Back from doNothing\n";

    Directory d3;
    d3 = d2;

    // Should display 1592
    cout << d2["Carmack"] << endl;
	
} // main
