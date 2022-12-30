#ifndef SYSTEM_H
#define SYSTEM_H
#include "ProgramRecord.h"

class System
{
protected:
    struct User
    {
        string idNumber;
        string firstName;
        string userName;
        string password;
        string lastName;
        string address;
        string dateStarted; // date employed or dateEnrolled
        string programmeCode;
        bool enrolmentStatus;
        string contactNumber;
        string selectedProgram;
        string programType;
        bool isRegistered;
        bool isCoursesSelected;
        int pI;
    } user;

public:
    time_t now = time(NULL);
    struct tm date = *localtime(&now);
    string pos[6] = {"1st", "2nd", "3rd", "4th", "5th", "6th"};

    System();
    ~System();
    string getFirstName(string firstName);
    string getLastName(string lastName);
    string getUserName(string userName, string filename, bool status, int index);
    string getAddress(string address);
    string getDateStarted(string dateStarted);
    string getFaculty(string faculty);
    string getDepartment(string department);
    string getContactNumber(string contactNumber);
    string setPassword(string password);
    void signInOptions();
    void signInAs();
    void signUpAs();
    void staffLoginScreen();
    void studentLoginScreen();
    void programAdminScreen();
    void enrollmentScreen();
    void addData(string userName);

    void userData(User user, bool stud, bool staff, int i);
    void readInUserData(string filename, int id, int index);
    void saveInUserData(string filename, int index);
    void signUp(string filename, int (*function)(), int index);
    bool loginSystem(string filename, string *currUser, int index);
    bool checkIfUserNameExist(string userName, string filename, int index);
    void continueOn();

    class Administrator
    {
    private:
        struct Admin
        {
            string userName;
            string password;
            string firstName;
            string lastName;
            string faculty;
            string department;
            bool isStaffCreated = false; // staff account
        } admin;

    public:
        bool isAccountsCreated();
        bool isAdminSetup();
        void setAdminAccount(System sys, int index);
        void createStaffAccounts(System sys, int index);
        bool checkForUserName(string userName, string filename);
        bool loginAdmin(System *sys, string filename, int trials, int index);
        bool resetProgCourseDataBase();
        void adminLoginScreen();
    };
};

#endif