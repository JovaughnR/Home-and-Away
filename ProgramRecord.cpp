#include "ProgramRecord.h"

ProgramRecord::ProgramRecord()
{
    this->maxCourses = 8;
    /* Checking if the program file is available, if not it will create one. */
    this->awAcc = "";
    if (!isProgramsAvailable())
        programAndDetails();
}
ProgramRecord::ProgramRecord(string pName, string pCode)
{
    /* A constructor that takes in two parameters and assigns them to the class variables. */
    this->programName = pName;
    this->programCode = pCode;
}

ProgramRecord::~ProgramRecord()
{
    // freeMemory();
}

void ProgramRecord::configureProgramList(int col)
{
    try
    {
        /* Creating a 2D array of strings. */
        programs = new string *[this->rows];
        for (int i = 0; i < this->rows; i++)
            programs[i] = new string[col];
    }
    /*
     * It catches the exception and prints the error message,exception object that was thrown.
     */
    catch (std::bad_alloc &exception)
    {
        std::cerr << "Programme Record Error: " << exception.what() << '\n';
    }
}

void ProgramRecord::populateProgramList(int col, str2dVec prog[])
{
    for (int i = 0; i < this->rows; i++)
        for (int j = 0; j < col; j++)
            programs[i][j] = prog[0][i][j];
}

// utily method
void ProgramRecord::saveProgramDetails(int columns, str2dVec prog[])
{
    /* Creating a file object and assigning the value of the parameter to the class variable. */
    ofstream file;
    this->cols = columns;
    /* Creating a 2D array of strings. */
    configureProgramList(this->cols);
    /* Populating the 2D array of strings with the values of the parameter. */
    populateProgramList(this->cols, prog);
    /* Opening a file called programFile.bin in binary mode. */
    file.open("programFile.bin", ios::out | ios::binary);
    /* Writing the value of the class variable cols to the file. */
    file.write(reinterpret_cast<char *>(&this->cols), 4);
    /* Writing the values of the 2D array of strings to the file. */
    for (int i = 0; i < this->rows; i++)
        for (int j = 0; j < this->cols; j++)
            file.write(reinterpret_cast<char *>(&programs[i][j]), 45);

    /* Closing the file and freeing the memory. */
    file.close(), freeMemory();
}

void ProgramRecord::freeMemory()
{
    /* Freeing the memory allocated to the 2D array of strings. */
    try
    {
        for (int i = 0; i < this->rows; i++)
            delete[] programs[i];
        delete[] programs;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}

string ProgramRecord::getProgramCode()
{
    cout << "\033[1;94m\n\t\tEnter Program Code: ", fflush(stdin);
    getline(cin, programCode);
    /* Checking if the program code is a number. */
    for (int i = 0; i < programCode.length(); i++)
        if (int(programCode[i] - '0') < 0 || int(programCode[i] - '0') > 9)
        {
            clearConsole;
            cout << "\n\t\t\033[1;91mOnly Numbers Allowed!!\n";
            getProgramCode();
        }
    /* Checking if the program code is 4 digits long. */
    if (programCode.length() != 4)
    {
        clearConsole;
        /* Printing the error message in red. */
        cout << "\n\t\t\033[1;91millegal Program Code length!!\n";
        cout << "\t\t\033[1;95mAbsolutely 4 required!!\n";
        /* Returning the value of the function getProgramCode() */
        return getProgramCode();
    }

    return programCode;
}

string ProgramRecord::getProgramName()
{
    cout << "\033[1;94m\n\n\t\tEnter Program Name: ", fflush(stdin);
    getline(cin, programName);
    /* Checking if the length of the program name is greater than 24, if it is it will print an error
    message and return the value of the function getProgramName(). */
    if (programName.length() > 24)
    {
        clearConsole;
        /* Printing the error message in red. */
        cout << "\n\t\t\033[1;91mCourse Name too long!!\n";
        return getProgramName();
    }
    return programName;
}

void ProgramRecord::selectProgram(str2dVec prog[], int *progIndex)
{
    char option;
    cout << ("\033[1;94m") << "\n\n\t\tSelect the number that matches with the program\n\n\n";
    /* Printing the programs available in the program file. */
    for (int i = 1; i <= prog[0][0].size(); i++)
        cout << "\t\t\t" << i << ".\t" << prog[0][0][i - 1] << "\n";

    cout << "\n\t\t======> ";
    cin >> option;

    /* Checking if the option selected is within the range of the program list. */
    if (int(option - '0') < 1 || int(option - '0') > prog[0][0].size())
    {
        clearConsole;
        cout << ("\n\t\t\033[1;91m") << option << " isn't a valid option!!\n";
        selectProgram(prog, progIndex);
    }
    /* Subtracting the value of the option selected by the user from the ASCII value of 0 and
    subtracting 1 from it. */
    *progIndex = int(option - '0') - 1;
}

void ProgramRecord::readInPrograms()
{
    ifstream file;
    file.open("programFile.bin", ios::in | ios::binary);
    file.read(reinterpret_cast<char *>(&this->cols), 4);
    configureProgramList(this->cols);
    /* Reading the values of the 2D array of strings from the file. */
    for (int i = 0; i < this->rows; i++)
        for (int j = 0; j < this->cols; j++)
            file.read(reinterpret_cast<char *>(&programs[i][j]), 45);

    file.close();
}

void ProgramRecord::setCurrentPrograms(str2dVec prog[])
{
    vector<string> temp;
    /* Copying the values of the 2D array of strings to a vector of strings. */
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < this->cols; j++)
            temp.push_back(programs[i][j]);

        prog[0].push_back(temp);
        temp.clear();
    }
}

void ProgramRecord::programAndDetails()
{
    /* Creating a 2D vector of strings, for programme list*/
    str2dVec programList = {
        {"Computer Science", "Management Information"},
        {"1001", "1042"},
        {"0", "0"}};

    /* Creating a 2D vector of strings, for programme list. */
    str2dVec programArray[1] = {programList};
    /* Calling the function saveProgramDetails() and passing the size of the first vector of the 2D
    vector of strings and the 2D vector of strings as parameters. */
    saveProgramDetails(programArray[0][0].size(), programArray);
}

bool ProgramRecord::isProgramsAvailable()
{
    /* Checking if the file is available, if it is not it will throw an exception. */
    try
    {
        ifstream file("programFile.bin", ios::in | ios::binary);
        if (file.fail())
            throw false;
    }
    catch (bool error)
    {
        return error;
    }
    return true;
}