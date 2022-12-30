# Home-and-Away


The Home & Away Institute (H&AI) is an Educational Institution that specializes in offering Distance Learning courses. The institution has been in operation for over three (3) years, and has been using a paper based system for the administrative processes such as student admission, and programme administration.
The Chairman of the H&AI has requested that a program be created to automate the student admission and programme administration processes. As the Manager of the Information and Communication Technology (ICT) Department, you are in charge of presenting the prototype system at the next meeting of the Board that is schedule for November 18, 2023.
After completing an analysis of the paper based system, the Chairman provided a set of basic system requirements. The Chairman has also instructed your team to provide additional functionalities to enhance the program.
Basic requirements. The prototype should:
• provide an administrator account for the initial system configuration that allows the administrator to create user accounts for staff members.
• provide staff members with a login screen for accessing the system.
• provide staff with menu options to:
o RegisterStudent,and
o ProgrammeAdministration.
▪ Create Programme.
▪ ModifyProgrammeDetails. ▪ Generate Student List
• provide students with a login screen for accessing the system.
• provide students with menu options to:
    o EnrollforSemester
Page 1 of 5
▪ ViewProgrammeDetails.
▪ Add Course.
▪ GenerateFeeBreakdownforSemester
o GenerateProgressReport.
The analysis of the paper based system also uncovered details related to the various records held in a number of files (i.e. staff, student, course, and programme), some of the information stored, includes:
Staff Record:
• Id Number, Name (First and Last), Faculty, Department and Date employed (day, month, year)
Student Record:
• Id Number, Name (First and Last), Address, Date enrolled, Programme Code, Enrolment Status and Contact number.
Course Record:
• Course Code, Name, Description, Credits and Pre-requisite Programme Record:
• Programme Code, Name, Maximum number of courses, Award and Accreditation
H&AI offers Certificate, Diploma and Associate Degree programmes. Each programme consists of a number of courses:
• Certificate Programmes offer students four specialized courses.
• Diploma Programmes offer student six specialized courses.
• Associate Degree Programmes offer students eight specialized courses
Functionality Requirements when the user selects:
Register Student – the system should accept student’s details and generate a student record. The student id number should be generated using the current year, programme code and a sequence that starts at zero (0), and the enrollment status should be set to zero (0).
Programme Administration:
• Create Programme – the system should accept general programme details.
• Modify Programme Details – the system should allow for the addition, removal, and
editing of courses for the programme.
• Generate Student List – the system should accept a programme code then displays
the list of student currently enrolled in the programme.
Enroll for Semester:
Page 2 of 5

• View Programme Details – the system should display all courses in the programme.
• Add Course – the system should allow the selection of courses from the enrolled
programme.
• Generate Fee Breakdown for Semester – the system should display all courses
enrolled in for the semester and the total cost (i.e. number of credits * cost per credit), it should also switch students enrolled status to one (1).
Generate Progress Report – the system should display all the courses the student has ever enrolled in for the programme.
