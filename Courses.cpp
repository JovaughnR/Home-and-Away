#include <vector>
#include <fstream>
#include <unistd.h>
#include "Courses.h"

/**
 * A constructor of the class Courses. To check if Courses is Available
 * And Get Courses and Details
 */

Courses::Courses()
{
    if (!isCoursesAvailable())
        coursesAndDetials();
}

/**
 * The destructor for the Courses class.
 */
Courses::~Courses()
{
    delete[] amountCourses;
}

void Courses::readInDetails(vector<int> v, int rows)
{
    ConfigureAndInitialize(rows, v);
    /* The above code is opening a file called courseFile.bin in binary mode. */
    std::ifstream file("courseFile.bin", std::ios::in | std::ios::binary);

    /* Moving the file pointer to the beginning of the second column. */
    file.seekg(4 + (sizeof(v[0]) * rows));
    /* The below code is reading the data from the file and storing it in the arrays. */
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < v[i]; j++)
        {
            file.read(reinterpret_cast<char *>(&courses[i][j]), 32);
            file.read(reinterpret_cast<char *>(&courseCodes[i][j]), 32);
            file.read(reinterpret_cast<char *>(&credits[i][j]), 24);
            file.read(reinterpret_cast<char *>(&prerequisites[i][j]), 32);
            file.read(reinterpret_cast<char *>(&description[i][j]), 32);
            file.read(reinterpret_cast<char *>(&certificate[i][j]), 24);
        }
    // closing file
    file.close();
}

void Courses::ConfigureAndInitialize(int &rows, vector<int> v)
{
    // configure the  with the amount of rows and columns
    try
    {
        courses = new string *[rows];
        courseCodes = new string *[rows];
        credits = new string *[rows];
        prerequisites = new string *[rows];
        description = new string *[rows];
        certificate = new string *[rows];
        for (int i = 0; i < rows; i++)
        {
            /* Creating a 2D array of strings. */
            courses[i] = new string[v[i]];
            courseCodes[i] = new string[v[i]];
            credits[i] = new string[v[i]];
            prerequisites[i] = new string[v[i]];
            description[i] = new string[v[i]];
            certificate[i] = new string[v[i]];
        }
    }
    /**
     * It catches the bad_alloc exception and prints out the error message.
     *  The exception object that was thrown.
     */

    catch (const std::bad_alloc &e)
    {
        std::cerr << "Course Error: " << e.what() << '\n';
    }
}

void Courses::populateArray(str2dVec course[], int rows, vector<int> v, int inc) // utility method to help configure the system. 1 time use
{
    if (inc != 6)
    {
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < v[i]; j++)
            {
                /* The below code is assigning the values of the array course to the other arrays. */
                if (inc == 0)
                    courses[i][j] = course[inc][i][j];
                if (inc == 1)
                    courseCodes[i][j] = course[inc][i][j];
                if (inc == 2)
                    credits[i][j] = course[inc][i][j];
                if (inc == 3)
                    prerequisites[i][j] = course[inc][i][j];
                if (inc == 4)
                    description[i][j] = course[inc][i][j];
                if (inc == 5)
                    certificate[i][j] = course[inc][i][j];
            }
        populateArray(course, rows, v, inc + 1);
    }
}

void Courses::freeMemoryAllocated(int size)
{
    /*
    In a try catch exception
    The  code below is deleting the dynamically allocated memory. for Course Details
    */
    try
    {
        for (int i = 0; i < size; i++)
        {

            delete[] courses[i];
            delete[] courseCodes[i];
            delete[] credits[i];
            delete[] prerequisites[i];
            delete[] description[i];
            delete[] certificate[i];
        }
        delete[] courses;
        delete[] courseCodes;
        delete[] credits;
        delete[] prerequisites;
        delete[] description;
        delete[] certificate;
    }
    catch (const std::exception &e)
    {
        /* The above code is printing the error message to the standard error stream. */
        std::cerr << e.what() << '\n';
    }
}

string Courses::getCourseName()
{
    /* Printing the text in blue color. then  Clearing the buffer.*/
    cout << "\033[1;94m\n\n\t\tEnter course name: ", fflush(stdin);
    /* Checking if the course name is too long. greater than 24 */
    if (courseName.length() > 24)
    {
        clearConsole;
        cout << "\n\t\t\033[1;91mCourse Name too long!!\n";
        return getCourseName();
    }
    /* Getting the course name from the user. */
    getline(cin, this->courseName);
    /* Returning the courseName variable. */
    return this->courseName;
}

