#include "Course.h"
#include "Student.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std; 

namespace BrooklynPoly{
    Student::Student(const string& studentName) : name(studentName) {}; 
    
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

    const string& Student::getName() const{return name;}
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
}