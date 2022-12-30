#include "system.h"

System::System()
{
    /* The above code is initializing the user object. */
    user.address = "";
    user.idNumber = "None";
    user.lastName = "";
    user.userName = "None";
    user.password = "";
    user.firstName = "";
    user.dateStarted = "";
    user.contactNumber = "";
    user.programmeCode = "";
    user.isRegistered = false;
    user.enrolmentStatus = false;
    user.isCoursesSelected = false;
};

System::~System() {}

string System::getFirstName(string firstName)
{
    /* Taking the first letter of the first name and making it uppercase. */
    cout << ("\033[1;94m") << "\t\tEnter First Name: ", fflush(stdin);
    cin >> firstName;
    firstName[0] = toupper(firstName[0]);
    return firstName;
}

string System::getLastName(string lastName)
{
    /* Asking the user to enter their last name and then it is capitalizing the first letter of the
    last name. */
    cout << ("\033[1;94m") << "\t\tEnter Last name: ", fflush(stdin);
    cin >> lastName;
    lastName[0] = toupper(lastName[0]);
    return lastName;
}

string System::getUserName(string userName, string filename, bool status, int index)
{
    /* The above code is asking the user to enter their username. */
    cout << ("\033[1;94m") << "\n\n\t\tEnter User Name: ", fflush(stdin);
    cin >> userName;
    if (status)
        if (checkIfUserNameExist(userName, filename, index))
        {
            clearConsole;
            /* The above code is checking if the user name is already taken. If it is, it will ask the
            user to try a different user name. */
            cout << "\033[3;91m\n\t\tThat user Name is already taken!!\n";
            cout << "\033[1;94m\n\tTry creating a different user name\n\n";
            getUserName(userName, filename, status, index);
        }
    return userName;
}

string System::getAddress(string address)
{
    /* The above code is asking the user to enter their address. */
    cout << ("\033[1;94m") << "\t\tEnter address: ", fflush(stdin);
    getline(cin, address);
    if (address.length() > 40)
    {
        clearConsole;
        /* Checking if the address is too long. */
        cout << "\n\t\t\033[1;91mAddress word length too long!!\n";
        return getAddress(address);
    }
    return address;
}

string System::getDateStarted(string dateStarted)
{
    /* The below code is using the strftime function to format the date and time. */
    char dateTime[45];
    strftime(dateTime, 45, "%B %d, %Y", &date);
    dateStarted = dateTime;
    return dateStarted;
}
string System::getFaculty(string faculty)
{
    /* Setting the color of the text to be printed to blue. */
    cout << ("\033[1;94m") << "\t\tEnter Faculty: ", fflush(stdin);
    getline(cin, faculty);
    /* Checking if the length of the faculty is greater than 40. If it is, it will clear the console
    and print out an error message. */
    if (faculty.length() > 40)
    {
        clearConsole;
        cout << "\n\t\t\033[1;91mCourse Code length too long!!\n";
        return getFaculty(faculty);
    }
    /*  */
    return faculty;
}

string System::getDepartment(string department)
{
    /* Asking the user to enter the department. */
    cout << ("\033[1;94m") << "\t\tEnter Department: ", fflush(stdin);
    getline(cin, department);
    /* Checking if the length of the department is greater than 40. */
    if (department.length() > 40)
    {
        clearConsole;
        cout << "\n\t\t\033[1;91mCourse Code length too long!!\n";
        return getDepartment(department);
    }
    return department;
}

string System::getContactNumber(string contactNumber)
{
    /* The below code is asking the user to enter the contact number. */
    cout << ("\033[1;94m") << "\t\tEnter contact number: ";
    fflush(stdin);
    getline(cin, contactNumber);
    return contactNumber;
}

string System::setPassword(string password)
{
    string pass;
    /* The below code is asking the user to enter a password and then confirm the password. */
    cout << ("\033[1;96m") << "\n\n\t\tEnter Password: ", fflush(stdin);
    getline(cin, password);
    cout << ("\033[1;94m") << "\t\tConfirm Password: ", fflush(stdin);
    getline(cin, pass);
    /* Checking if the password is the same as the password that was entered. */
    if (pass != password)
    {
        cout << "\033[1;91m Passwords don't match\n";
        setPassword(password);
    }
    clearConsole;
    return password;
}

