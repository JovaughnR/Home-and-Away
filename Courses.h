#ifndef COURSES_H
#define COURSES_H
#include <iostream>
#include <iomanip>
#include <new>
#include <vector>
#include <fstream>
#include <unistd.h>
#include <stdexcept>

#define str2dVec std::vector<std::vector<std::string> >
// #define clearConsole system("cls")
#define clearConsole system("clear")

using std::cin;
using std::cout;
using std::fstream;
using std::ifstream;
using std::ios;
using std::left;
using std::ofstream;
using std::right;
using std::setw;
using std::string;
using std::to_string;
using std::vector;

class Courses
{
private:
    int rows;
    string credit;
    string courseCode;
    string courseName;
    string prerequisite;
    string courseDescription;

protected:
    int *amountCourses;
    string **courses;
    string **credits;
    string **courseCodes;
    string **prerequisites;
    string **description;
    string **certificate;

public:
    Courses();
    ~Courses();

    void readInDetails(vector<int> v, int rows);
    void ConfigureAndInitialize(int &rows, vector<int> v);
    void populateArray(str2dVec course[], int rows, vector<int> v, int inc);
    void freeMemoryAllocated(int size);
    string getCourseName();
    string getCourseCode();
    string getCredit();
    string getDescription();
    string getPrerequisites();
    string selectProgType();
    void saveDetails(int row, vector<int> &cols);
    void getRowsCols(int *row, vector<int> &cols);
    void addNewCourse(str2dVec course[], vector<int> &v, int row, int pI);
    void getCourseDetails(str2dVec course[], int pI, int inc);
    bool isCoursesAvailable();
    void setCurrentCourses(str2dVec course[], int rows, vector<int> v, int inc);
    void addProgramCourses(str2dVec course[], int amount);
    void coursesAndDetials();
    void configureAmountOfCourses(vector<int> &v1, int *size);
    void displayCoursesAndDetails(str2dVec courses[], vector<int> v, int pI);
};
#endif
