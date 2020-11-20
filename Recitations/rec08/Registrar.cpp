#include "Course.h"
#include "Student.h"
#include "Registrar.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std; 

namespace BrooklynPoly{
    Registrar::Registrar(){};

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
}