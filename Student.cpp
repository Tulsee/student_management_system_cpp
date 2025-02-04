#include "Student.h"
#include <iostream>
#include <cstring>
#include <sstream>

Student::Student(int id, std::string name, int age, std::string department)
    : id(id), name(name), age(age), department(department) {}

void Student::save() {
    Database *db = Database::getInstance();
    MYSQL *conn  = db->getConnection();

    const char *query = "INSERT INTO students (id, name, age, department) VALUES (?, ?, ?, ?)";
    MYSQL_STMT *stmt = mysql_stmt_init(conn);
    if (!stmt) {
        std::cout << "❌ Could not initialize MYSQL statement" << std::endl;
        return;
    }

    mysql_stmt_prepare(stmt, query, strlen(query));

    MYSQL_BIND bind[4] = {0};
    bind[0].buffer_type = MYSQL_TYPE_LONG;
    bind[0].buffer = &id;
    bind[1].buffer_type = MYSQL_TYPE_STRING;
    bind[1].buffer = (void*)name.c_str();
    bind[1].buffer_length = name.length();
    bind[2].buffer_type = MYSQL_TYPE_LONG;
    bind[2].buffer = &age;
    bind[3].buffer_type = MYSQL_TYPE_STRING;
    bind[3].buffer = (void*)department.c_str();
    bind[3].buffer_length = department.length();

    mysql_stmt_bind_param(stmt, bind);
    mysql_stmt_execute(stmt);
    mysql_stmt_close(stmt);

    std::cout << "✅ Student saved successfully" << std::endl;
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
    MYSQL* conn = db->getConnection();
    
    std::stringstream query;
    query << "UPDATE students SET ";

    bool hasPrev = false;
    if (!name.empty()) {
        query << "name = '" << name << "'";
        hasPrev = true;
    }
    if (age != -1) {
        if (hasPrev) query << ", ";
        query << "age = " << age;
        hasPrev = true;
    }
    if (!department.empty()) {
        if (hasPrev) query << ", ";
        query << "department = '" << department << "'";
    }

    query << " WHERE id = " << id;

    if (!hasPrev) {
        std::cout << "❌ No changes provided for update!\n";
        return false;
    }

    bool success = db->executeQuery(query.str());
    if (success) {
        std::cout << "✅ Student updated successfully!\n";
    } else {
        std::cout << "❌ Student update failed! Check if the ID exists.\n";
    }

    return success;
}