string Courses::getCourseCode()
{
    /* Printing the text in blue color,Flushing the input stream. */
    cout << "\t\t\033[1;94mEnter Course Code: ", fflush(stdin);
    /* Asking the user to input a course code. */
    cin >> courseCode;
    /* Checking if the course code is longer than 8 characters.
     If it is, it will clear the console and print an error message. */
    if (courseCode.length() > 8)
    {
        clearConsole;
        cout << "\n\t\t\033[1;91mCourse Code length too long!!\n";
        return getCourseCode();
    }
    /* Converting the course code to uppercase. */
    for (int i = 0; i < courseCode.length(); i++)
        courseCode[i] = toupper(courseCode[i]);
    return courseCode;
}

string Courses::getCredit()
{
    /* The above code is asking the user to enter the amount of credit. */
    cout << "\033[1;94m\t\tEnter amount of credit: ", fflush(stdin); /* Flushing the input buffer. */
    cin >> credit;
    /* Checking if the first character of the credit string is between 1 and 4. */
    if (int(credit[0] - '0') < 1 || int(credit[0] - '0') > 4)
    {
        clearConsole;
        cout << "\n\t\t\033[3;91millegal credit amount!!\n";
        cout << "\t\t\033[3;95mLegal Amount is 1 - 4\n";
        getCredit();
    }
    /* Returning the value of the variable credit. */
    return credit;
}

string Courses::getDescription()
{
    /* Get a short description from user then Flushing the input buffer. */
    cout << "\t\t\033[1;94mWrite a short description about course: ", fflush(stdin);
    getline(cin, courseDescription);
    /* Checking if the length of the course description is greater than 24. If it is, it will clear the
    console and print out a message saying that the description is too long. */
    if (courseDescription.length() > 24)
    {
        clearConsole;
        cout << "\n\t\t\033[1;91mDescription too long!!\n";
        return getDescription();
    }
    /* Returning the courseDescription variable. */
    return courseDescription;
}

string Courses::getPrerequisites()
{
    /* Printing the text in blue. */
    cout << "\t\t\033[1;94mEnter Prerequisite: ", fflush(stdin);
    /* Reading a line of input from the user and storing it in the variable prerequisite. */
    getline(cin, prerequisite);
    /* Checking the length of the course description. If it is greater than 24, it will clear the
    console and print an error message. */
    if (courseDescription.length() > 24)
    {
        clearConsole;
        cout << "\n\t\t\033[1;91mPrerequisite length too long!!\n";
        return getPrerequisites();
    }
    /*  */
    return prerequisite;
}

string Courses::selectProgType()
{
    char option;
    /* Printing the text in the quotes in the colour magenta. */
    cout << "\033[1;95m\n\n\t\t\tPROGRAMME TYPES \033[1;92m ******\n\n";
    /* Printing the text in yellow color. */
    cout << "\033[3;93m\t\t\t\t1.  Certificate Programme\n";
    cout << "\t\t\t\t2.  Diploma Programme\n";
    cout << "\t\t\t\t3.  Associates Programme\033[0m\n\n";
    /* Printing the text in blue color. */
    cout << "\033[1;94m\t\t\t======> ";
    cin >> option;
    /* Checking if the user input is a valid option. */
    if (int(option - '0') < 1 || int(option - '0') > 3)
    {
        clearConsole;
        cout << "\033[1;91m\t\t" << option << " is not a valid option!!\n";
        selectProgType();
    }
    /* Converting the variable option to a string.  and storing it in opt*/
    string opt = std::to_string(option);
    /* Returning the value of opt. */
    return opt;
}

void Courses::saveDetails(int size, vector<int> &cols)
{
    /* Checking if the size is not equal to zero, if it is not equal to zero, then it will set the rows
    to the size. */
    if (size)
        this->rows = size;

    /* Creating a file called courseFile.bin and opening it in binary mode. */
    std::ofstream file("courseFile.bin", std::ios::out | std::ios::binary);

    /* Writing the number of rows and the number of courses in each row to the file. */
    file.write(reinterpret_cast<char *>(&this->rows), 4);
    for (int i = 0; i < this->rows; i++)
        file.write(reinterpret_cast<char *>(&amountCourses[i]), 4);

    for (int i = 0; i < size; i++)
        /* The below code is writing the data to the file. */
        for (int j = 0; j < cols[i]; j++)
        {
            file.write(reinterpret_cast<char *>(&courses[i][j]), 32);
            file.write(reinterpret_cast<char *>(&courseCodes[i][j]), 32);
            file.write(reinterpret_cast<char *>(&credits[i][j]), 24);
            file.write(reinterpret_cast<char *>(&prerequisites[i][j]), 32);
            file.write(reinterpret_cast<char *>(&description[i][j]), 32);
            file.write(reinterpret_cast<char *>(&certificate[i][j]), 24);
        }
    file.close();
}

