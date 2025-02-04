#include <iostream>
#include "Student.h"

int main() {
    int choice;

    while (true) {
        std::cout << "\n📚 Student Database Management System\n";
        std::cout << "1. Add Student\n";
        std::cout << "2. Fetch All Students\n";
        std::cout << "3. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (choice == 1) {
            int id, age;
            std::string name, department;

            std::cout << "Enter student ID: ";
            std::cin >> id;
            std::cin.ignore();

            std::cout << "Enter student name: ";
            std::getline(std::cin, name);

            std::cout << "Enter student age: ";
            std::cin >> age;
            std::cin.ignore();

            std::cout << "Enter student department: ";
            std::getline(std::cin, department);

            Student student(id, name, age, department);
            student.save();
        } 
        else if (choice == 2) {
            Student::fetchAll();
        } 
        else if (choice == 3) {
            std::cout << "👋 Exiting the program...\n";
            break;
        } 
        else {
            std::cout << "❌ Invalid choice! Please enter 1, 2, or 3.\n";
        }
    }

    return 0;
}
