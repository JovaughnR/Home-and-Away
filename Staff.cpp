#include "Staff.h"

void Staff::ProgramAdmin::addCourse(str2dVec course[], str2dVec prog[], vector<int> &v, int &pI, int size)
{
    /* Printing the list of courses in the program. */
    cout << "\n\n\t\tList of courses in the " << prog[0][0][pI] << " program\n\n";
    for (int i = 0; i < course[0][pI].size(); ++i)
        /* Printing the courses in the first semester. */
        if (!course[0][pI].size())
        {
            cout << "\t\tNo Courses Here\n";
            break;
        }
        else
            cout << "\t\t\t" << i + 1 << ".\t" << course[0][pI][i] << "\n";
    /* Adding a new course to the course array. */
    addNewCourse(course, v, size, pI);
}

void Staff::ProgramAdmin::removeCourse(str2dVec course[], char opt, int &pI, vector<int> &v)
{
    /* Calling the function displayCoursesAndDetails and passing the course, v, and pI variables to it. */
    displayCoursesAndDetails(course, v, pI);
    /* Iterating through the course vector and printing out the courses that the student is enrolled in. */
    int inc = 0;
    cout << "\033[0m \033[1;93m\n\n\t\tEnter 'Y' beside the course you wish to remove!!\n";
    cout << "\t\tEnter 'N' to not remove the course!!\n";
    cout << "\033[1;95m\t\tEnter 'X' to quit at any moment!\n\n\n";
    for (auto i = course[0][pI].begin(); i != course[0][pI].end(); ++i)
    {
        cout << ("\n\t\t\t\033[1;94m Remove '") << *i << "' : ", fflush(stdin);
        cin >> opt;
        opt = toupper(opt);
        /* Removing a student from a course. */
        if (opt == 'Y' && course[0][pI].size())
        {
            swap(inc, course[1][pI], course[1][pI].size());
            course[1][pI].pop_back();
            swap(inc, course[2][pI], course[2][pI].size());
            course[2][pI].pop_back();
            swap(inc, course[3][pI], course[3][pI].size());
            course[3][pI].pop_back();
            swap(inc, course[4][pI], course[4][pI].size());
            course[4][pI].pop_back();
            swap(inc, course[5][pI], course[5][pI].size());
            course[5][pI].pop_back();
            cout << ("\n\t\t\t\033[9;91m ") << *i << ("\033[0m") << " removed!!\n";
            course[0][pI].erase(i);
            --i;
        }
        else if (opt == 'N')
            inc++;
        else if (opt == 'X')
            break;
        else
        {
            cout << "\t\t" << opt << " isn't a valid option!!\n";
            --i;
        }
    }
    /* Finding the size of the vector at the first index of the course array. */
    v[pI] = course[0][pI].size();
    amountCourses[pI] = course[0][pI].size();
    int rows = course[0].size();
    /* The below code is a C++ program that is used to store the details of students in a file. */
    ConfigureAndInitialize(rows, v);
    populateArray(course, rows, v, 0);
    saveDetails(rows, v);
    freeMemoryAllocated(rows);
    /* Clearing the console and then printing the text in green. */
    clearConsole;
    cout << ("\n\t\t\033[1;92m") << "Modifications applied successfully\n\n";
}

void Staff::ProgramAdmin::swap(int inc, vector<string> &arr, const int size)
{
    /* Checking if the value of inc is not equal to the value of size - 1. */
    if (inc != (size - 1))
    {
        /* Swapping the values of the array. */
        string temp = arr[inc];
        arr[inc] = arr[inc + 1];
        arr[inc + 1] = temp;
        swap(inc + 1, arr, size);
    }
}

void Staff::ProgramAdmin::progModification()
{
    /* The below code is a C++ code that is used to display the menu for the user to select the option
    they want to use. */
    cout << ("\033[1;93m") << "\n\n\t\t\t      The Home And Away Institute of Learning";
    cout << ("\033[1;95m") << "\n\t\t\t  ^v^v^v^v^v^v^v^                    ^v^v^v^v^v^v^v^\n";
    cout << ("\033[1;96m") << "\t\t\t\t  Programmes Modification Section\n";
    cout << ("\033[1;97m") << "\t\t\t  ^v^v^v^v^v^v^v^                    ^v^v^v^v^v^v^v^\n\n";
    cout << ("\033[1;96m") << "\t\t\t\t  A.\t\tAdd Courses\n\t\t\t\t  R.\t\tRemove Courses\n";
    cout << ("\033[1;96m") << "\t\t\t\t  E.\t\tEdit Course\n\n\t\t\t\t  C.\t\tCancel\n\n";
    cout << ("\033[1;94m") << "\t\t\t  ======> ";
}