void Courses::getRowsCols(int *row, vector<int> &cols)
{
    /* The above code is opening a file called courseFile.bin in binary mode. */
    std::ifstream file("courseFile.bin", std::ios::in | std::ios::binary);
    /* Reading the number of rows in the file. */
    file.read(reinterpret_cast<char *>(&this->rows), 4);
    amountCourses = new int[this->rows];
    /* The above code is reading the amount of courses for each student. */
    for (int i = 0; i < this->rows; i++)
    {
        file.read(reinterpret_cast<char *>(&amountCourses[i]), 4);
        cols.push_back(amountCourses[i]);
    }
    /* Closing the file. */
    file.close();
    /* Assigning the value of the rows variable to the row variable. */
    *row = this->rows;
}

void Courses::addNewCourse(str2dVec course[], vector<int> &v, int row, int pI)
{
    /* Calling the getCourseDetails function with the parameters course, pI, and 0. */
    getCourseDetails(course, pI, 0);
    this->rows = course[0].size();
    /* Finding the size of the vector at the first index of the course array. */
    v[pI] = course[0][pI].size();
    /* Finding the number of courses in each program. */
    amountCourses[pI] = course[0][pI].size();
}

void Courses::getCourseDetails(str2dVec course[], int pI, int inc) // pI represents the program index
{
    /* The below code is checking if the value of inc is not equal to 6. If it is not equal to 6, then
    it will check if the value of inc is equal to 0. If it is equal to 0, then it will push back the
    value of selectProgType() into the vector course[5][pI]. If the value of inc is equal to 1, then
    it will push back the value of getCourseName() into the vector course[0][pI]. If the value of inc
    is equal to 2, then it will push back the value of getCourse */
    if (inc != 6)
    {
        if (inc == 0)
            course[5][pI].push_back(selectProgType());

        if (inc == 1)
            course[0][pI].push_back(getCourseName());

        if (inc == 2)
            course[1][pI].push_back(getCourseCode());

        if (inc == 3)
            course[2][pI].push_back(getCredit());

        if (inc == 4)
            course[3][pI].push_back(getPrerequisites());

        if (inc == 5)
            course[4][pI].push_back(getDescription());

        /* Calling the getCourseDetails function recursively. */
        getCourseDetails(course, pI, inc + 1);
    }
}

bool Courses::isCoursesAvailable()
{
    try
    {
        /* Checking if the file exists. */
        std::ifstream file("courseFile.bin", std::ios::in | std::ios::binary);
        if (file.fail())
            throw false;
        file.close();
    }
    catch (bool error)
    {
        return error;
    }
    return true;
}

void Courses::setCurrentCourses(str2dVec course[], int rows, vector<int> v, int inc)
{
    if (inc != 6)
    {
        /* Declaring a vector of strings called temp. */
        vector<string> temp;
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < v[i]; j++)
            {
                /* The above code is pushing back the data from the arrays into the temp vector. */
                if (inc == 0)
                    temp.push_back(courses[i][j]);
                if (inc == 1)
                    temp.push_back(courseCodes[i][j]);
                if (inc == 2)
                    temp.push_back(credits[i][j]);
                if (inc == 3)
                    temp.push_back(prerequisites[i][j]);
                if (inc == 4)
                    temp.push_back(description[i][j]);
                if (inc == 5)
                    temp.push_back(certificate[i][j]);
            }
            /* Pushing back the string temp into the vector course[inc] */
            course[inc].push_back(temp);
            temp.clear();
        }
        /* A recursive function that is adding 1 to the value of inc and then
         returning the value of inc. */
        setCurrentCourses(course, rows, v, inc + 1);
    }
}

void Courses::addProgramCourses(str2dVec course[], int amount)
{
    /* Declaring a vector of strings called temp, temp1, temp2, temp3, temp4, and temp5. */
    vector<string> temp, temp1, temp2, temp3, temp4, temp5;
    for (int i = 0; i < amount; i++)
    {
        /* The above code is pushing back the values of the functions into the vectors. */
        temp5.push_back(selectProgType());
        temp.push_back(getCourseName());
        temp1.push_back(getCourseCode());
        temp2.push_back(getCredit());
        temp3.push_back(getPrerequisites());
        temp4.push_back(getDescription());
    }
    /* Pushing back the values of the temp variables into the course vector. */
    course[0].push_back(temp);
    course[1].push_back(temp1);
    course[2].push_back(temp2);
    course[3].push_back(temp3);
    course[4].push_back(temp4);
    course[5].push_back(temp5);

    /* Clearing the contents of the vectors. */
    temp.clear(), temp1.clear(), temp2.clear();
    temp3.clear(), temp4.clear(), temp5.clear();
}

