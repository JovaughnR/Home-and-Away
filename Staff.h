#ifndef STAFF_H
#define STAFF_H
#include "Student.h"
#include "ProgramRecord.h"

class Staff : public Student
{
public:
    int idCount;

    class ProgramAdmin : public Courses, public ProgramRecord
    {
    public:
        void addCourse(str2dVec course[], str2dVec prog[], vector<int> &v, int &pI, int size);
        void removeCourse(str2dVec course[], char opt, int &pI, vector<int> &v);
        void swap(int inc, vector<string> &arr, const int size);
        void progModification();
        void editCourses(int pI, str2dVec courses[], vector<int> v);
        void changeCourseName(int pI, str2dVec courses[], vector<int> v);
        void changeCourseCode(int pI, str2dVec courses[], vector<int> v);
        void changeCredit(int pI, str2dVec courses[], vector<int> v);
        void changePrerequisite(int pI, str2dVec courses[], vector<int> v);
        void changeDescription(int pI, str2dVec courses[], vector<int> v);
        void editingOptions();
        void createProgram(str2dVec prog[], str2dVec course[], vector<int> &v, bool True);
    };

    void generateStudentList(str2dVec prog[]);
    int amountNreg();
    bool registerStudent(int id, int nUnreg, str2dVec prog[], int i);
    // utility method
    string generateId(string program, str2dVec prog[]);
    // utility method
    void sequence(string *seq, int idCount);
};

#endif

// going to make modifcations to this file so if i should undo then i should stop here