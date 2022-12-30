#include "Staff.h"
#include "Student.h"
#define ProAd Staff::ProgramAdmin
#define Sys System
#define Admin System::Administrator

std::string files[] = {
    "StaffAccounts.bin",
    "StudentsData.bin",
};

string currentUser;

/* The below code is a function that is used to log out of the system. */
void logOut(Sys sys, Admin admin, Staff staff, Student stud, ProAd proAd, str2dVec course[], str2dVec prog[], vector<int> v, string type);

/* A function prototype for a function that takes in a system, admin, staff, student, proAd, course,
prog, and vector of ints. */
void studViewProgDetails(Sys sys, Admin admin, Staff staff, Student stud, ProAd proAd, str2dVec course[], str2dVec prog[], vector<int> v);

/* A function that adds a course to a student's course list. */
void studAddCourse(Sys sys, Admin admin, Staff staff, Student stud, ProAd proAd, str2dVec course[], str2dVec prog[], vector<int> v);

void studMainConstruct(Sys sys, Admin admin, Staff staff, Student stud, ProAd proAd, str2dVec course[], str2dVec prog[], vector<int> v);

/* A function that generates a fee breakdown for a student. */
void studGenerateFeeBreakdown(Sys sys, Admin admin, Staff staff, Student stud, ProAd proAd, str2dVec course[], str2dVec prog[], vector<int> v);

/* A function that generates a progress report for a student. */
void studGenerateProgressReport(Sys sys, Admin admin, Staff staff, Student stud, ProAd proAd, str2dVec course[], str2dVec prog[], vector<int> v);

/* Declaring a function called mainConstruct. */
void mainConstruct(Sys sys, Admin admin, Staff staff, ProAd proAd, Student stud, str2dVec prog[], str2dVec course[], vector<int> v);

void staffMainConstruct(Sys sys, Admin admin, Staff staff, Student stud, ProAd proAd, str2dVec prog[], str2dVec course[], vector<int> v);

void staffRegisterStud(Sys sys, Admin admin, Staff staff, Student stud, ProAd proAd, str2dVec course[], str2dVec prog[], vector<int> v);

/* Creating a program for a student. */
void staffCreateProgram(ProAd proAd, str2dVec prog[], str2dVec course[], vector<int> v);

/* A function prototype for a function that modifies a program. */
void staffModifyProgram(Sys sys, Admin admin, Staff staff, Student stud, ProAd proAd, str2dVec prog[], str2dVec course[], vector<int> v);

/* Declaring a function that takes in a 2D vector of strings and a Staff object and returns nothing. */
void staffGenerateStudList(str2dVec prog[], Staff staff);

void AdminMainConstruct(Sys sys, Admin admin, Staff staff, Student stud, ProAd proAd, str2dVec course[], str2dVec prog[], vector<int> v, string type);

int main(void)
{
    /* Creating objects of the classes Admin, Staff, Student, ProAd and Sys. */
    Admin admin;
    Staff staff;
    Student student;
    ProAd proAd;
    Sys sys;

    // check if the Sys was already configured
    if (!admin.isAdminSetup()) // check if the initial admin configuration was already done
    {
        /* Setting the admin account to the first account in the system. */
        admin.setAdminAccount(sys, 0);
    }

    if (!admin.isAccountsCreated())
    {
        /* Creating a staff account. */
        admin.createStaffAccounts(sys, 0);
        sys.continueOn();
    }

    int rows, cols;
    /* The below code is declaring a 2D vector of strings. */
    str2dVec courses, courseCodes, courseCredits;
    str2dVec prerequisites, descriptions, programs;
    str2dVec certificates, courseArray[6], programArray[1];
    vector<int> v;

    programArray[0] = programs;
    /* Calling the readInPrograms function from the proAd class. */
    proAd.readInPrograms();
    proAd.setCurrentPrograms(programArray);
    // test create program if problem the put free memory function here

    proAd.getRowsCols(&rows, v);
    /* The below code is reading in the details of the courses from the file and then setting the
    current courses. */
    courseArray[0] = courses, courseArray[1] = courseCodes;
    courseArray[2] = courseCredits, courseArray[3] = prerequisites;
    courseArray[4] = descriptions, courseArray[5] = certificates;

    proAd.readInDetails(v, rows);
    proAd.setCurrentCourses(courseArray, rows, v, 0);
    proAd.freeMemoryAllocated(rows);

    /* Calling the mainConstruct function. */
    mainConstruct(sys, admin, staff, proAd, student, programArray, courseArray, v);
    return 0;
}