void System::signInOptions()
{
    /* The below code is a menu for the user to choose from. */
    cout << ("\033[1;93m") << "\n\n\t\t\t»‹^›‹^›‹^›‹^›‹^›‹^›‹^›‹^›‹^›‹^›‹^›‹^›‹^›‹^›‹^›‹^›«\n";
    cout << "\t\t\t" << ("\033[1;95m") << "Welcome to the Home and Away Institute of Learning\n";
    cout << ("\033[1;96m") << "\n\t\t\t\t    L.\t\t  Login";
    cout << ("\033[1;96m") << "\n\t\t\t\t    S.\t\t  Sign Up";
    cout << ("\033[1;96m") << "\n\t\t\t\t    X.\t\t  Exit\n";
    cout << ("\033[1;94m") << "\n\t\t\t\t==> ";
}

void System::signInAs()
{
    clearConsole;
    /* The below code is a simple menu that allows the user to select what type of user they are. */
    cout << ("\033[1;93m") << "\n\n\t\t Home And Away Institute of Learning 📝\n";
    cout << ("\033[1;94m") << "\t\t****** Login As:\n";
    cout << ("\033[1;96m") << "\t\t\t\t1\t -> \tAdminstrator\n";
    cout << "\t\t\t\t2\t -> \tStaff Member\n";
    cout << "\t\t\t\t3\t -> \tStudent\n";
    cout << "\t\t\t\t4\t <- \tGo Back\n\n";
    cout << ("\033[1;94m") << "\t\t\t    ==> ";
}

void System::signUpAs()
{
    clearConsole;
    /* The below code is a C++ code that is used to display the sign up menu. */
    cout << ("\033[1;93m") << "\n\n\t\tHome And Away Institute of Learning 📝\n";
    cout << ("\033[1;94m") << "\t\t****** Sign Up As:\n";
    cout << ("\033[1;96m") << "\t\t\t\t1\t -> \tStaff Member\n";
    cout << "\t\t\t\t2\t -> \tStudent\n";
    cout << "\t\t\t\t3\t <- \tGo Back\n\n";
    cout << ("\033[1;94m") << "\t\t\t    ==> ";
}

void System::staffLoginScreen()
{
    /* The below code is a menu for the user to choose from. */
    cout << ("\033[1;93m") << "\n\t\t\t˜ı˜ı˜ı˜ı                                           ı˜ı˜ı˜ı¯";
    cout << ("\033[1;95m") << "\n\t\t\t––––––––– THE HOME AND AWAY INSTITUTE OF LEARNING ––––––––";
    cout << ("\033[1;96m") << ("\033[1;93m") << "\n\t\t\t˘°˘°˘°˘°                                           ˘°˘°˘°˘°";
    cout << "\n\t\t\t\t      R\t\t  REGISTER STUDENT\n";
    cout << "\t\t\t\t      P\t\t  PROGRAM ADMINISTRATION\n";
    cout << ("\033[1;91m") << "\n\t\t\t              X.          LOG OUT.\n";
    cout << ("\033[1;94m") << "\n\t\t\t\t====> " << ("\033[0m\033[1;92m");
}

void System::studentLoginScreen()
{
    /* The below code is a menu for the student to choose from. */
    cout << ("\033[1;93m") << "\n\t\t\t˜ı˜ı˜ı˜ı                                          ı˜ı˜ı˜ı¯";
    cout << ("\033[1;95m") << "\n\t\t\t––––––––– THE HOME AND AWAY INSTITUTE OF LEARNING ––––––––";
    cout << ("\033[1;93m") << "\n\t\t\t˘°˘°˘°˘°                                          ˘°˘°˘°˘°";
    cout << "\n\t\t\t              E.          ENROLL FOR SEMESTER";
    cout << "\n\t\t\t              P.          PROGRESS REPORT";
    cout << "\n\t\t\t              M.          MY INFORMATION";
    cout << ("\033[1;91m") << "\n\t\t\t              X.          LOG OUT.\n";
    cout << ("\033[1;94m") << "\n\t\t\t\t====> " << ("\033[0m\033[1;92m");
}