void Courses::coursesAndDetials()
{
    this->rows = 2;
    /* The below code is creating a 2D vector of strings containing list of Courses. */
    str2dVec courseList = {
        {"Programming I", "Computer Networks", "Computer Logic", "Data Base Management", "Programming II", "Information Technology", "Statistics",
         "Discrete Mathematics", "Web Programming", "Data Structures"},
        {"Business Law", "Prob and Stats", "Web 1", "Academic Writing 2", "Programming 1",
         "Web 2", "Information Technology", "Academic Writing 1", "Discrete Math", "Accounting"}};

    /* The below code is creating a 2D vector of strings containing list of Course Codes */
    str2dVec courseCodeList = {
        {"CMP1024", "CMP1026", "CLDD331", "DBMS145", "CMP1353", "INT1001", "STAT4243", "MAT1008", "WPG3431", "DTST352"},
        {"BSD1003", "PAS1020", "WPG3431", "ACW5829", "CMP1024", "WPG1003", "INT1001", "ACW8525", "MAT1008", "ACC7532"}};

    /* The below code is creating a 2D vector of strings containing list of Course Credits */
    str2dVec creditList = {
        {"2", "3", "3", "4", "4", "3", "3", "4", "2", "4"},
        {"2", "3", "4", "3", "3", "3", "4", "2"}};
    /* The below code is creating a 2D vector of strings containing list of Course Pre RequisiteList */
    str2dVec prerequisiteList = {
        {"None", "None", "None", "None", "None", "None", "None", "None", "None", "None"},
        {"None", "None", "None", "None", "None", "None", "None", "None", "None", "None"}};

    /* The below code is creating a 2D vector of strings containing list of Course Descriptions */
    str2dVec descriptionList = {
        {"Coding", "Configuring Networks", "Binary", "Databases", "Coding",
         "Technologies", "Maths", "Maths", "Web Development", "algorithms"},
        {"Entrapeneurship", "Maths", "Web development", "Writing", "Coding", "web development", "Technologies", "Writing", "Maths", "Accounting"}};

    /* The below code is creating a 2D vector of strings containing list of Certificates*/
    str2dVec certificate = {
        {"1", "2", "2", "2", "2", "1", "2", "1", "1", "2"},  // 1 represent a certificate progamme
        {"1", "2", "1", "2", "1", "1", "2", "2", "2", "2"}}; // 2 represents a diploma programme

    /* Creating a Vector of Course attributes*/
    str2dVec course[6] = {
        courseList, courseCodeList, creditList,
        prerequisiteList, descriptionList, certificate};

    vector<int> values = {10, 10}; // values represents the amount of courses is in each programs
                                   /* Calling the configureAmountOfCourses function and passing the values array and the address of the
                                   rows variable. */
    configureAmountOfCourses(values, &this->rows);

    /* Calling the ConfigureAndInitialize function with the number of rows and the values. */
    ConfigureAndInitialize(this->rows, values);
    /* Populating the array course with the values in the array values. */
    populateArray(course, this->rows, values, 0);
    /* Calling the saveDetails function and passing the rows and values as parameters. */
    saveDetails(this->rows, values);
    /* Freeing the memory allocated to the rows array. */
    freeMemoryAllocated(this->rows);
}

void Courses::configureAmountOfCourses(vector<int> &v1, int *size)
{
    /* Creating a new array of ints and copying the values from the vector into the array. */
    *size = v1.size();
    amountCourses = new int[*size];
    for (int i = 0; i < *size; i++)
        amountCourses[i] = v1[i];
}

void Courses::displayCoursesAndDetails(str2dVec courses[], vector<int> v, int pI)
{
    /* Clearing the console. */
    clearConsole;
    /* Printing the courses of the selected program. */
    cout << ("\033[1;95m \033[3;95m\n\n\t\t\033[7;95m") << std::left << std::setw(25) << "COURSE NAME" << std::setw(15) << "COURSE CODE" << std::setw(10) << "CREDIT" << std::setw(15) << "PREREQUISITE" << std::setw(24) << "DESCRIPTION" << std::setw(1) << "\n";
    for (int i = 0; i < v[pI]; i++)
        cout << ("\t\t\033[1;94m") << std::left << std::setw(25) << courses[0][pI][i] << std::setw(15) << courses[1][pI][i] << std::setw(10) << courses[2][pI][i] << std::setw(15) << courses[3][pI][i] << std::setw(24) << courses[4][pI][i] << "\n";
    cout << ("\033[0m");
}

// changes are going to make here right now