void staffGenerateStudList(str2dVec prog[], Staff staff)
{
    clearConsole;
    /* Calling the generateStudentList function from the staff class and passing the prog variable as
    an argument. */
    staff.generateStudentList(prog);
}

void staffModifyProgram(Sys sys, Admin admin, Staff staff, Student stud, ProAd proAd, str2dVec prog[], str2dVec course[], vector<int> v)
{
    char option;
    int progIndex, rows;
    proAd.progModification(), fflush(stdin);
    std::cin >> option;
    /* The below code is a function that is used to modify the program. */
    if (option == 'A' || option == 'a')
    {
        clearConsole;
        proAd.selectProgram(prog, &progIndex);
        proAd.addCourse(course, prog, v, progIndex, rows);
        rows = course[0].size();
        proAd.ConfigureAndInitialize(rows, v);
        proAd.populateArray(course, rows, v, 0);
        proAd.saveDetails(rows, v);
        proAd.freeMemoryAllocated(rows);
        /* Calling the staffModifyProgram function. */
        staffModifyProgram(sys, admin, staff, stud, proAd, prog, course, v);
    }
    else if (option == 'R' || option == 'r')
    {
        clearConsole;
        proAd.selectProgram(prog, &progIndex);
        proAd.removeCourse(course, option, progIndex, v);
        staffModifyProgram(sys, admin, staff, stud, proAd, prog, course, v);
    }
    else if (option == 'E' || option == 'e')
    {
        proAd.selectProgram(prog, &progIndex);
        proAd.editCourses(progIndex, course, v);
        staffModifyProgram(sys, admin, staff, stud, proAd, prog, course, v);
    }
    else if (option == 'C' || option == 'c')
    {
        clearConsole, staffMainConstruct(sys, admin, staff, stud, proAd, prog, course, v);
    }
    clearConsole;
    cout << "\n\033[1;91m\t\t" << option << " is not a valid option!!\n";
    /* Calling the function staffModifyProgram. */
    staffModifyProgram(sys, admin, staff, stud, proAd, prog, course, v);
}

void staffCreateProgram(ProAd proAd, str2dVec prog[], str2dVec course[], vector<int> v)
{
    int rows, cols;
    /* The below code is creating a program, configuring the amount of courses, configuring and
    initializing the program, populating the array, saving the details and freeing the memory
    allocated. */
    proAd.createProgram(prog, course, v, true);
    proAd.configureAmountOfCourses(v, &rows);
    proAd.ConfigureAndInitialize(rows, v);
    proAd.populateArray(course, rows, v, 0);
    proAd.saveDetails(rows, v);
    proAd.freeMemoryAllocated(rows);
}

void staffRegisterStud(Sys sys, Admin admin, Staff staff, Student stud, ProAd proAd, str2dVec course[], str2dVec prog[], vector<int> v)
{
    int numUnreg = staff.amountNreg();
    /* Checking if there are any unregistered students. If there are, it will register them. If not, it
    will display a message saying there are no students to register. */
    if (numUnreg)
    {
        staff.registerStudent(0, numUnreg, prog, 0);
        staffMainConstruct(sys, admin, staff, stud, proAd, prog, course, v);
    }
    else
    {
        clearConsole, cout << "\n\t\tNo Students to register!!\n";
        staffMainConstruct(sys, admin, staff, stud, proAd, prog, course, v);
    }
}

