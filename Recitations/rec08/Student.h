#ifndef REC_08_STUDENT_H
#define REC_08_STUDENT_H

#include <string>
#include <vector>
#include <iostream>

namespace BrooklynPoly{
    class Course; 

    class Student {
        friend std::ostream& operator<<(std::ostream& os, const Student& rhs);
    public:
    // Student methods needed by Registrar
        explicit Student(const std::string& name);
        const std::string& getName() const;
        bool addCourse(Course* newCourse);

        // Student method needed by Course
        void removedFromCourse(Course* oldCourse);

    private:
        std::string name;
        std::vector<Course*> courses;
    };
    
}

#endif