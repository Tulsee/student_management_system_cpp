#include "Database.h"
#include "config.h"
#include <fstream>

std::mutex Database::dbMutex;
Database* Database::instance = nullptr;

Database::Database() {
    conn = mysql_init(nullptr);
    conn = mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, NULL, 0);
    if (!conn) {
        std::cerr << "Database Connection Failed: " << mysql_error(conn) << std::endl;
        exit(1);
    }
}

Database::~Database() {
    mysql_close(conn);
}

Database* Database::getInstance() {
    if (!instance) {
        instance = new Database();
    }
    return instance;
}

MYSQL* Database::getConnection() {
    return conn;
}

bool Database::executeQuery(const std::string &query) {
    std::lock_guard<std::mutex> lock(dbMutex);
    if (mysql_query(conn, query.c_str())) {
        std::cerr << "Query Execution Failed: " << mysql_error(conn) << std::endl;
        return false;
    }
    return true;
}

MYSQL_RES* Database::fetchQuery(const std::string &query) {
    std::lock_guard<std::mutex> lock(dbMutex);
    if (mysql_query(conn, query.c_str())) {
        return nullptr;
    }
    return mysql_store_result(conn);
}
