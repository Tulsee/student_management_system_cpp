#ifndef STUDENT_H
#define STUDENT_H


#include <string>
#include "Database.h"

class Student {
    private:
        int id;
        std::string name;
        int age;
        std::string department;

    public:
        Student(int id, std::string name, int age, std::string department);
        void save();
        static void fetchAll();
        static bool updateStudent(int id, const std::string& name, int age, const std::string& department);
};

#endif