void staffMainConstruct(Sys sys, Admin admin, Staff staff, Student stud, ProAd proAd, str2dVec prog[], str2dVec course[], vector<int> v)
{
    char option;
    sys.staffLoginScreen();
    std::cin >> option;
    /* The below code is the main menu for the staff. */
    if (option == 'R' || option == 'r')
        clearConsole, staffRegisterStud(sys, admin, staff, stud, proAd, course, prog, v);

    else if (option == 'P' || option == 'p')
    {
    start:
        sys.programAdminScreen();
        cin >> option;
        /* The below code is a goto statement. It is used to jump to a specific location in the code. */
        if (option == 'C' || option == 'c')
        {
            clearConsole, staffCreateProgram(proAd, prog, course, v);
            staffMainConstruct(sys, admin, staff, stud, proAd, prog, course, v);
        }
        else if (option == 'M' || option == 'm')
            clearConsole, staffModifyProgram(sys, admin, staff, stud, proAd, prog, course, v);

        else if (option == 'G' || option == 'g')
        {
            clearConsole, staffGenerateStudList(prog, staff);
            staffMainConstruct(sys, admin, staff, stud, proAd, prog, course, v);
        }
        else if (option == 'X' || option == 'x')
            staffMainConstruct(sys, admin, staff, stud, proAd, prog, course, v);
        else
        {
            clearConsole;
            cout << "\n\t\t" << option << " is not a valid option!!\n";
            goto start;
        }
    }
    else if (option == 'X' || option == 'x')
        logOut(sys, admin, staff, stud, proAd, course, prog, v, "STAFF");
    else
    {
        clearConsole;
        cout << "\n\t\t" << option << " is not a valid option!!\n";
        staffMainConstruct(sys, admin, staff, stud, proAd, prog, course, v);
    }
}

void mainConstruct(Sys sys, Admin admin, Staff staff, ProAd proAd, Student stud, str2dVec prog[], str2dVec course[], vector<int> v)
{
    /* The below code is asking the user to input a character. */
    char option;
    sys.signInOptions();
    std::cin >> option;
    if (option == 'L' || option == 'l')
    {
        sys.signInAs();
        std::cin >> option;
        /* The below code is checking if the user input is between 1 and 4. If it is not, it will print
        an error message and ask the user to input again. */
        while (int(option - '0') < 1 || int(option - '0') > 4)
        {
            std::cout << ("\033[1;91m") << "\n\t\tNot a valid Option!!\n";
            sys.signInAs();
            std::cin >> option;
        }
        /* A switch statement that is used to call the main function. */
        if (int(option - '0') == 4)
            main();

        /* The below code is checking if the user has selected the option 1, if yes, then it will check
        if the user is an admin, if yes, then it will call the AdminMainConstruct function. */
        if (int(option - '0') == 1)
        {
            if (admin.loginAdmin(&sys, "AdminFile.bin", 0, 0))
            {
                AdminMainConstruct(sys, admin, staff, stud, proAd, prog, course, v, "ADMIN");
            }
            else
            {
                cout << "\n\t\t\033[1;91mYour Login Doesn't match any in the system!!\n";
                mainConstruct(sys, admin, staff, proAd, stud, prog, course, v);
            }
        }

        /* The below code is checking if the user is a staff or student. If the user is a staff, the
        staffMainConstruct function is called. If the user is a student, the studMainConstruct
        function is called. */
        if (sys.loginSystem(files[int(option - '0') - 2], &currentUser, int(option - '0') - 2))
        {
            if (int(option - '0') - 1 == 1)
                staffMainConstruct(sys, admin, staff, stud, proAd, prog, course, v);
            else if (int(option - '0') - 1 == 2)
                studMainConstruct(sys, admin, staff, stud, proAd, course, prog, v);
        }
        else
            /* Calling the mainConstruct function. */
            mainConstruct(sys, admin, staff, proAd, stud, prog, course, v);
    }
    else if (option == 'S' || option == 's')
    {
    begin:
        sys.signUpAs();
        std::cin >> option;
        /* Converting the char option to an int. */
        int index = int(option - '0');
        /* A recursive function. */
        if (index == 3)
            main();
        if (index == 1)
        {
            std::cout << "\n\tUse the User Name provided by administrator to sign up!!\n\n";
            /* The below code is a function that is used to sign up a new user. */
            sys.signUp("StaffAccounts.bin", main, 0);
            sys.saveInUserData("StaffAccounts.bin", 0);
            cout << "\n\t\tSigned up Successfully!!\n";
            sys.continueOn(), main();
        }
        if (index == 2)
            /* The below code is adding the students data to the program. */
            stud.addStudentsData(prog, main);

        else
        {
            clearConsole;
            cout << "\n\033[1;91m\t\t" << option << " is not a valid option!!\n";
            goto begin;
        }
    }
    else if (option == 'X' || option == 'x')
        exit(0);
    else
    {
        cout << "\n\033[1;91m\t\t" << option << " is not a valid option!!\n";
        /* Calling the mainConstruct function and passing the variables sys, admin, staff, proAd, stud,
        prog, course, v to it. */
        mainConstruct(sys, admin, staff, proAd, stud, prog, course, v);
    }
}

