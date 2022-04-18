#include <iostream>
#include <fstream>
using namespace std;

//Global
class Subject;
class Student;
void ShowMainMenu(int stdNumber);
void EnterStudentNumber();
void AddSubject (Subject *subject);
int stdNumber ;
int studentCount;

//Objects
class Subject
{
    public :
    //Data
    int id;
    string Name;
    string Name2;
    int Number;
    int Credit;
    int Capacity;
    //next
    Subject * next;
};
class Student
{
    public :
    // Data
    int id;
    int Number ;
    string Name;
    string Name2;
    int Tuition;
    int SubjectNumber;
    Subject * subjects ;
    // Next
    Student * next;
};

//Pointers
Student *FirstStd ;
Student *LastStd ;
Student *CurrentStd;
Student *CurrentStd2;
Student *Std;

Subject *FirstSub;
Subject *LastSub;
Subject *CurrentSub;
Subject *CurrentSub2;
Subject *Sub;

//Student Services
void AddStudent (Student *student)
{   
    if (FirstStd == NULL)
    {
        FirstStd = LastStd = student;
    }
    else
    {
        LastStd->next = student;
        LastStd = student;
        LastStd->next = NULL;
    }
}

void ShowStudent (int stdNum)
{
    CurrentStd = FirstStd;
    while(CurrentStd->Number != stdNum)
    {
        CurrentStd = CurrentStd->next;
    }
    FirstSub = CurrentStd->subjects;
    CurrentSub = FirstSub;
    for (int i = 1 ; i <= CurrentStd->SubjectNumber ; i++)
    {
        if (i == CurrentStd->SubjectNumber)
        {
            LastSub = CurrentSub;
            break;
        }
        CurrentSub = CurrentSub->next;
    }
    Sub = CurrentSub;
    Std = CurrentStd;
    CurrentSub = NULL;
    CurrentStd = NULL;
    cout << "Name : " << Std->Name << endl;
    cout << "LastName : " << Std->Name2 << endl;
    cout << "Number : " << Std->Number << endl;
    cout << "Tuition : " << Std->Tuition << endl << endl;
    
}

void AddStudentToLinkList()
{
    std::ifstream stdFile("Student.txt");
    stdFile >> studentCount;
    for(int i = 0 ; i<studentCount;i++)
    {        
        Student *student = new Student();
        student->id = i;
        stdFile >> student->Number;
        stdFile >> student->Name >> student->Name2;
        stdFile >> student->Tuition ;
        stdFile >> student->SubjectNumber;
        Subject *first ;
        for (int j = 0 ; j < student->SubjectNumber ; j++)
        {
            student->subjects = new Subject();
            if (j == 0)
            {
                first = student->subjects;
            }
            student->subjects->id = j;
            stdFile >> student->subjects->Name >> student->subjects->Name2;
            stdFile >> student->subjects->Number >> student->subjects->Credit;
            AddSubject(student->subjects);
        }
        AddStudent(student);
        student->subjects = first;
    }
}

//Subject(Lesson) Services
void AddSubject (Subject *subject)
{   
    if (FirstSub == NULL)
    {
        FirstSub = LastSub = subject;
    }
    else
    {
        LastSub->next = subject;
        LastSub = subject;
        LastSub->next = NULL;
    }
}

void DeleteSubject ()
{
    cout << "Please enter the lesson number : ";
    int id;
    cin >> id;
    CurrentSub2 = CurrentSub = FirstSub;
    while(CurrentSub2->next != NULL)
    {
        if (CurrentSub2->next->Number ==id)
        {
            break;
        }
        CurrentSub2 = CurrentSub2->next;
    }
    if (CurrentSub2->next == NULL)
    {
        CurrentSub2 = NULL;
    }
    while(CurrentSub->Number != id)
    {
        CurrentSub = CurrentSub->next;
    }
    int temp = (CurrentSub->Credit)*1000;
    if(CurrentSub == FirstSub)
    {
        FirstSub = FirstSub->next;
        Std->subjects = FirstSub;
        delete CurrentSub;
    }
    else if (CurrentSub == LastSub)
    {
        LastSub = CurrentSub2;
        LastSub->next = NULL;
        delete CurrentSub;
    }
    else
    {
        CurrentSub2->next = CurrentSub->next;
        delete CurrentSub;
    }
    Std->SubjectNumber --; 
    Std->Tuition -= temp;

    ofstream OutstdFile("Student.txt");
    OutstdFile << studentCount << endl;
    CurrentStd = FirstStd;
    for (int i = 0 ;i< studentCount ; i++)
    {
        OutstdFile << CurrentStd->Number << endl;
        OutstdFile << CurrentStd->Name << "\t" <<CurrentStd->Name2 <<endl;
        OutstdFile << CurrentStd->Tuition << endl << CurrentStd->SubjectNumber << endl;
        CurrentSub = CurrentStd->subjects;
        for (int j = 0 ; j < CurrentStd->SubjectNumber ; j++)
        {
            OutstdFile << CurrentSub->Name << "\t" << CurrentSub->Name2 << "\t" <<  CurrentSub->Number << "\t"<< CurrentSub->Credit << endl ;
            CurrentSub = CurrentSub->next;
        }
        CurrentStd = CurrentStd->next;
    }
    CurrentSub = NULL;
    CurrentStd = NULL;
    ShowMainMenu(stdNumber);
}

