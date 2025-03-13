#include<bits/stdc++.h>
using namespace std;

// Data
struct Student;
struct Grade;
struct Subject;
ifstream studentFileR("StudentsList.txt");
//ofstream studentFileW("StudentsList.txt");
ifstream subjectFileR("SubjectsList.txt");
//ofstream subjectFileW("SubjectsList.txt");

// Function
void Init();
void addNode();
void getGrade();
void saveAndQuit();

int main() {
    Init();
    return 0;
}

struct Grade {
    Grade *next;
    int IDST;
    string fullName;
    double grades[8]; // This array indicate for
    // lab1, lab2, progressTest1 , progressTest1, finalTest;
    // averageTen, averageFour;
    // If this student does not have this component grade yet, it will set -1 by default 
    Grade(): next(NULL), IDST(0), fullName("") {}; // Default constructor
    void calAaverage();
    void transformToAlphabet();
};

struct Subject {
    Subject *next;
    int IDS; 
    string name;
    Subject(): next(NULL), IDS(0), name("") {}; // Default constructor
    Grade *parentGradeNode = new Grade(); // Linked list of grade of each student
    void sortGrade();
    void showGradeList();
};
Subject *subjectList = new Subject();

struct Student {
    Student *next;
    int IDST;
    Subject *parentSubjectNode = subjectList; // Linked list of subject, it refers to global Linked list of Subject
    string fullName;
    Student(): next(NULL), IDST(0), fullName("") {}; // Default constructor 
    void modifyGrade();
    void showGrade();
};
Student *studentsList = new Student();

void addNode(auto *element, auto *parentNode) {
    auto *temp = parentNode;
    while(temp->next != NULL) temp = temp->next;
    temp->next = element;
}

void Init() {
    string line, temp, name;
    int len;
    // Get student data from 
    if(studentFileR) { // Existing this file
        while(getline(studentFileR, line)) {
            Student *st = new Student();        
            temp = "", name = "";
            len = line.size();
            for(int i=0;i<len;i++) {
                if(line[i] == ';') {
                    name = temp;
                    temp = "";
                } else temp = temp + line[i];
            }
            st->fullName = name;
            st->IDST = stoi(temp);
            addNode(st, studentsList);
        }
    } else {    
        cout << "Cannot access to StudentsList!";
        exit(0);
    }
    // Get subject data from file
    if(subjectFileR) { // Existing this file
        while(getline(subjectFileR, line)) {
            Subject *su = new Subject();
            temp = "", name = "";
            len = line.size();
            for(int i=0;i<len;i++) {
                if(line[i] == ';') {
                    name = temp;
                    temp = "";
                } else temp = temp + line[i];
            }
            su->name = name; name = name + ".txt";
            su->IDS = stoi(temp);
            // Reading everysingle line data of this subject
            ifstream gradesList(name);
            if(gradesList) {
                string temp1, line1;
                int len1, count = 1;
                while(getline(gradesList, line1)) {
                    temp1 = "";
                    cout << line1 << '\n';
                    Grade *gr = new Grade();
                    len1 = line1.size();
                    for(int j=0;j<len1;j++) {
                        if(line1[j] == ';') {
                            if(count == 1) {
                                gr->fullName = temp1;
                                temp1 = "";
                                count++;
                            } else if(count == 2) {
                                gr->IDST = stoi(temp1);
                                temp1 = "";
                                count++;
                            } else {
                                gr->grades[count-2] = stod(temp1);
                                temp1 = "";
                                count++;
                            }
                        } else temp1 = temp1 + line1[j];
                    } 
                    addNode(gr, su->parentGradeNode);
                }
            } else {
                cout << "Cannot access to file list grade: " << name;
                exit(0);
            }
            addNode(su, subjectList); // Adding this subject to linked list   
        }
    } else {
        cout << "Cannot access to SubjectsList!";
        exit(0);
    }
}