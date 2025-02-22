#include <iostream>
#include <thread>
#include <chrono>
#include "Student.h"

#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif

#define RESET   "\033[0m"
#define BOLD    "\033[1m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define CYAN    "\033[36m"
#define RED     "\033[31m"

void loadingEffect(const std::string& message) {
    std::cout << YELLOW << message;
    for (int i = 0; i < 3; i++) {
        std::cout << "." << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    std::cout << RESET << std::endl;
}

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void displayMenu() {
    clearScreen();
    std::cout << BOLD << CYAN;
    std::cout << "=====================================\n";
    std::cout << " 📚 Student Database Management System\n";
    std::cout << "=====================================\n";
    std::cout << RESET;
    std::cout << GREEN << "1. Add Student\n";
    std::cout << "2. Fetch All Students\n";
    std::cout << "3. Update Student\n";
    std::cout << "4. Delete Student\n";
    std::cout << "5. Exit\n" << RESET;
    std::cout << BOLD << "Enter your choice: " << RESET;
}

int getValidIntInput(const std::string& prompt) {
    int value;
    while (true) {
        std::cout << BOLD << CYAN << prompt << RESET;
        std::cin >> value;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << RED << "❌ Invalid input! Please enter a valid number.\n" << RESET;
        } else {
            std::cin.ignore();
            return value;
        }
    }
}

int main() {
    int choice;

    while (true) {
        displayMenu();
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << RED << "❌ Invalid input! Please enter a number.\n" << RESET;
            std::this_thread::sleep_for(std::chrono::seconds(2));
            continue;
        }

        if (choice == 1) {
            int id, age;
            std::string name, department;

            std::cout << BOLD << CYAN << "Enter student ID: " << RESET;
            std::cin >> id;
            std::cin.ignore();

            std::cout << BOLD << CYAN << "Enter student name: " << RESET;
            std::getline(std::cin, name);

            std::cout << BOLD << CYAN << "Enter student age: " << RESET;
            std::cin >> age;
            std::cin.ignore();

            std::cout << BOLD << CYAN << "Enter student department: " << RESET;
            std::getline(std::cin, department);

            Student student(id, name, age, department);
            loadingEffect("Saving student");
            student.save();
            std::cout << GREEN << "✅ Student saved successfully!\n" << RESET;
            std::this_thread::sleep_for(std::chrono::seconds(2));
        } 
        else if (choice == 2) {
            loadingEffect("Fetching students");
            Student::fetchAll();
            std::cout << GREEN << "✅ Student records displayed above.\n" << RESET;
            std::cout << "Press ENTER to continue...";
            std::cin.ignore();
            std::cin.get();
        } 
        else if (choice == 3) {
            int id = getValidIntInput("✏️ Enter Student ID to update: ");
            std::string name, department;
            int age = -1;

            std::cout << BOLD << CYAN << "Enter new name (leave empty to keep unchanged): " << RESET;
            std::getline(std::cin, name);

            std::cout << BOLD << CYAN << "Enter new age (or -1 to keep unchanged): " << RESET;
            std::cin >> age;
            std::cin.ignore();

            std::cout << BOLD << CYAN << "Enter new department (leave empty to keep unchanged): " << RESET;
            std::getline(std::cin, department);

            loadingEffect("Updating student details");
            Student::updateStudent(id, name, age, department);
        } 
        else if (choice == 4) {
            int id = getValidIntInput("🗑️ Enter Student ID to delete: ");
            loadingEffect("Deleting student");
            Student::deleteStudent(id);
        } 
        else if (choice == 5) {
            std::cout << BOLD << "👋 Exiting the program...\n" << RESET;
            break;
        } 
        else {
            std::cout << RED << "❌ Invalid choice! Please enter a valid option.\n" << RESET;
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }
    }

    return 0;
}
