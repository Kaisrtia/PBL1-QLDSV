#include<bits/stdc++.h>
using namespace std;

// Data
struct Student;
struct Grade;
struct Subject;
ifstream studentFileR("StudentsList.txt");
ofstream studentFileW("StudentsList.txt");
ifstream subjectFileR("SubjectsList.txt");
ofstream subjectFileW("SubjectsList.txt");

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
    Student(); // Constructor
    void modifyGrade();
    void showGrade();
};
Student *studentList = new Student();

void addNode(auto *element, auto *parentNode) {
    auto *temp = parentNode;
    while(temp->next != NULL) temp = temp->next;
    temp-> next = element;
}

void Init() {
    string line, temp, name;
    int len;
    // Get student data from file
    Student *st = new Student();
    if(studentFileR) { // Existing this file
        while(getline(studentFileR, line)) {
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
            addNode(st, studentList);
        }
    } else {    
        cout << "Cannot access to StudentList!";
        exit(0);
    }
    // Get subject data from file
    Subject *su = new Subject();
    if(subjectFileR) { // Existing this file
        while(getline(subjectFileR, line)) {
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
            string temp1, line1;
            int len1, count = 1;
            while(getline(gradesList, line1)) {
                Grade *gr = new Grade();
                len1 = line1.size();
                for(int j=0;j<len1;j++) {
                    if(line1[j] == ';') {
                        if(count == 1) {
                            gr->IDST = stoi(temp1);
                            temp1 = "";
                            count++;
                        } else if(count == 2) {
                            gr->fullName = temp1;
                            temp1 = "";
                            count = 1;
                        } else {
                            gr->grades[count] = stod(temp1);
                            temp1 = "";
                            count++;
                        }
                    } else temp1 = temp1 + line1[j];
                } 
                addNode(gr, su->parentGradeNode);
            }
        }
        // Adding this subject to linked list
        addNode(su, subjectList);
    } else {
        cout << "Cannot accest to SubjectsList!";
        exit(0);
    }
}