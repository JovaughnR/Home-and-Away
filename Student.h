#ifndef STUDENT_H
#define STUDENT_H
#include "ProgramRecord.h"
#include "system.h"

class Student : public System
{
protected:
    User stud;

private:
    int amountCourses;
    string studentFullName;
    string *selectedCourses;

public:
    Student();
    ~Student();
    time_t now = time(NULL);
    struct tm date = *localtime(&now);
    void selectProgram(str2dVec prog[]);
    void selectCourses(str2dVec prog[], str2dVec course[], vector<string> &selected, string currStud, bool state);
    void readInStudentData(string filename, int id);
    void saveInStudentData(string filename);
    int findUserId(int currentId, string currUser);
    void generateFeeBreakDown(vector<string> selected, str2dVec course[], string currStud);
    void addStudentsData(str2dVec prog[], int (*func)());
    bool findSelectedCourses(vector<string> &c, int s, string currStud);
    void saveSelectedCourses(vector<string> selected, string currStud);
    void configureSelectedCoursesList(vector<string> selected);
    void viewProgramDetails(str2dVec prog[], str2dVec course[]);
    void generateProgressReport(vector<string> selected, string currStud);
    void viewMyData(string currentUser);
};
#endif