void System::programAdminScreen()
{
    clearConsole;
    /* Printing the menu for the user to choose from. */
    cout << ("\033[1;93m") << "\n\t\t\t˜ı˜ı˜ı˜ı                                           ı˜ı˜ı˜ı¯";
    cout << ("\033[1;95m") << "\n\t\t\t–––––––––––– PROGRAMMES ADMINISTRATION SECTIONS –––––––––––";
    cout << ("\033[1;96m") << ("\033[1;93m") << "\n\t\t\t˘°˘°˘°˘°                                           ˘°˘°˘°˘°";
    cout << "\n\t\t\t              C           CREATE PROGRAME                  ";
    cout << "\n\t\t\t              M           MODIFY PROGRAME DETAILS                 ";
    cout << "\n\t\t\t              G           GENERATE STUDENT LIST              \n";
    cout << ("\033[1;91m") << "\n\t\t\t              X           GO BACK.\n";
    cout << ("\033[1;94m") << "\n\t\t\t\t====> " << ("\033[0m\033[1;92m");
}

void System::enrollmentScreen()
{
    clearConsole;
    /* The below code is a menu for the user to choose from. */
    cout << ("\033[1;93m") << "\n\t\t\t˜ı˜ı˜ı˜ı                                          ı˜ı˜ı˜ı¯";
    cout << ("\033[1;95m") << "\n\t\t\t    ––––––––––––––– ENROLLMENT SECTION –––––––––––––––";
    cout << ("\033[1;93m") << "\n\t\t\t˘°˘°˘°˘°                                          ˘°˘°˘°˘°";
    cout << "\n\t\t\t              v.          VIEW PROGRAMME DETAILS";
    cout << "\n\t\t\t              A.          ADD COURSE";
    cout << "\n\t\t\t              G.          GENERATE FEE BREAKDOWN \n\t\t\t\t\t\t  FOR SEMESTER\n";
    cout << ("\033[1;91m") << "\n\t\t\t              X.          GO BACK.\n";
    cout << ("\033[1;94m") << "\n\t\t\t\t====> " << ("\033[0m\033[1;92m");
}

void System::addData(string userName)
{
    /* Setting the user's first name, last name, address, date started, contact number, and isRegistered
    to true. */
    this->user.firstName = getFirstName("");
    this->user.lastName = getLastName("");
    this->user.address = getAddress("");
    this->user.dateStarted = getDateStarted("");
    this->user.contactNumber = getContactNumber("");
    this->user.isRegistered = true;
}

