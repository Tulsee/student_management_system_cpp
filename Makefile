all: student_management

student_management: main.o Database.o Student.o Security.o
	g++ -o student_management main.o Database.o Student.o Security.o -lmysqlclient -lssl -lcrypto

main.o: main.cpp
	g++ -c main.cpp

Database.o: Database.cpp
	g++ -c Database.cpp

Student.o: Student.cpp
	g++ -c Student.cpp

Security.o: Security.cpp
	g++ -c Security.cpp

clean:
	rm -f *.o student_management
