system: main.o system.o Staff.o Student.o Courses.o ProgramRecord.o
	g++ main.o system.o Staff.o Student.o Courses.o ProgramRecord.o -o main

main.o: main.cpp
	g++ -c main.cpp -std=c++20

system.o: system.cpp
	g++ -c system.cpp -std=c++20 

Staff.o: Staff.cpp
	g++ -c Staff.cpp -std=c++20 

Student.o: Student.cpp
	g++ -c Student.cpp -std=c++20 

Courses.o: Courses.cpp 
	g++ -c Courses.cpp -std=c++20

ProgramRecord.o: ProgramRecord.cpp
	g++ -c ProgramRecord.cpp -std=c++20

clean:
	rm *.o *.bin system