void System::userData(User user, bool stud, bool staff, int i)
{
    string certificateType;
    if (stud)
    {
        /* The above code is checking the value of the programType variable and assigning the
        appropriate value to the certificateType variable. */
        if (user.programType == "1")
            certificateType = "Certificate Programme";
        if (user.programType == "2")
            certificateType = "Diploma Programme";
        if (user.programType == "3")
            certificateType = "Associate Degree Programme";
    }
    clearConsole;
    /* Printing the title of the program. */
    cout << "\033[1;96m\t\t┌────────────────────────────────────────────────────────────────────┐\n";
    cout << "\033[0;95m\t\t|" << right << setw(33) << "INFORMATION" << right << setw(37) << "|\n";
    cout << "\033[1;96m\t\t└────────────────────────────────────────────────────────────────────┘\n";
    /* Printing the top of the table. */
    cout << "\033[3;96m\t\t┌─────────────────────────┬──────────────────────────────────────────┐\n";
    /* The above code is printing the first name of the user. */
    cout << "\033[4;95m\t\t│" << left << setw(25) << "  First Name" << right << setw(5) << "│  " << left << setw(40) << user.firstName << "│\n";
    /* Printing the last name of the user. */
    cout << "\t\t│" << left << setw(25) << "  Last Name" << right << setw(5) << "│  " << left << setw(40) << user.lastName << "│\n";
    /* The above code is printing the user name. */
    cout << "\t\t│" << left << setw(25) << "  User Name " << right << setw(5) << "│  " << left << setw(40) << user.userName << "│\n";
    cout << "\t\t│" << left << setw(25) << "  Identifcation Number" << right << setw(5) << "│  " << left << setw(40) << user.idNumber << "│\n";
    /* The above code is printing the address of the user. */
    cout << "\t\t│" << left << setw(25) << "  Address" << right << setw(5) << "│  " << left << setw(40) << user.address << "│\n";
    /* The above code is printing the contact number of the user. */
    cout << "\t\t│" << left << setw(25) << "  Cell Number" << right << setw(5) << "│  " << left << setw(40) << user.contactNumber << "│\n";
    /* The above code is printing the date the user started the program. */
    cout << "\t\t│" << left << setw(25) << "  Date Started" << right << setw(5) << "│  " << left << setw(40) << user.dateStarted << "│\n";
    if (stud)
    {
        /* The above code is printing the enrolment status of the user. */
        cout << "\t\t│" << left << setw(25) << "  Enrolment Status" << right << setw(5) << "│  " << left << setw(40) << user.enrolmentStatus << "│\n";
        /* Printing the selected program of the user. */
        cout << "\t\t│" << left << setw(25) << "  Programme" << right << setw(5) << "│  " << left << setw(40) << user.selectedProgram << "│\n";
        /* The above code is printing the certificate type. */
        cout << "\t\t│" << left << setw(25) << "  Programme Type" << right << setw(5) << "│  " << left << setw(40) << certificateType << "│\n";
    }
    cout << "\033[0m\033[1;96m\t\t└─────────────────────────┴──────────────────────────────────────────┘\n";
}

void System::readInUserData(string filename, int id, int index)
{
    ifstream file;
    file.open(filename, ios::in | ios::binary);
    /* Moving the file pointer to the beginning of the record that we want to read. */
    file.seekg((id - 1) * sizeof(User));
    /* Reading the user data from the file. */
    file.read(reinterpret_cast<char *>(&this->user), sizeof(user));
    file.close();
}

void System::saveInUserData(string filename, int index)
{
    ofstream file;
    /* The above code is opening the file in binary mode and appending to the file. */
    file.open(filename, ios::app | ios::binary);
    /* Writing the user struct to the file. */
    file.write(reinterpret_cast<char *>(&this->user), sizeof(this->user));
    file.close();
}

void System::signUp(string filename, int (*function)(), int index)
{

    /* Getting the user name from the file name. */
    this->user.userName = getUserName("", filename, false, index);
    /* Creating an object of the class Administrator. */
    System::Administrator admin;
    if (!admin.checkForUserName(this->user.userName, filename))
    {
        /* The above code is a function that is called when the user enters a wrong username. */
        cout << "\033[1;93m\n\t\tThat user name you entered is not register in the system!\n";
        cout << "\t\tContact Administrator for your user name!!\n";
        continueOn(), function();
    }
    /* Adding the userName to the data array. */
    addData(user.userName);
    /* Setting the password of the user to the password that is passed in. */
    this->user.password = setPassword(user.password);
}

bool System::loginSystem(string filename, string *currUser, int index)
{
    /* Getting the username from the file. */
    string userN, pass;
    ifstream file(filename, ios::in | ios::binary);
    userN = getUserName("", filename, false, index);
    while (file)
    {
        file.read(reinterpret_cast<char *>(&user), sizeof(User));
        if (userN == this->user.userName)
        {
            /* The above code is asking the user to enter their password. */
            cout << ("\t\t\033[1;94m") << "Enter your 'PASSWORD': ";
            cin >> pass;
            if (pass == this->user.password)
            {
                clearConsole;
                /* Checking if the user is logged in or not. */
                cout << "\033[1;92m\n\tLogin Successfully!!\n";
                cout << "\033[3;96m\n\t\tWelcome " << this->user.firstName << "\n";
                *currUser = this->user.firstName + " " + this->user.lastName;
                file.close();
                return true;
            }
            /* Printing the text in red color. */
            cout << ("\033[0;91m") << "\n\t\tIncorrect Password!!\n";
        }
    }
    /* Checking if the username exists in the system. */
    cout << "\033[3;96m\n\n\t\tYour User name does not exist in our System!!\n";
    file.close(), continueOn();
    return false;
}

