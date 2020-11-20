// Tiffany Chan 
// Lab 8 
// Separate Compilation, Association

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Student; 
class Registrar; 

class Course {
    friend ostream& operator<<(ostream& os, const Course& rhs);
public:
    // Course methods needed by Registrar
    Course(const string& courseName);
    const string& getName() const;
    bool addStudent(Student* newStudent);
    void removeStudentsFromCourse(); 

private:
    string name;
    vector<Student*> students;
};

class Student {
    friend ostream& operator<<(ostream& os, const Student& rhs);
public:
    // Student methods needed by Registrar
    Student(const string& name);
    const string& getName() const;
    bool addCourse(Course* newCourse);

    // Student method needed by Course
    void removedFromCourse(Course* oldCourse);

private:
    string name;
    vector<Course*> courses;
};

class Registrar {
    friend ostream& operator<<(ostream& os, const Registrar& rhs);
public:
    Registrar();
    bool addCourse(const string& courseName);
    bool addStudent(const string& studentName);
    bool enrollStudentInCourse(const string& studentName,
                               const string& courseName);
    bool cancelCourse(const string& courseName);
    void purge();

private:
    size_t findStudent(const string& studentName) const;
    size_t findCourse(const string& courseName) const;

    vector<Course*> courses;
    vector<Student*> students;
};

int main() {

    Registrar registrar;

    cout << "No courses or students added yet\n";
    cout << registrar << endl;
     
    cout << "AddCourse CS101.001\n";
    registrar.addCourse("CS101.001");
    cout << registrar << endl;

    cout << "AddStudent FritzTheCat\n";
    registrar.addStudent("FritzTheCat");
    cout << registrar << endl;

    cout << "AddCourse CS102.001\n";
    registrar.addCourse("CS102.001");
    cout << registrar << endl;

    cout << "EnrollStudentInCourse FritzTheCat CS102.001\n";
    registrar.enrollStudentInCourse("FritzTheCat", "CS102.001");
    cout << "EnrollStudentInCourse FritzTheCat CS101.001\n";
    registrar.enrollStudentInCourse("FritzTheCat", "CS101.001");
    cout << registrar << endl;

    cout << "EnrollStudentInCourse Bullwinkle CS101.001\n";
    cout << "Should fail, i.e. do nothing, "
         << "since Bullwinkle is not a student.\n";
    registrar.enrollStudentInCourse("Bullwinkle", "CS101.001");
    cout << registrar << endl;

    cout << "CancelCourse CS102.001\n";
    registrar.cancelCourse("CS102.001");
    cout << registrar << endl;
   
    /*
    // [OPTIONAL - do later if time]
    cout << "ChangeStudentName FritzTheCat MightyMouse\n";
    registrar.changeStudentName("FritzTheCat", "MightyMouse");
    cout << registrar << endl;  

    cout << "DropStudentFromCourse MightyMouse CS101.001\n";
    registrar.dropStudentFromCourse("MightyMouse", "CS101.001");
    cout << registrar << endl;  

    cout << "RemoveStudent FritzTheCat\n";
    registrar.removeStudent("FritzTheCat");
    cout << registrar << endl;  
    */

    cout << "Purge for start of next semester\n";
    registrar.purge();
    cout << registrar << endl;
}
  
// ostreams for each class
ostream& operator<<(ostream& os, const Registrar& rhs){
    os << "Registrar's Report" << endl;
    
    os << "Courses: " << endl; 
    if (!(rhs.courses.size() == 0)){
        for (const Course* c : rhs.courses){
            os << *c << endl; 
        }
    }
    os << "Students: " << endl; 

    if (!(rhs.students.size() == 0)){
        for (const Student* s : rhs.students){
            os << *s << endl;
        }
    }


    return os; 

}

ostream& operator<<(ostream& os, const Student& rhs){
    os << rhs.name << " : "; 
    if (rhs.courses.size() == 0){
        os << "No Courses"; 
    } else{
        for (const Course* c :rhs. courses){
            os << c->getName() << " ";
        }
    }
    return os;
}

ostream& operator<<(ostream& os, const Course& rhs){
    os << rhs.name << " : "; 
    if (rhs.students.size() == 0){
        os << "No Students";
    } else{
        for (const Student* s : rhs.students){
            os << s->getName() << " "; 
        }
    }
    return os;
}

// Registrar 
Registrar::Registrar(){};

bool Registrar::addCourse(const string& courseName){
    for (const Course* c : courses){
        if (c->getName() == courseName){
            return false;
        }
    }

    courses.push_back(new Course(courseName));
    return true;
}

bool Registrar::addStudent(const string& studentName){
    for (const Student* s : students){
        if(s->getName() == studentName){
            return false;
        }
    }

    students.push_back(new Student(studentName));
    return true;
}

bool Registrar::enrollStudentInCourse(const string& studentName, const string& courseName){
    size_t s = findStudent(studentName); 
    size_t c = findCourse(courseName); 

    if(s == students.size() || c == courses.size()){
        return false;
    }

    students[s]->addCourse(courses[c]); 
    courses[c]->addStudent(students[s]);
    return true;
}

bool Registrar::cancelCourse(const string& courseName){
    size_t c = findCourse(courseName); 
    if (c == courses.size()){return false;}
    courses[c]->removeStudentsFromCourse();

    delete courses[c];
    courses[c] = courses[courses.size()-1];

    courses.pop_back();
    return true;
}

void Registrar::purge(){
    for (size_t i = 0; i < courses.size(); i++){
        delete courses[i]; 
        courses[i] = nullptr;
    }
    courses.clear(); 

    for(size_t i = 0; i < students.size(); i++){
        delete students[i]; 
        students[i] = nullptr; 
    }
    students.clear();
}

size_t Registrar::findStudent(const string& studentName) const{
    for (size_t i = 0; i < students.size(); i++){
        if (students[i]->getName() == studentName){
            return i; 
        }
    }

    return students.size();
}

size_t Registrar::findCourse(const string& courseName) const{
    for (size_t i = 0; i < courses.size(); i++){
        if (courses[i]-> getName() == courseName){
            return i;
        }
    }
    
    return courses.size();
}

// Student 
Student::Student(const string& studentName) : name(studentName) {}; 
const string& Student::getName()const{return name;}
bool Student::addCourse(Course* newCourse){
    for (const Course* c : courses){
        if (c == newCourse){
            return false; 
        }
    }

    courses.push_back(newCourse);
    return true;
}
void Student::removedFromCourse(Course* oldCourse){
    for (size_t i = 0; i < courses.size(); i++){
        if (courses[i] == oldCourse){
            courses[i] = courses[courses.size() - 1]; 
            courses.pop_back();

            return;
        }
    }
}

// Course 
Course::Course(const string& courseName): name(courseName) {}; 
const string& Course::getName() const{return name;}
bool Course::addStudent(Student* newStudent){

    for (const Student* s : students){
        if (s == newStudent){
            return false; 
        }
    }

    students.push_back(newStudent);
    return true;
}

void Course::removeStudentsFromCourse(){
    for (Student* s : students){
        s->removedFromCourse(this);
        
    }

    students.clear();

}