void AdminMainConstruct(Sys sys, Admin admin, Staff staff, Student stud, ProAd proAd, str2dVec course[], str2dVec prog[], vector<int> v, string type)
{
    char option;
    admin.adminLoginScreen();
    cin >> option;
    if (option == 'C' || option == 'c')
    {
        /* Creating a staff account for the system. */
        admin.createStaffAccounts(sys, 0);
        /* Calling the AdminMainConstruct function. */
        sys.continueOn(), clearConsole;
        AdminMainConstruct(sys, admin, staff, stud, proAd, course, prog, v, type);
    }

    else if (option == 'R' || option == 'r')
    {
        /* Calling the function AdminMainConstruct to display the admin menu. */
        admin.resetProgCourseDataBase();
        AdminMainConstruct(sys, admin, staff, stud, proAd, course, prog, v, type);
    }
    else if (option == 'X' || option == 'x')
    {
        /* The below code is logging out the admin. */
        logOut(sys, admin, staff, stud, proAd, course, prog, v, "ADMIN");
        main();
    }
    else
    {
        clearConsole;
        cout << "\n\t\t\033[1;91m" << option << " isn't a valid option!!\n";
        /* Calling the AdminMainConstruct function. */
        AdminMainConstruct(sys, admin, staff, stud, proAd, course, prog, v, type);
    }
}

void studGenerateProgressReport(Sys sys, Admin admin, Staff staff, Student stud, ProAd proAd, str2dVec course[], str2dVec prog[], vector<int> v)
{
    vector<string> selectedCourses;
    /* The below code is calling the generateProgressReport function from the student class. */
    stud.generateProgressReport(selectedCourses, currentUser);
    studMainConstruct(sys, admin, staff, stud, proAd, course, prog, v);
}

void studGenerateFeeBreakdown(Sys sys, Admin admin, Staff staff, Student stud, ProAd proAd, str2dVec course[], str2dVec prog[], vector<int> v)
{
    vector<string> selectedCourses;
    /* The below code is calling the generateFeeBreakDown function from the student class. */
    stud.generateFeeBreakDown(selectedCourses, course, currentUser);
    studMainConstruct(sys, admin, staff, stud, proAd, course, prog, v);
}

