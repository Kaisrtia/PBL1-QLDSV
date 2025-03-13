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
    int IDST;
    string fullName;
    double lab1, lab2, progressTest1 , progressTest1, finalTest;
    double averageTen, averageFour;
    void calAaverage();
    void transformToAlphabet();
};

struct Subject {
    Subject *next;
    int IDS; 
    string name;
    void sortGrade();
    void showGradeList();
};

struct Student {
    Student *next;
    int IDST;
    string fullName;
    void modifyGrade();
    void showGrade();
};
