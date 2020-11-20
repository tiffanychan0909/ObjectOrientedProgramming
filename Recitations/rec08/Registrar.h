#ifndef REC_08_REGISTRAR_H
#define REC_08_REGISTRAR_H

#include <string>
#include <vector>
#include <iostream>


namespace BrooklynPoly{
    class Student; 
    class Course;
    class Registrar {
        friend std::ostream& operator<<(std::ostream& os, const Registrar& rhs);
    public:
        Registrar();
        bool addCourse(const std::string& courseName);
        bool addStudent(const std::string& studentName);
        bool enrollStudentInCourse(const std::string& studentName,
                                const std::string& courseName);
        bool cancelCourse(const std::string& courseName);
        void purge();

    private:
        size_t findStudent(const std::string& studentName) const;
        size_t findCourse(const std::string& courseName) const;

        std::vector<Course*> courses;
        std::vector<Student*> students;
    };
}

#endif