void studMainConstruct(Sys sys, Admin admin, Staff staff, Student stud, ProAd proAd, str2dVec course[], str2dVec prog[], vector<int> v)
{
    char option;
    sys.studentLoginScreen();
    fflush(stdin);
    std::cin >> option;
    /* The below code is a function that is used to display the main menu for the student. */
    if (option == 'E' || option == 'e')
    {
    loop:
        sys.enrollmentScreen();
        cin >> option;
        option = toupper(option);
        /* The below code is a goto statement. It is used to jump to a specific location in the code. */
        if (option == 'V')
            studViewProgDetails(sys, admin, staff, stud, proAd, course, prog, v);
        else if (option == 'A')
            studAddCourse(sys, admin, staff, stud, proAd, course, prog, v);
        else if (option == 'G')
            studGenerateFeeBreakdown(sys, admin, staff, stud, proAd, course, prog, v);
        else if (option == 'X')
            studMainConstruct(sys, admin, staff, stud, proAd, course, prog, v);
        else
        {
            cout << "\n\033[1;91m\t\t" << option << " is not a valid option!!\n";
            goto loop;
        }
    }
    else if (option == 'P' || option == 'p')
        /* Calling the function studGenerateProgressReport() */
        studGenerateProgressReport(sys, admin, staff, stud, proAd, course, prog, v);

    else if (option == 'M' || option == 'm')
    {
        stud.viewMyData(currentUser);
        studMainConstruct(sys, admin, staff, stud, proAd, course, prog, v);
    }

    else if (option == 'X' || option == 'x')
        logOut(sys, admin, staff, stud, proAd, prog, course, v, "STUDENT");
    else
    {
        clearConsole;
        /* The below code is a function that is called when the user enters an invalid option. */
        cout << "\n\033[1;91m\t\t" << option << " is not a valid option!!\n";
        studMainConstruct(sys, admin, staff, stud, proAd, course, prog, v);
    }
}

void studAddCourse(Sys sys, Admin admin, Staff staff, Student stud, ProAd proAd, str2dVec course[], str2dVec prog[], vector<int> v)
{
    vector<string> selectedCourses;
    /* The below code is calling the selectCourses function from the student class. */
    stud.selectCourses(prog, course, selectedCourses, currentUser, false);
    studMainConstruct(sys, admin, staff, stud, proAd, course, prog, v);
}

void studViewProgDetails(Sys sys, Admin admin, Staff staff, Student stud, ProAd proAd, str2dVec course[], str2dVec prog[], vector<int> v)
{
    /* The below code is calling the viewProgramDetails function from the student class. */
    stud.viewProgramDetails(prog, course);
    studMainConstruct(sys, admin, staff, stud, proAd, course, prog, v);
}

void logOut(Sys sys, Admin admin, Staff staff, Student stud, ProAd proAd, str2dVec course[], str2dVec prog[], vector<int> v, string type)
{
    char option;
    /* Asking the user to confirm log out. */
    std::cout << "\033[4;96m\n\n\t\tConfirm LOG OUT. (Y\\N)\033[0m: ", fflush(stdin);
    std::cin >> option;
    /* The above code is asking the user if they want to run the program again. */
    if (option == 'Y' || option == 'y')
    {
        clearConsole;
        main();
    }
    /* Checking if the user input is equal to 'N' or 'n' */
    else if (option == 'N' || option == 'n')
    {
        /* The below code is checking the type of user that is logged in and then calling the
        appropriate function to display the main menu for that user. */
        if (type == "STUDENT")
        {
            clearConsole;
            studMainConstruct(sys, admin, staff, stud, proAd, course, prog, v);
        }
        if (type == "STAFF")
        {
            clearConsole;
            staffMainConstruct(sys, admin, staff, stud, proAd, prog, course, v);
        }
        if (type == "ADMIN")
        {
            clearConsole;
            AdminMainConstruct(sys, admin, staff, stud, proAd, course, prog, v, type);
        }
    }
    /* The below code is a switch statement that is used to determine the type of user that is logged in. */
    std::cout << "\n\tInvalid Option Type!!\n";
    logOut(sys, admin, staff, stud, proAd, prog, course, v, type);
}