bool System::checkIfUserNameExist(string userName, string filename, int index)
{
    ifstream file;
    try
    {
        /* The above code is opening the file in binary mode. */
        file.open(filename, ios::in | ios::binary);
        if (file.fail())
            throw false;
        else
            while (file)
            {
                /* Reading the userName from the file and comparing it to the userName that was passed
                in. */

                file.read(reinterpret_cast<char *>(&this->user), sizeof(user));
                if (user.userName == userName)
                {
                    file.close();
                    return true;
                }
            }
    }
    catch (bool error)
    {
        return false;
    }
    /*  */
    file.close();
    return false;
}

void System::continueOn()
{
    /* Printing the text in blue color. */
    cout << "\033[1;96m\n\n\t\tPress ENTER to continue: ", fflush(stdin);
    char c = getchar();
    clearConsole;
}

bool System::Administrator::isAccountsCreated()
{
    ifstream file;
    try
    {
        /* The above code is opening a file in binary mode. */
        file.open("TemporaryFile.bin", ios::in | ios::binary);
        if (file.fail())
            throw false;
    }
    catch (bool error)
    {
        /* The above code is a function that returns an error message if the user tries to access the
        staff account. */
        cout << ("\033[0;33m") << "\n\n\t\tSTAFF ACCOUNTS ARE NOT YET CREATED!!\n\n";
        return error;
    }
    file.close();
    return true;
}

bool System::Administrator::isAdminSetup()
{
    /* Opening the file. */
    clearConsole;
    ifstream file;
    try
    {
        /* The above code is opening a file in binary mode. */
        file.open("AdminFile.bin", ios::in | ios::binary);
        if (file.fail())
            throw false;
    }
    catch (bool error)
    {
        /* The above code is a simple error message that is displayed when the admin account is not yet
        configured. */
        cout << "\033[0;33m\t\tADMIN ACCOUNT IS NOT YET CONFIGURED!!\n\n";
        return error;
    }
    file.close();
    return true;
}

void System::Administrator::setAdminAccount(System sys, int index)
{
    string pass;
    /* The above code is creating an admin account. */
    this->admin.firstName = sys.getFirstName("");
    this->admin.lastName = sys.getLastName("");
    this->admin.userName = sys.getUserName("", "AdminFile.bin", true, index);
    this->admin.password = sys.setPassword("");
    cout << "\n\t\t" << ("\033[0;92m") << "Administrator Account Created Successfully!\n\n";
    ofstream file("AdminFile.bin", ios::out | ios::binary);
    file.write(reinterpret_cast<char *>(&this->admin), sizeof(Admin));
    file.close(), sys.continueOn();
}

void System::Administrator::createStaffAccounts(System sys, int index)
{
    /* The above code is creating a file called TemporaryFile.bin and is opening it in append mode. */
    int amount;
    ofstream file;
    cout << ("\033[1;94m") << "How many staff accounts you wish to create: ", fflush(stdin);
    cin >> amount;
    file.open("TemporaryFile.bin", ios::app | ios::binary);
    clearConsole;
    if (!(amount > 6))
        for (int i = 1; i <= amount; i++)
        {
            /* The above code is creating an account for the staff member. */
            cout << "\n\n\t\t" << ("\033[1;93m") << "Creating an";
            cout << " account for the " << sys.pos[i - 1] << " staff member!!\n\n";
            this->admin.userName = sys.getUserName("", "TemporaryFile.bin", false, index);
            this->admin.faculty = sys.getFaculty("");
            this->admin.faculty = sys.getDepartment("");
            this->admin.isStaffCreated = true;
            file.write(reinterpret_cast<char *>(&this->admin), sizeof(Admin));
            cout << "\n\t" << ("\033[1;92m") << this->admin.userName << "'s account Created!!\n\n";
        }
    else
    {
        clearConsole;
        /* The above code is checking if the number of staff accounts created is greater than 6. If it
        is, it will display an error message and call the createStaffAccounts function again. */
        cout << ("\033[1;91m") << "Can only create 1 to 6 staff accounts at a time!!\n\n";
        createStaffAccounts(sys, index);
    }
    cout << ("\033[1;92m") << amount << " Staff acounts created sucessfully!!\n\n";
    file.close();
}

