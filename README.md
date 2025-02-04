Here’s a **detailed README** for your **Student Database Management System**. It includes setup instructions, database connection changes, terminal UI customization, and snippets. 🚀  

---

## **📚 Student Database Management System**  

A simple **C++** application to **add, fetch, update, and delete** student records using **MySQL** as the database. The program is designed with **Object-Oriented Programming (OOP)** principles and provides a **beautiful terminal UI** with colors and animations.

---

## **⚡ Features**  
✅ Add Student  
✅ Fetch All Students  
✅ Update Student Details  
✅ Delete Student  
✅ Beautiful UI with animations  
✅ Secure Database Connection  
✅ Error Handling  

---

## **🛠️ Technologies Used**  
- **C++** (Object-Oriented Programming)  
- **MySQL** (Relational Database Management System)  
- **MySQL C++ Connector** (MySQL API)  
- **Multi-threading** (for loading effects)  
- **ANSI Escape Codes** (for terminal styling)  

---

## **🚀 How to Run Locally**  

### **1️⃣ Install Required Dependencies**  
Make sure you have the following installed:  

- **g++** (C++ Compiler)  
- **MySQL Server** (Installed via Docker or locally)  
- **MySQL C++ Connector**  

To install them on **Ubuntu**, run:  
```bash
sudo apt update
sudo apt install g++ libmysqlclient-dev
```

For **Windows**, install **MySQL Connector C++** from [MySQL Official Website](https://dev.mysql.com/downloads/connector/cpp/).  

---

### **2️⃣ Clone the Repository**
```bash
git clone https://github.com/Tulsee/student_management_system_cpp.git
cd student_management_system_cpp
```

---

### **3️⃣ Configure Database Connection**  
Open **`config.h`** and update these values with your database credentials:  
```cpp
#define DB_HOST "localhost"
#define DB_USER "root"
#define DB_PASS "yourpassword"
#define DB_NAME "student_db"
```

If you're using **Docker**, find the MySQL container’s IP:  
```bash
docker inspect mysql-container-name | grep "IPAddress"
```
And replace `DB_HOST` with that IP.

---

### **4️⃣ (OPTIONAL) Create Database and Table**  
Run the following SQL commands in **MySQL**:
```sql
CREATE DATABASE student_db;
USE student_db;

CREATE TABLE students (
    id INT PRIMARY KEY,
    name VARCHAR(100),
    age INT,
    department VARCHAR(100)
);
```

---

### **5️⃣ Compile and Run the Program**  
To compile using **Makefile**, simply run:
```bash
make
```
Then execute the program:
```bash
./student_management 
```
Alternatively, compile manually with:
```bash
g++ main.cpp Student.cpp Database.cpp Security.cpp -o main -lmysqlclient -pthread
./main
```

---

## **🎨 Terminal UI (Customization)**
The UI is styled using **ANSI escape codes** for better readability.

### **Example UI**
```
=====================================
 📚 Student Database Management System
=====================================
1. Add Student
2. Fetch All Students
3. Update Student
4. Delete Student
5. Exit
Enter your choice: 
```

### **Modify Colors in `main.cpp`**
You can change **text colors** in `main.cpp`:
```cpp
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define CYAN    "\033[36m"
#define RED     "\033[31m"
```
For example, to make text **blue**, replace:
```cpp
#define CYAN    "\033[34m"
```

---

## **📝 Features Overview & Code Snippets**

### **➕ Add Student**
Snippet from `main.cpp`:
```cpp
std::cout << "Enter student name: ";
std::getline(std::cin, name);
Student student(id, name, age, department);
student.save();
```
### **📜 Fetch All Students**
```cpp
Student::fetchAll();
```

### **✏️ Update Student**
Handles **empty input** correctly:
```cpp
std::getline(std::cin, ageInput);
if (!ageInput.empty()) { 
    age = std::stoi(ageInput);
}
```

### **🗑 Delete Student**
```cpp
int id = getValidIntInput("Enter student ID to delete: ");
Student::deleteStudent(id);
```

---

## **🐞 Troubleshooting**  

### **1️⃣ MySQL Table Doesn't Exist**  
If you get:  
```
Error Code: 1146. Table 'student_db.students' doesn't exist
```
Run the SQL script again:
```sql
CREATE TABLE students (
    id INT PRIMARY KEY,
    name VARCHAR(100),
    age INT,
    department VARCHAR(100)
);
```

### **2️⃣ MySQL Connection Fails**  
Check if MySQL is running:
```bash
sudo systemctl start mysql
```
Or restart Docker container:
```bash
docker restart mysql-container-name
```

### **3️⃣ Compilation Issues**
If `mysql/mysql.h` is missing, install:
```bash
sudo apt install libmysqlclient-dev
```

---

## **🤝 Contributing**
Feel free to open an issue or contribute to improving the **Student Database Management System**! 🎉

---

## **📜 License**
This project is licensed under the **MIT License**.

---

This **README** gives everything you need to **run, configure, and customize** your project. Let me know if you need further improvements! 🚀😊
