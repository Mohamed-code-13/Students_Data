/*
    This is an application which can make you add a new student
    ,search for a student and change the marks of the subjects
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// here will be structures

// this structure for subjects
typedef struct Subject
{
    char *name;
    int mark;

}Subject;

// this structure for students and all information about students
typedef struct Student
{
    char *name;  // student's name
    int age;  //  student's age
    int id_number;  // student's id
    char section;  // student's section
    Subject subjects[4];  // to make every student has 4 subjects

}Student;

// here will be all global variables
int studentCounter = 0;
Student *students;

int newAge, id_number;
char section;

// this function will print options for user
int menu()
{
    int choice;  // will contain user's choice

    printf("\n-----------------------\n");

    printf("Choose one form these four options:- \n");
    printf("1. To add new student \n");
    printf("2. To find a student \n");
    printf("3. To change subject's marks for student \n");
    printf("-1. TO EXIT \n");

    scanf("%d", &choice);  // to know what is user's choice

    return choice;
}

// this function make user enter a new student
char *studentFromUser()
{
    char *newName = (char *)malloc(60);

    printf("Enter new student's name (ONLY LETTERS):- ");
    scanf("%s", newName);

    printf("Enter new student's age (ONLY NUMBERS):- ");
    scanf("%d", &newAge);

    printf("Enter new student's id_number (ONLY NUMBERS) :- ");
    scanf("%d", &id_number);

    printf("Enter new student's section (ONLY ONE LETTER) :- ");
    scanf(" %c", &section);

    return newName;
}

// this function create a new student and return it
Student createStudent(char *newstudent, int age, int id_number, char section)
{
    Student student;

    // add student information
    student.name = newstudent;
    student.age = age;
    student.id_number = id_number;
    student.section = section;

    addSubject(&student);  // to add subjects to the student

    return student;
}

// this function add subjects to the student
void addSubject(Student *student)
{
    Subject english, math, physics, chemistry;

    // adding the names of the subjects and first mark for each subject
    english.name = "English";
    english.mark = 0;

    math.name = "Math";
    math.mark = 0;

    physics.name = "Physics";
    physics.mark = 0;

    chemistry.name = "Chemistry";
    chemistry.mark = 0;

    // adding each subject to the student's subjects
    student->subjects[0] = english;
    student->subjects[1] = math;
    student->subjects[2] = physics;
    student->subjects[3] = chemistry;
}

// this function print all details about the student
void studentDetails(Student student)
{
    // print the normal information
    printf("\n-----------------------\n\n");
    printf("Information about student:- \n");

    printf("1. Name of student: %s\n", student.name);
    printf("2. Age of student: %d\n", student.age);
    printf("1. Id_Number of student: %d\n", student.id_number);
    printf("2. Section of student: %c\n", student.section);

    // print subjects and marks
    printf("The marks for this student:- \n");

    for (int i = 0; i < 4; i++)
    {
        printf("%d. %s: %d\n", i + 1, student.subjects[i].name, student.subjects[i].mark);
    }

}

// here will be adding all students in one place to make it easy to get any of the student
void addStudent(Student student)
{
    studentCounter++;
    students = (Student *)realloc(students, sizeof(student) * studentCounter);
    students[studentCounter - 1] = student;
}

// to know if the student has been signed before or not
// if the student is already signed we will know where is his number to can print his information
int findStudent(char *st)
{
    for (int i = 0; i < studentCounter; i++)
    {
        if (strcmp(st, students[i].name) == 0)
        {
            printf("We could find this student: %s", st);
            studentDetails(students[i]);

            return i;
        }
    }
    printf("There isn't a student has this name: %s", st);

    return -1;
}

// this function edit the marks from user
void editMark(int stdNum, int choice, int mark)
{
    students[stdNum].subjects[choice].mark = mark;
}

// this is the case one
// if the user choose to create a new student this code will be run
void case1()
{
    // call this function
    char *newstudent = studentFromUser();  // store the new student name into this variable

    Student student = createStudent(newstudent, newAge, id_number, section);
    studentDetails(student);
    addStudent(student);
}

// this is the case two
// if the user choose to find a student this code will run
int case2()
{
    char *st = (char *)malloc(60);

    printf("Enter the name of the student you want:- ");
    scanf("%s", st);

    int studentNumber = findStudent(st);
    free(st);

    return studentNumber;
}

// this is the case three
// if the user choose to change the marks this code will run
void case3()
{
    int studentNumber = case2();  // to know where is this student

    if (studentNumber == -1)  // this code will stop if user choose -1
    {
        return;
    }

    int choice;  // to know what subject the user want to change

    do
    {
        printf("\n----------------------\n\n");
        printf("Enter the number of subject to change and -1 to back :- \n");
        printf("1. English\n");
        printf("2. Math\n");
        printf("3. Physics\n");
        printf("4. Chemistry\n");

        scanf("%d", &choice);

        if (choice >= 1 && choice <= 4)  // to check that the user enter number between 1 and 4
        {
            int mark;

            printf("Enter the new mark:- ");
            scanf("%d", &mark);

            editMark(studentNumber, choice - 1, mark);  // change the mark to a new one
        }

        else if (choice == -1)  // this code will stop if user choose -1
        {
            return;
        }

        else
        {
            printf("INVALID INPUT -1 TO BACK !!!");
        }

    } while (choice != -1);
}

// the main function which contain all function we will use
int main()
{
    printf("Welcome to students details application \n");

    while (1)
    {
        int choice = menu();  // to print menu and store the choice into

        switch (choice)  // to check what is the choice
        {
        case 1:  // if the choice is equal 1
            case1();  // call the function to do what happen if the choice is 1
            break;

        case 2:  // if the choice is equal 2
            case2();  // call the function to do what happen if the choice is 2
            break;

        case 3:  // if the choice is equal 3
            case3();  // call the function to do what happen if the choice is 3
            break;

        case -1:  // if the choice is equal -1
            exit(1);  // to end the program
            break;

        default:  // else print invalid input
            printf("INVALID INPUT -1 TO EXIT !!!");
            break;

        }

    }

    return 0;
}