bool System::Administrator::checkForUserName(string userName, string filename)
{
    ifstream file;
    /* The above code is opening a file called TemporaryFile.bin in binary mode. */
    file.open("TemporaryFile.bin", ios::in | ios::binary);
    while (file)
    {
        /* The above code is reading the file and checking if the username is the same as the one that
        is being passed in. */
        file.read(reinterpret_cast<char *>(&this->admin), sizeof(Admin));
        if (this->admin.userName == userName)
        {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

bool System::Administrator::loginAdmin(System *sys, string filename, int trials, int index)
{
    /* Checking if the user has tried to login 3 times. If so, it clears the console and returns false. */
    if (trials == 3)
    {
        clearConsole;
        return false;
    }
    string name, password;
    /* Opening a file in binary mode. */
    ifstream file(filename, ios::in | ios::binary);
    /* Getting the user name from the system. */
    name = sys->getUserName("", filename, false, index);
    /* Reading the data from the file and storing it in the admin object. */
    file.seekg(0);
    file.read(reinterpret_cast<char *>(&admin), sizeof(Admin));
    /* Checking if the user name is the same as the admin user name. If it is, it sets the trials to 0. */
    if (name == this->admin.userName)
    {
        trials = 0;
    pass:
        /* The above code is asking the user to enter their password. */
        cout << "\n\t\t\033[1;95mEnter Your PassWord: ", fflush(stdin);
        cin >> password;
        if (password == this->admin.password)
        {
            /* The above code is checking if the username and password entered by the user is the same
            as the one in the database. */
            clearConsole;
            cout << "\n\tWelcome " << this->admin.firstName << " " << this->admin.lastName << "\n";
            return true;
        }
        if (trials == 3)
            return false;
        else
        {
            /* The above code is a goto statement. It is used to transfer control to a specific
            statement. */
            ++trials, clearConsole;
            cout << "\n\t\tThe Password You Entered didn't match!!\n";
            goto pass;
        }
    }
    else
    {
        /* The above code is a recursive function that is called when the user enters a wrong username. */
        clearConsole;
        cout << "\n\t\t\033[1;91mThe User name you entered could not be found\n";
        return loginAdmin(sys, filename, trials + 1, index);
    }
}

bool System::Administrator::resetProgCourseDataBase()
{
    /* Asking the user to confirm the database reset. */
    char option;
    cout << "\n\t\t\033[1;95mConfirm DATABASE RESET (Y\\N): ", fflush(stdin);
    cin >> option;
    /* Converting the input to uppercase. */
    option = toupper(option);
    if (option == 'Y')
    {
        /* The below code is resetting the database. */
        Courses course;
        ProgramRecord program;
        clearConsole, cout << "\n\n\t\t\tResetting DATABASE....\n";
        sleep(2), clearConsole;
        course.coursesAndDetials(), program.programAndDetails();
        cout << "\n\t\t\t\033[3;96mDATABASE RESET COMPLETE\n\n";
        return true;
    }
    /* Checking if the user wants to continue the program. */
    else if (option == 'N')
        return false;

    clearConsole;
    /* A function that is called when the user enters an invalid option. */
    cout << "\t\t\033[1;91m" << option << " isn't a valid option\n";
    return resetProgCourseDataBase();
}

void System::Administrator::adminLoginScreen()
{
    clearConsole;
    /* The above code is a C++ code that is used to display the system administrator menu. */
    cout << "\033[3;92m\n\t\t\t\tSYSTEM ADMINISTRATOR *************\n\n";
    cout << "\033[1;95m\t\t\t\t   C\t  CREATE STAFF ACCOUNTS\n";
    cout << "\t\t\t\t   R\t  RESET COURSES AND PROGRAMS DATABASE\n\n";
    cout << "\033[1;91m\t\t\t\t   X\t  LOGOUT\n\n\t\t\t\033[1;94m      ===> ";
}