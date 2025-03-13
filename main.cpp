#include<bits/stdc++.h>
using namespace std;

// Data
struct Student;
struct Grade;
struct Subject;

// Function
void Init();
void addStudent();
void addSubject();
void getGrade();

int main() {
    Init();
    return 0;
}

struct Grade {
    Grade *next;
    int IDST;
    string fullName;
    double lab1, lab2, progressTest1 , progressTest1, finalTest;
    double averageTen, averageFour;
    Grade(); // Constructor
    void calAaverage();
    void transformToAlphabet();
};

struct Subject {
    Subject *next;
    int IDS; 
    string name;
    Subject(): next(NULL), IDS(0), name("") {}; // Default constructor
    Subject(); // Constructor
    Grade *parentGradeNode; // Linked list of grade of each student
    void sortGrade();
    void showGradeList();
};
Subject *currentSubject = new Subject();

struct Student {
    Student *next;
    int IDST;
    Subject *parentSubjectNode = currentSubject; // Linked list of subject, it refers to global Linked list of Subject
    string fullName;
    Student(): next(NULL), IDST(0), fullName("") {}; // Default constructor 
    Student(); // Constructor
    void modifyGrade();
    void showGrade();
};
Student *currentStudent = new Student();

void Init() {

}