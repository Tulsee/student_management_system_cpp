#ifndef DATABASE_H
#define DATABASE_H

#include </usr/include/mysql/mysql.h>
#include <iostream>
#include <mutex>

class Database {
private:
    static Database *instance;
    MYSQL *conn;
    static std::mutex dbMutex;
    Database(); // Private constructor for Singleton

public:
    static Database* getInstance();
    ~Database();
    MYSQL* getConnection();
    bool executeQuery(const std::string &query);
    MYSQL_RES* fetchQuery(const std::string &query);
};

#endif
