#include "Student.h"

Student::Student() {}

Student::~Student() {}

void Student::selectProgram(str2dVec prog[])
{
    char option;
    /* Changing the color of the text. */
    cout << "\033[1;95m\n\n\t\t\tPROGRAMME TYPES \033[1;92m ******\n\n";
    cout << "\033[3;93m\t\t\t\t1.  Certificate Programme\n";
    cout << "\t\t\t\t2.  Diploma Programme\n";
    cout << "\t\t\t\t3.  Associates Programme\033[0m\n\n";
    cout << "\033[1;94m\t\t\t======> ";
    cin >> option;
    /* Checking if the user input is between 1 and 3. If it is not, it will display an error message
    and call the function again. */
    if (int(option - '0') < 1 || int(option - '0') > 3)
    {
        clearConsole;
        cout << "\n\033[1;91m\t\t" << option << " is not a valid option!!\n";
        selectProgram(prog);
    }
    /* Converting the char option to an integer and then to a string. */
    stud.programType = to_string(int(option - '0'));
programmes:
    /* Changing the color of the text. */
    cout << "\033[1;96m\n\n\t\t\t~`~`~`~`+. LIST OF PROGRAMMES .+`~`~`~`~~\n\n";
    /* Displaying the list of programmes. */
    for (int i = 0; i < prog[0][0].size(); i++)
        cout << "\033[3;92m\t\t\t\t" << i + 1 << "\t->\t" << prog[0][0][i] << "\n";

    /* Changing the color of the text to blue and then displaying the text "Select Programme: " and then
    flushing the input stream and then taking in the user input. */
    cout << "\n\n\t\t\t\033[1;95mSelect Programme: ", fflush(stdin);
    cin >> option;

    /* Checking if the user input is between 1 and 3. If it is not, it will display an error message
    and call the function again. */
    if (int(option - '0') > prog[0][0].size() || int(option - '0') < 1)
    {
        clearConsole;
        cout << "\033[3;91m\n\t\t" << stud.pI << " Is not a valid Programme option\n\n";
        goto programmes;
    }
    /* Assigning the programme code and the selected programme to the student. */
    stud.pI = int(option - '0') - 1;
    stud.programmeCode = prog[0][1][stud.pI];
    stud.selectedProgram = prog[0][0][stud.pI];
}

void Student::selectCourses(str2dVec prog[], str2dVec course[], vector<string> &selected, string currStud, bool state)
{
    /* Declaring a variable called option of type char and then it is declaring a variable called id of
    type int and then it is initializing it to the value returned by the function findUserId. Then it
    is declaring a variable called max of type int and then it is initializing it to 0. Then it is
    calling the function readInStudentData and passing in the parameters "StudentsData.bin" and id. */
    char option;
    int id = findUserId(0, currStud), max = 0;
    readInStudentData("StudentsData.bin", id);

    /* Checking the program type of the student and then assigning the max amount of courses the student
    can take. */
    if (stud.programType == "3")
        max = 8, state = true;
    if (stud.programType == "2")
        max = 6;
    if (stud.programType == "1")
        max = 4;

    cout << "\n\t\tEnter 'Y' if you wish to take the course.\n";
    cout << "\t\tEnter 'N' or any other key to do otherwise.\n";

    for (int i = 0; i < course[0][stud.pI].size(); i++)
    {
        /* Checking if the size of the vector selected is equal to the max amount of courses the
        student can take. If it is, it will break out of the loop. */
        if (selected.size() == max)
            break;

        /* Checking if the state is true and if it is, it is assigning the program type of the student
        to the program type of the course. */
        if (state)
            stud.programType = course[5][stud.pI][i];

        /* Asking the user to select the course. */
        if (course[5][stud.pI][i] == stud.programType)
        {
        select:
            /* Asking the user to select the course. */
            cout << "\n\t\t\tSelect " << course[0][stud.pI][i] << ": ", fflush(stdin);
            cin >> option;
            if (option == 'Y' || option == 'y')
                selected.push_back(course[0][stud.pI][i]);
            else if (option == 'N' || option == 'n')
                continue;
            else
            {
                cout << "\n\033[1;91m\t\t" << option << " is not valid option!!\n";
                goto select;
            }
        }
    }
    if (selected.size() != max)
    {
        selected.clear();
        cout << "\n\t\tThe amount of courses you selected doesn't match for your programme type!!\n";
        cout << "\t\tPlease RE-SELECT courses!!";
        cout << "\n\033[1;96m\t\t\tYOU ARE RECCOMMENDED TO '" << max << "' COURSES ONLY!!\n";
        /* Calling the function selectCourses and passing in the parameters prog, course, selected,
        currStud and false. */
        selectCourses(prog, course, selected, currStud, false);
    }

    /* Saving the selected courses to the student's record. */
    saveSelectedCourses(selected, currStud);
    cout << "\n\t\t\033[1;92mCourses Selected Succesfully!!\n";
    /* Calling the function continueOn() */
    continueOn(), clearConsole;
}

