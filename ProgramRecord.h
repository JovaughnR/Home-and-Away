#ifndef PROGRAM_RECORD_H
#define PROGRAM_RECORD_H
#include <fstream>
#include <iostream>
#include <vector>
#include "Courses.h"

class ProgramRecord
{
private:
    const int rows = 3;
    int cols;
    string programName;
    string programCode;
    int maxCourses;
    string awAcc;

protected:
    string **programs;

public:
    ProgramRecord();
    ProgramRecord(string pName, string pCode);
    ~ProgramRecord();

    void configureProgramList(int col);
    void populateProgramList(int col, str2dVec prog[]);
    // utility method
    void saveProgramDetails(int columns, str2dVec prog[]);
    void freeMemory();
    string getProgramCode();
    string getProgramName();
    void selectProgram(str2dVec prog[], int *progIndex);
    void readInPrograms();
    void setCurrentPrograms(str2dVec prog[]);
    void programAndDetails();
    bool isProgramsAvailable();
    // void readOutPrograms();
};

#endif