void ShowLessons()
{
    cout << "Lessons : " << endl;
    CurrentSub = FirstSub;
    while (CurrentSub != LastSub)
    {
        cout << CurrentSub->Name << " " << CurrentSub->Name2 << "\t";
        cout << CurrentSub->Number << "\t" << CurrentSub->Credit ; 
        cout << endl;
        CurrentSub = CurrentSub->next;
    }
    cout << LastSub->Name << " " << LastSub->Name2 << "\t";
    cout << LastSub->Number << "\t" << LastSub->Credit ; 
    cout << endl; 
    CurrentStd = NULL;
    CurrentSub = NULL;
    cout << endl << "Please enter * to main menu : ";
    string enter ; 
    cin >> enter ;
    if (enter == "*")
    {
        ShowMainMenu(stdNumber);
        return;
    }   
}

void AddNewLesson()
{
    Subject *subject = new Subject();
    subject->id = LastSub->id + 1;
    cout << "Enter the subject's name : ";
    cin >> subject->Name >> subject->Name2 ;
    cout << "Enter the subject's credit : ";
    cin >> subject->Credit;
    cout << "Enter the subject's number : ";
    cin >> subject->Number; 
    Subject *temp;
    if(LastSub->next != NULL)
    temp = LastSub->next;
    else
    temp = NULL;
    AddSubject(subject);
    LastSub->next = temp;
    Std->SubjectNumber ++;
    Std->Tuition += (subject->Credit)*1000;
    ofstream OutstdFile("Student.txt");
    OutstdFile << studentCount << endl;
    CurrentStd = FirstStd;
    for (int i = 0 ;i< studentCount ; i++)
    {
        OutstdFile << CurrentStd->Number << endl;
        OutstdFile << CurrentStd->Name << "\t" <<CurrentStd->Name2 <<endl;
        OutstdFile << CurrentStd->Tuition << endl << CurrentStd->SubjectNumber << endl;
        CurrentSub = CurrentStd->subjects;
        for (int j = 0 ; j < CurrentStd->SubjectNumber ; j++)
        {
            OutstdFile << CurrentSub->Name << "\t" << CurrentSub->Name2 << "\t" <<  CurrentSub->Number << "\t"<< CurrentSub->Credit << endl ;
            CurrentSub = CurrentSub->next;
        }
        CurrentStd = CurrentStd->next;
    }
    CurrentSub = NULL;
    CurrentStd = NULL;
    ShowMainMenu(stdNumber);
}

//Main
void ShowMainMenu(int StdNumber)
{
    ShowStudent ( StdNumber);
    cout << "***** Main Menu *****"<<endl;
    cout << "1.Show Lessons " << endl;
    cout << "2.Back " << endl;
    cout << "3.Exit " << endl;
    cout << "4.Delete Lessons " << endl;
    cout << "5.Add New Lesson" << endl ;
    cout << "Please enter your choice : ";
    string enterance;
    cin >> enterance; 
    if (enterance == "1")
    {
        ShowLessons();
        return;
    }
    else if (enterance == "2" )
    {
        EnterStudentNumber();
        return;
    }
    else if (enterance == "3" )
    {
        exit(0);
    }
    else if (enterance == "4")
    {
        DeleteSubject();
        return;
    }
    else if(enterance == "5")
    {
        AddNewLesson();
        return;
    }
}

void EnterStudentNumber()
{
    cout << "Please enter the number of student : ";
    cin >> stdNumber;
    ShowMainMenu(stdNumber);

}

int main()
{
    FirstSub = LastSub  = 0;
    FirstStd = LastStd = 0;
    AddStudentToLinkList();
    EnterStudentNumber();
}