void Student::readInStudentData(string filename, int id)
{
    /* Reading the file and storing the data in the stud object. */
    ifstream file;
    file.open(filename, ios::in | ios::binary);
    file.seekg(id * sizeof(stud));
    file.read(reinterpret_cast<char *>(&this->stud), sizeof(stud));
    file.close();
}

void Student::saveInStudentData(string filename)
{
    /* Writing the data of the student to the file. */
    ofstream file;
    file.open(filename, ios::app | ios::binary);
    file.write(reinterpret_cast<char *>(&this->stud), sizeof(stud));
    file.close();
}

int Student::findUserId(int currentId, string currStud)
{
    /* The above code is opening a file named StudentsData.bin in binary mode. */
    ifstream file("StudentsData.bin", ios::in | ios::binary);
    /* Moving the file pointer to the location of the student record. */
    file.seekg(currentId * sizeof(stud));
    /* Reading the file and checking if the student name is the same as the current student name. */
    file.read(reinterpret_cast<char *>(&this->stud), sizeof(stud));
    if (stud.firstName + " " + stud.lastName == currStud)
        return currentId;
    /* Calling the findUserId function with the currentId + 1 and the current student. */
    return findUserId(currentId + 1, currStud);
}

void Student::generateFeeBreakDown(vector<string> selected, str2dVec course[], string currStud)
{
    if (findSelectedCourses(selected, 0, currStud))
    {
        int i = 0, id = findUserId(0, currStud);
        /* Seeking the position of the student in the file. */
        fstream file("StudentsData.bin", ios::in | ios::out | ios::binary);
        file.seekg(id * sizeof(stud));
        /* Reading the data from the file and storing it in the stud object. */
        file.read(reinterpret_cast<char *>(&stud), sizeof(stud));
        vector<int> costs, creditsAssigned;

        for (int j = 0; j < course[0][stud.pI].size(); j++)
        {
            if (course[0][stud.pI][j] != selected[i])
                continue;
            else if (course[0][stud.pI][j] == selected[i])
            { /* The above code is pushing back the cost of the course and the credits assigned to the
             student. */

                costs.push_back(int(course[2][stud.pI][j][0] - '0') * 25000);
                creditsAssigned.push_back(int(course[2][stud.pI][j][0] - '0'));
                i++;
            }
        }
        int tCredits = 0, tCosts = 0;
        for (int i = 0; i < creditsAssigned.size(); i++)
        {
            /* Adding the credits and costs of each course to the total credits and total costs. */
            tCredits += creditsAssigned[i];
            tCosts += costs[i];
        }
        clearConsole;
        cout << "\033[7;94m\n\t\t" << left << setw(25) << "COURSE NAME" << setw(10) << "CREDITS" << setw(10) << "COST";
        for (int i = 0; i < selected.size(); ++i)
        {
            /* The above code is printing the selected courses, the credits assigned to the courses, and
            the costs of the courses. */
            cout << "\n\033[4;92m\t\t" << left << setw(25) << selected[i] << setw(10) << creditsAssigned[i] << setw(10) << costs[i];
        }
        /* The above code is printing the total credits and costs. */
        cout << "\n\033[3;95m\t\t" << left << setw(25) << "TOTAL" << setw(10) << tCredits << setw(10) << tCosts << "\n";
        cout << "\033[0m";
        stud.enrolmentStatus = true;
        /* Moving the pointer to the position of the student in the file. */
        file.seekp(id * sizeof(stud));
        /* Writing the data of the student to the file. */
        file.write(reinterpret_cast<char *>(&stud), sizeof(stud));
        file.close(), continueOn();
    }
}

void Student::addStudentsData(str2dVec prog[], int (*func)())
{
    /* The below code is setting the values of the student object. */
    this->stud.firstName = getFirstName("");
    this->stud.lastName = getLastName("");
    this->stud.address = getAddress("");
    this->stud.dateStarted = getDateStarted("");
    this->stud.contactNumber = getContactNumber("");
    this->stud.isRegistered = false;
    this->stud.idNumber = "N\\A";
    this->stud.userName = getUserName("", "StudentsData.bin", true, 1);
    this->stud.password = setPassword("");
    /* Saving the student data in a binary file. */
    selectProgram(prog), userData(stud, true, false, 1);
    saveInStudentData("StudentsData.bin");
    cout << "\n\n\033[3;92mSigned up successfully!!\n";
    continueOn(), func();
}

