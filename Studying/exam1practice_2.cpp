#include <iostream> 
#include <vector>
using namespace std; 


class Section{
    private: 
        friend ostream& operator<<(ostream& os, const Section& section){
            os << "Section: " << section.section << ", "
                << section.timeslot 
                << "Students: " << endl;

            if (section.roster.size() > 0){
                for (const StudentRecord* s : section.roster){
                    os << *s << endl;
                }

            } else{
                os << "None";
            }

            return os;
        }

        class StudentRecord{
            private: 
                friend ostream& operator<<(ostream& os, const Section::StudentRecord& record){
                    os << "Name: " << record.studentname
                    << ", Grades: "; 
                    for (int g : record.grades){
                        os << g << " ";
                    }
                    return os;
                }

                string studentname; 
                vector<int> grades;
            public:
                StudentRecord(const string& name): studentname(name), grades(14, -1) {}
                StudentRecord(const StudentRecord& rhs) : studentname(rhs.studentname), grades(rhs.grades){}
                const string& getname() const {return studentname;}

                bool updategrade(int grade, int index){
                    grades[index - 1] = grade;
                    return true;
                }
        };

        class Timeslot{
            private: 
                friend ostream& operator<<(ostream& os, const Section::Timeslot& timeslot){
                    os << "Time slot: [Day" << timeslot.day 
                    << ", Start time: "; 

                    if (timeslot.hour > 12){
                        os << timeslot.hour - 12 << "pm], ";
                    } else{
                        os << timeslot.hour << "am], ";
                    }

                    return os;
                }

                string day; 
                unsigned int hour; 

            public:
                Timeslot(const string& day, unsigned int hour): day(day), hour(hour) {}
                Timeslot(const Timeslot& rhs): day(rhs.day), hour(rhs.hour) {}

        };

        string section; 
        vector<StudentRecord*> roster; 
        Timeslot timeslot;

    public: 
        Section(const string& section, const string& day, unsigned int hour) : 
            section(section), timeslot(day,hour) {}
        
        Section(const Section& rhs): section(rhs.section), timeslot(rhs.timeslot){
            for (StudentRecord* s: rhs.roster){
                roster.emplace_back(new StudentRecord(*s));
            }
        }

        ~Section(){
            cout << section << " is being deleted" << endl;
            for (size_t i = 0; i < roster.size(); i++){
                cout << "Deleting " << roster[i]-> getname() << endl;
                delete roster[i];
                roster[i] = nullptr;
            }
            roster.clear();
        }

        bool addStudent(const string& newstudent){
            roster.emplace_back(new StudentRecord(newstudent));
            return true;
        }

        StudentRecord* isPartOfRoster(const string& student){
            for (StudentRecord* s : roster){
                if (s->getname() == student){
                    return s;
                }
            }
            return nullptr;
        }

        bool addGrade(const string& studentname, int grade, int index){
            StudentRecord* student = isPartOfRoster(studentname);
            if (student != nullptr){
                student-> updategrade(grade, index);
                return true; 
            } else{
                return false;
            }
        }

};

class LabWorker{
    private: 
        friend ostream& operator<<(ostream& os, const LabWorker& ta){
            os << ta.name; 
            if (ta.section == nullptr){
                os << " does not have a section. " << endl;
            } else{
                os << "has " << *ta.section << endl;
            }
            return os;
        }

        Section* section;
        string name; 

    public:
        LabWorker(const string& name) : name(name), section(nullptr){}

        bool addSection(Section& newsection){
            section = &newsection;
            return true;
        }

        bool addGrade(const string& studentname, int grade, int index){
            return section-> addGrade(studentname, grade, index);
        }
};

void doNothing(Section sec) { 
    cout << sec << endl;;
}

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
    LabWorker moe("Moe");
    cout << moe << endl;

    cout << "\nTest 4: Adding a section to a lab worker.\n";
    moe.addSection(secA2);
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
    jane.addSection(secB3);
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
    << "then make sure the following call works properly, i.e. no memory leaks\n";
    doNothing(secA2);
    cout << "Back from doNothing\n\n";

} // main