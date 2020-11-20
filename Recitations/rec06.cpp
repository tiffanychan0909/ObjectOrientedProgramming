/*
    Tiffany Chan 
    10/11/2020
    Lab 6
    School sections and Instructors

 */

#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Section Class with nested StudentRecord and Timeslot classes
class Section{
public: 
    Section(const string& sec, const string& day, unsigned int hour)
    : sec(sec), timeslot(day, hour) {};

    Section(const Section& rhs) // copy
    : sec(rhs.sec), timeslot(rhs.timeslot){
        for (size_t i = 0; i < rhs.student_records.size(); i++ ){
            student_records.emplace_back(new StudentRecord(*rhs.student_records[i]));
        }
    }

    ~Section(){ // delete
        cout << "SECTION " << sec << " IS BEING DELETED" << endl;
        for (StudentRecord*& s: student_records){
            cout << "Deleting " << s->getname() << endl;
            delete s;
        }
        student_records.clear();
    }

    string getsec() const{return sec;}

    bool addStudent(const string& studentname){
        student_records.emplace_back(new StudentRecord(studentname));
        return true;
    }
    
    bool changegrade(const string& studentname, int score, int index){
        for (size_t i = 0; i < student_records.size(); i++){
            if(student_records[i]->getname() == studentname){
                student_records[i]->updategrades(score,index);
                return true;
            }
        }
        return false;
    }
private: 
    friend ostream& operator<<(ostream& os, const Section& section){
        os << "Section: " << section.sec << ", Time slot: " << section.timeslot << ", Students:";

        if (section.student_records.size() == 0){
            os << " None";
        } else{
            for (StudentRecord* s : section.student_records){
                os << endl << *s ;
            }
        }

        return os;
    }
    class TimeSlot{
        private: 
            friend ostream& operator<<(ostream& os, const Section::TimeSlot& timeslot){
                unsigned int h = timeslot.hour;
                string period = "AM";
                if (timeslot.hour > 12){
                    h -= 12; 
                    period = "PM";
                }
                os << "[Day: " << timeslot.day << ", Start time: " << h << period << "]"; 
                return os; 
            }

            string day; 
            unsigned int hour;

        public: 
            TimeSlot(const string& day, unsigned int hour): day(day), hour(hour) {}; 
            const string getday() const{return day;}
            const unsigned int gethour() const{return hour;}

    };

    class StudentRecord{
        private: 
            friend ostream& operator<<(ostream& os, const StudentRecord& studentrecord){
                os << "Name: " << studentrecord.studentname << ", Grades: "; 
                for (const int& g : studentrecord.grades){
                    os << g << " ";
                }
                return os;
            }
            string studentname; 
            vector<int> grades;
        public: 
            StudentRecord(const string& studentname): studentname(studentname), grades(14, -1) {};
            string getname() const{return studentname;}
            void updategrades(int score, int index){
                grades[index - 1] = score;

            }

    };

    string sec; 
    TimeSlot timeslot;
    vector<StudentRecord*> student_records; 
};


class LabWorker{
    public: 
        LabWorker(const string& name): name(name), sec(nullptr){};

        void addSection(Section& newsec){sec = &newsec;}
        bool addGrade(const string& studentname, int score, int index){
            return sec->changegrade(studentname, score, index);
        } // don't fail silently
    private: 
        friend ostream& operator<<(ostream& os, const LabWorker& labworker){
            os << labworker.name;
            if (!labworker.sec){
                os << " does not have a section. ";
            } else{
                os << " has " << *labworker.sec;
            }
            return os;
        }
        string name;
        Section* sec; 
};

// Prototypes 
void doNothing(Section sec);

int main() {

    cout << "Test 1: Defining a section\n";
    Section secA2("A2", "Tuesday", 16);
    cout << secA2 << endl;

    cout << "\nTest 2: Adding students to a section\n";
    secA2.addStudent("John");
    secA2.addStudent("George");
    secA2.addStudent("Paul");
    secA2.addStudent("Ringo");
    cout << secA2 << endl;

    cout << "\nTest 3: Defining a lab worker.\n";
    LabWorker moe( "Moe" );
    cout << moe << endl;

    cout << "\nTest 4: Adding a section to a lab worker.\n";
    moe.addSection( secA2 );
    cout << moe << endl;

    cout << "\nTest 5: Adding a second section and lab worker.\n";
    LabWorker jane( "Jane" );
    Section secB3( "B3", "Thursday", 11 );
    secB3.addStudent("Thorin");
    secB3.addStudent("Dwalin");
    secB3.addStudent("Balin");
    secB3.addStudent("Kili");
    secB3.addStudent("Fili");
    secB3.addStudent("Dori");
    secB3.addStudent("Nori");
    secB3.addStudent("Ori");
    secB3.addStudent("Oin");
    secB3.addStudent("Gloin");
    secB3.addStudent("Bifur");
    secB3.addStudent("Bofur");
    secB3.addStudent("Bombur");
    jane.addSection( secB3 );
    cout << jane << endl;

    cout << "\nTest 6: Adding some grades for week one\n";
    moe.addGrade("John", 17, 1);  
    moe.addGrade("Paul", 19, 1);  
    moe.addGrade("George", 16, 1);  
    moe.addGrade("Ringo", 7, 1);  
    cout << moe << endl;

    cout << "\nTest 7: Adding some grades for week three (skipping week 2)\n";
    moe.addGrade("John", 15, 3);  
    moe.addGrade("Paul", 20, 3);  
    moe.addGrade("Ringo", 0, 3);  
    moe.addGrade("George", 16, 3);  
    cout << moe << endl;

    cout << "\nTest 8: We're done (almost)! \nWhat should happen to all "
         << "those students (or rather their records?)\n";

    cout << "\nTest 9: Oh, IF you have covered copy constructors in lecture, "
         << "then make sure the following call works:\n";
    doNothing(secA2);
    cout << "Back from doNothing\n\n";

} // main

void doNothing(Section sec) { cout << sec << endl; }