void Staff::ProgramAdmin::editCourses(int pI, str2dVec courses[], vector<int> v) // pI for program index
{
    char opt;
    /* The below code is calling the function displayCoursesAndDetails and passing the variables
    courses, v, and pI. */
    displayCoursesAndDetails(courses, v, pI);
    editingOptions();
    cin >> opt;

    /* A goto statement. */
    if (opt == 'X' || opt == 'x')
        goto end;

    else
    {
        /* The below code is checking if the user input is valid. If the user input is not valid, the
        program will ask the user to input again. */
        if (int(opt - '0') < 1 || int(opt - '0') > 5)
        {
            cout << opt << " isn't a option!!\n";
            editCourses(pI, courses, v);
        }
        if (int(opt - '0') == 1)
            changeCourseName(pI, courses, v);
        if (int(opt - '0') == 2)
            changeCourseCode(pI, courses, v);
        if (int(opt - '0') == 3)
            changeCredit(pI, courses, v);
        if (int(opt - '0') == 4)
            changePrerequisite(pI, courses, v);
        if (int(opt - '0') == 5)
            changeDescription(pI, courses, v);
    }
end:
    clearConsole;
    int rows = courses[0].size();
    /* The below code is initializing the array, populating the array, saving the details and freeing
    the memory allocated. */
    ConfigureAndInitialize(rows, v);
    populateArray(courses, rows, v, 0);
    saveDetails(rows, v);
    freeMemoryAllocated(rows);
    cout << "\t\t\033[3:92m Changes applied sucessfully!!\n\n";
}

void Staff::ProgramAdmin::changeCourseName(int pI, str2dVec courses[], vector<int> v)
{
    char opt;
    for (int i = 0; i < v[pI]; i++)
    {
        /* Asking the user to input a new name for the course. */
        cout << "\n\t\tChange name of " << courses[0][pI][i] << " to: ", fflush(stdin);
        cin >> opt;
        /* Checking if the user wants to enter a course name. If the user enters 'Y' or 'y' then the user
        is prompted to enter a course name. If the user enters 'N' or 'n' then the program continues.
        If the user enters 'X' or 'x' then the program breaks. If the user enters anything else then
        the program will decrement the value of i and print out that the option entered is not valid. */
        if (opt == 'Y' || opt == 'y')
            courses[0][pI][i] = getCourseName();
        else if (opt == 'N' || opt == 'n')
            continue;
        else if (opt == 'X' || opt == 'x')
            break;
        else
            --i, cout << opt << " isn't valid option!!\n";
    }
}

void Staff::ProgramAdmin::changeCourseCode(int pI, str2dVec courses[], vector<int> v)
{
    char opt;
    for (int i = 0; i < v[pI]; i++)
    {
        /* Asking the user to enter the new course code. */
        cout << "\n\t\tChange Course Code of " << courses[0][pI][i] << " to: ", fflush(stdin);
        cin >> opt;
        /* Checking if the user wants to enter another course code. */
        if (opt == 'Y' || opt == 'y')
            courses[1][pI][i] = getCourseCode();
        else if (opt == 'N' || opt == 'n')
            continue;
        else if (opt == 'X' || opt == 'x')
            break;
        else
            --i, cout << opt << " isn't valid option!!\n";
    }
}

void Staff::ProgramAdmin::changeCredit(int pI, str2dVec courses[], vector<int> v)
{
    char opt;
    for (int i = 0; i < v[pI]; i++)
    {
        /* Asking the user to input the new credit of the course. */
        cout << "\n\t\tChange Credit of " << courses[0][pI][i] << " to: ", fflush(stdin);
        /* Asking the user if they want to add a course. If they say yes, it will ask them for the
        credit hours. If they say no, it will go back to the beginning of the loop. If they say x, it
        will break out of the loop. If they enter anything else, it will go back to the beginning of
        the loop and ask them again. */
        cin >> opt;
        if (opt == 'Y' || opt == 'y')
            courses[2][pI][i] = getCredit();
        else if (opt == 'N' || opt == 'n')
            continue;
        else if (opt == 'X' || opt == 'x')
            break;
        else
            --i, cout << opt << " isn't valid option!!\n";
    }
}

void Staff::ProgramAdmin::changePrerequisite(int pI, str2dVec courses[], vector<int> v)
{
    char opt;
    for (int i = 0; i < v[pI]; i++)
    {
        cout << "\n\t\tChange Prerequisite of " << courses[0][pI][i] << " to: ", fflush(stdin);
        cin >> opt;
        /* Asking the user if they want to add a prerequisite course. If they do, it will call the
        getPrerequisites function. If they don't, it will continue. If they enter X or x, it will
        break out of the loop. If they enter anything else, it will decrement i and tell the user
        that the option they entered is invalid. */
        if (opt == 'Y' || opt == 'y')
            courses[3][pI][i] = getPrerequisites();
        else if (opt == 'N' || opt == 'n')
            continue;
        else if (opt == 'X' || opt == 'x')
            break;
        else
            --i, cout << opt << " isn't valid option!!\n";
    }
}

