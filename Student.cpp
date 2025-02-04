#include "Student.h"
#include <iostream>
#include <cstring>
#include <sstream>

Student::Student(int id, std::string name, int age, std::string department)
    : id(id), name(name), age(age), department(department) {}

void Student::save() {
    Database *db = Database::getInstance();
    MYSQL *conn  = db->getConnection();

    std::stringstream query;
    query << "INSERT INTO students (id, name, age, department) VALUES ("
          << id << ", '" << name << "', " << age << ", '" << department << "')";

    if (db->executeQuery(query.str())) {
        std::cout << "✅ Student saved successfully!\n";
    } else {
        std::cout << "❌ Failed to save student!\n";
    }
}

void Student::fetchAll() {
    Database *db = Database::getInstance();
    MYSQL_RES *res = db->fetchQuery("SELECT * FROM students");

    if (!res) {
        std::cout << "❌ Could not fetch students" << std::endl;
        return;
    }

    MYSQL_ROW row;
    while ((row = mysql_fetch_row(res))) {
        std::cout << "📌 ID: " << row[0] << " | Name: " << row[1] 
                  << " | Age: " << row[2] << " | Department: " << row[3] << std::endl;
    }
    mysql_free_result(res);
}

bool Student::updateStudent(int id, const std::string& name, int age, const std::string& department) {
    Database* db = Database::getInstance();
    std::stringstream query;
    query << "UPDATE students SET ";
    
    if (!name.empty()) query << "name = '" << name << "', ";
    if (age != -1) query << "age = " << age << ", ";
    if (!department.empty()) query << "department = '" << department << "', ";
    
    query.seekp(-2, query.cur);
    query << " WHERE id = " << id;

    return db->executeQuery(query.str());
}

bool Student::deleteStudent(int id) {
    Database* db = Database::getInstance();
    std::stringstream query;
    query << "DELETE FROM students WHERE id = " << id;
    return db->executeQuery(query.str());
}