bool Student::findSelectedCourses(vector<string> &c, int s, string currStud) // s represents the seekSize and c represents the selected courses vector
{
    ifstream file;
    try
    {
        /* The above code is opening a file called SelectedCourses.bin in binary mode. */
        file.open("SelectedCourses.bin", ios::in | ios::binary);
        if (file.fail())
            throw false;
    }
    catch (bool error)
    {
        /* Printing a message to the user that no courses have been selected. */
        cout << "\n\t\tNo Courses Selected!!\n";
        return false;
    }
    /* Moving the file pointer to the beginning of the file. */
    file.seekg(s);
    file.read(reinterpret_cast<char *>(&this->studentFullName), 40);
    file.read(reinterpret_cast<char *>(&this->amountCourses), 4);
    if (this->studentFullName == currStud)
    {
        /* Creating a new array of strings with the size of the amount of courses. */
        selectedCourses = new string[this->amountCourses];
        for (int i = 0; i < this->amountCourses; i++)
        { /* Reading the file and storing the data in the vector. */

            file.read(reinterpret_cast<char *>(&selectedCourses[i]), 40);
            c.push_back(selectedCourses[i]);
        }
        /* Deleting the array of pointers to Course objects. */
        delete[] selectedCourses;
        return true;
    }
    if (!file.eof())
    {
        file.close();
        /* Calculating the size of the object. */
        s += 40 + 4 + (this->amountCourses * 40);
        /* Calling the function findSelectedCourses and passing in the parameters c, s, and
        currStud. */
        return findSelectedCourses(c, s, currStud);
    }
    file.close();
    cout << "\t\tNo data Found for " << currStud << "\n\n";
    return false;
}

void Student::saveSelectedCourses(vector<string> selected, string currStud)
{
    this->studentFullName = currStud;
    configureSelectedCoursesList(selected);
    ofstream file("SelectedCourses.bin", ios::app | ios::binary);
    /* Setting the amount of courses to the size of the selected vector. */
    this->amountCourses = selected.size();
    /* Writing the studentFullName to the file. */
    file.write(reinterpret_cast<char *>(&this->studentFullName), 40);
    /* Writing the amount of courses to the file. */
    file.write(reinterpret_cast<char *>(&this->amountCourses), 4);
    /* Writing the selected courses to the file. */
    for (int i = 0; i < this->amountCourses; i++)
        file.write(reinterpret_cast<char *>(&selectedCourses[i]), 40);

    file.close();
    /* Deleting the array of pointers to Course objects. */
    delete[] selectedCourses;
}

void Student::configureSelectedCoursesList(vector<string> selected)
{
    /* Creating a new array of strings called selectedCourses. */
    selectedCourses = new string[selected.size()];
    /* Copying the contents of the vector selected into the array selectedCourses. */
    for (int i = 0; i < selected.size(); i++)
        selectedCourses[i] = selected[i];
}

void Student::viewProgramDetails(str2dVec prog[], str2dVec course[])
{
    while (true)
    {
        char option;
        cout << "\033[1;96m\n\n\t\t\t~`~`~`~`+. LIST OF PROGRAMMES .+`~`~`~`~~\n\n";
        /* Printing the contents of the vector prog[0][0] */
        for (int i = 0; i < prog[0][0].size(); i++)
            cout << "\033[3;92m\t\t\t\t" << i + 1 << "\t->\t" << prog[0][0][i] << "\n";
        /* The above code is a simple menu that allows the user to select a programme to run. */
        cout << "\033[1;94m\n\t\t\t\tEnter 'X' to 'QUIT' at anytime\n";
        cout << "\n\n\t\t\t\033[1;95mSelect Programme: ", fflush(stdin);
        cin >> option;
        /* The above code is a switch statement that allows the user to choose between the different
        options. */
        if (option == 'X' || option == 'x')
            break;
        /* Checking if the option is valid or not. */
        if (int(option - '0') < 1 || int(option - '0') > prog[0][0].size())
        {
            clearConsole;
            cout << "\n\t\t\033[3;91m'" << option << "' is not a valid option!!\n";
            continue;
        }
        clearConsole;
        /* Printing the course name and credit of the course. */
        cout << "\t\t\t\033[4;95m" << left << setw(30) << "COURSE NAME" << setw(7) << "CREDIT\n";
        for (int i = 0; i < course[0][int(option - '0') - 1].size(); i++)
            cout << "\033[0m\n\t\t\t\033[1;96m" << left << setw(30) << course[0][int(option - '0') - 1][i] << setw(10) << course[2][int(option - '0') - 1][i];
        cout << "\033[0m\n";
        continueOn(), clearConsole;
    }
    clearConsole;
}

void Student::generateProgressReport(vector<string> selected, string currStud)
{
    clearConsole;
    /* Checking if the selected courses are in the current student's list of courses. */
    if (findSelectedCourses(selected, 0, currStud))
    {
        /* Printing the courses that the student has enrolled in. */
        cout << "\n\t\t\033[1;95mAll Courses you enrolled in.....\n";
        for (int i = 0; i < selected.size(); i++)
            cout << "\n\t\t\t\033[3;96m" << i + 1 << ".\t " << selected[i];
    }
    continueOn(), clearConsole;
}

void Student::viewMyData(string currentUser)
{
    /* Reading in the user data from the file and then displaying it to the user. */
    int id = findUserId(0, currentUser);
    readInUserData("StudentsData.bin", id, 1);
    userData(stud, true, false, 1);
    continueOn();
}