void Staff::ProgramAdmin::changeDescription(int pI, str2dVec courses[], vector<int> v)
{
    char opt;
    for (int i = 0; i < v[pI]; i++)
    {
        cout << "\n\t\tChange Description of " << courses[0][pI][i] << " to: ", fflush(stdin);
        cin >> opt;
        /* The below code is asking the user if they want to add a prerequisite to the course. If they
        say yes, then it will call the getPrerequisites function. If they say no, then it will
        continue to the next course. If they say exit, then it will break out of the loop. If they
        enter anything else, then it will decrement the counter and tell the user that the option they
        entered is not valid. */
        if (opt == 'Y' || opt == 'y')
            courses[4][pI][i] = getPrerequisites();
        else if (opt == 'N' || opt == 'n')
            continue;
        else if (opt == 'X' || opt == 'x')
            break;
        else
            --i, cout << opt << " isn't valid option!!\n";
    }
}

void Staff::ProgramAdmin::editingOptions()
{
    /* Printing the menu for the user to choose from. */
    cout << "\033[1:95m\n\n\t\t\t\t1\t\tTo Change Course Name\n";
    cout << "\t\t\t\t2\t\tTo Change Course Code\n";
    cout << "\t\t\t\t3\t\tTo Change Course Credit\n";
    cout << "\t\t\t\t4\t\tTo Change Course Prerequisite\n";
    cout << "\t\t\t\t5\t\tTo Change Course Description\n";
    cout << "\n\t\t\t\tX\t\tTo Quit Editing\n\n\n\t\t\t  ====> ";
}

void Staff::ProgramAdmin::createProgram(str2dVec prog[], str2dVec course[], vector<int> &v, bool True)
{
    char amount;
    vector<string> temp1, temp2, temp3;
    if (True)
    {
        /* Copying the first row of the 2D vector prog into the 1D vectors temp1, temp2, and temp3. */
        for (int i = 0; i < prog[0][0].size(); i++)
        {
            temp1.push_back(prog[0][0][i]);
            temp2.push_back(prog[0][1][i]);
            temp3.push_back(prog[0][2][i]);
        }

        /* Pushing back the program name, program code and 0 into the temp1, temp2 and temp3 vectors. */
        temp1.push_back(getProgramName());
        temp2.push_back(getProgramCode());
        temp3.push_back("0"), prog[0].clear();
        /* Pushing back the strings temp1, temp2, and temp3 into the vector prog[0]. */
        prog[0].push_back(temp1);
        prog[0].push_back(temp2);
        prog[0].push_back(temp3);
    }
    cout << "\n\t\tHow many courses will you add: ", fflush(stdin);
    cin >> amount;
    /* Checking if the amount of courses is between 0 and 8. */
    if (int(amount - '0') < 0 || int(amount - '0') > 8)
    {
        cout << amount << " is not legal\n";
        True = false;
        createProgram(prog, course, v, True);
    }
    /* The below code is saving the program details in a vector. */
    saveProgramDetails(prog[0][0].size(), prog);
    v.push_back(int(amount - '0'));
    addProgramCourses(course, int(amount - '0'));
    cout << "\033[1;92m\n\t\tProgram Created Sucessfully!!";
}

void Staff::generateStudentList(str2dVec prog[])
{
    string proCode;
    /* Printing the list of program codes. */
    cout << "\t\tList of Program Codes:\n\n";
    for (int i = 0; i < prog[0][1].size(); i++)
        cout << "\t\t" << i + 1 << ".\t" << prog[0][1][i] << "\n";

    cout << "\n\t\tEnter program Code: ", fflush(stdin);
    cin >> proCode;

    /* Converting the string to uppercase. */
    for (int i = 0; i < proCode.length(); i++)
        proCode[i] = toupper(proCode[i]);

    /* The below code is reading the binary file and checking if the programme code is the same as the
    one entered by the user. If it is, it will call the userData function and pass the user object,
    true, false and 1 as arguments. */
    try
    {
        ifstream file("registerStudentFile.bin", ios::in | ios::binary);
        if (file.fail())
            throw errno;
        while (file)
        {
            file.read(reinterpret_cast<char *>(&stud), sizeof(stud));
            if (proCode == stud.programmeCode)
                userData(user, true, false, 1);
        }
        file.close();
    }
    catch (int err)
    {
        std::cerr << errno;
    }
    continueOn(), clearConsole;
}

// utility method
int Staff::amountNreg()
{
    int amount = 0;
    string currName = "";
    ifstream file("StudentsData.bin", ios::in | ios::binary);
    /* Counting the amount of students in the file. */
    while (file)
    {
        file.read(reinterpret_cast<char *>(&stud), sizeof(stud));
        if (!stud.isRegistered)
            /* Checking if the current name is not the same as the student's first name and if the
            student's first name is not empty. If both of these are true, then the current name is
            set to the student's first name and the amount is incremented. */
            if (currName != stud.firstName && stud.firstName != "")
            {
                currName = stud.firstName;
                amount++;
            }
    }
    file.close();
    return amount;
}

bool Staff::registerStudent(int id, int nUnreg, str2dVec prog[], int i) // 3
{
    if (nUnreg == 0)
    {
        /* Saving the program details into the program record. */
        ProgramRecord program;
        program.saveProgramDetails(prog[0][0].size(), prog);
        clearConsole;
        return false;
    }
    char option;
    fstream fileIn("StudentsData.bin", ios::in | ios::out | ios::binary); // 6 4

    fileIn.seekg(id * sizeof(stud));
    // Reading the student record from the file.
    fileIn.read(reinterpret_cast<char *>(&stud), sizeof(stud));
    if (stud.isRegistered)
    {
        /* Closing the file. */
        fileIn.close();
        /* Recursively calling the function registerStudent() until the number of unregistered students
        is 0. */
        return registerStudent(id + 1, nUnreg, prog, i);
    }
    /* Clearing the console. */
    clearConsole;
    cout << "\n\n\t\t" << pos[i] << " Unregistered Student.\n\n";
    /* Calling the userData function with the arguments stud, true, false, and 1. */
    userData(stud, true, false, 1);
    while (true)
    {
        cout << ("\033[0;94m") << "\n\n\t\tConfirm Registration (Y\\N): ";
        cin >> option;
        option = toupper(option);
        /* The below code is asking the user if they want to continue the program. */
        if (option == 'Y')
            break;
        if (option == 'N')
        {
            /* Recursively calling the function registerStudent() until the number of unregistered
            students is 0. */
            fileIn.close();
            return registerStudent(id + 1, nUnreg - 1, prog, i + 1);
        }

        /* Printing the text in red color. */
        cout << ("\033[0;91m") << "\n\t\tInvalid Option Type!!\n";
    }
    ofstream fileOut("registerStudentFile.bin", ios::app | ios::binary);
    /* Setting the isRegistered variable to true and then clearing the console. */
    stud.isRegistered = true, clearConsole;
    /* Assigning the value of the function generateId to the variable idNumber. */
    stud.idNumber = generateId(stud.selectedProgram, prog);
    cout << "\n\t\tGenerated ID Number is: \033[1;96m" << stud.idNumber << "\n\n";
    /* Moving the pointer to the position of the student in the file. */
    fileIn.seekp(id * sizeof(stud));
    /* Writing the contents of the stud variable to the file. */
    fileIn.write(reinterpret_cast<char *>(&stud), sizeof(stud));
    fileOut.write(reinterpret_cast<char *>(&stud), sizeof(stud));
    /* The below code is a function that is used to register a student. */
    cout << ("\033[1;92m") << "\n\n\t\t" << stud.firstName << " Registered Successfully!!\n\n";
    fileIn.close(), fileOut.close();
    continueOn();
    /* Recursively calling the function registerStudent() until the base case is reached. */
    return registerStudent(id + 1, nUnreg - 1, prog, i + 1);
}

// utility method
string Staff::generateId(string program, str2dVec prog[])
{
    string currIdNumber;
    int inc = 0;
    char currYear[4];
    string seq;
    /* Iterating through the first vector in the first vector in the vector of vectors. */
    for (int i = 0; i < prog[0][0].size(); i++)
        /* Checking if the program is in the list of programs. If it is, it will increment the number
        of times it has been used. */
        if (program == prog[0][0][i])
        {
            currIdNumber = prog[0][2][i];
            prog[0][2][i] = to_string(int(prog[0][2][i][0] - '0') + 1);
            inc = i;
        }
    /* Getting the current year. */
    strftime(currYear, 4, "%Y", &date);
    /* Creating a sequence of numbers from 1 to the number of the current id number. */
    sequence(&seq, int(currIdNumber[0] - '0') + 1);
    /* Returning the current year plus the value of the first element of the first element of the second
    element of the prog array. */
    return currYear + prog[0][1][inc] + seq;
}

// utility method
void Staff::sequence(string *seq, int idCount)
{
    /* The below code is checking the value of idCount and then assigning a string to seq based on the
    value of idCount. */
    if (idCount < 9)
        *seq = "00" + to_string(idCount);

    else if (idCount > 9 && idCount < 100)
        *seq = "0" + to_string(idCount);
    else
        *seq = to_string(idCount);
}
