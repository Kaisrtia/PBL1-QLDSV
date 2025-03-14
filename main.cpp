#include<bits/stdc++.h>
using namespace std;

// Data
struct Student;
struct Grade;
struct Subject;
fstream studentFile("StudentsList.txt");
fstream subjectFile("SubjectsList.txt");

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
    Grade *next, *head;
    int IDST;
    string fullName;
    string averageAlphabet; 
    double grades[8]; // This array indicate for lab1, lab2, progressTest1 ,
    // progressTest1, finalTest,
    // averageTen, averageFour;
    // If this student does not have this component grade yet, it will set -1 by default 
    Grade(): next(NULL), head(NULL), IDST(0), averageAlphabet(""),
    fullName(""), grades({-1,-1,-1,-1,-1,-1,-1,-1}) {}; // Default constructor
    void calAverage() {
        double averageTen, averageFour, sum = 0;
        for(int i=0;i<6;i++) sum += grades[i];
        averageTen = sum / 6;
        if(averageTen >= 8.5) averageFour = 4.0, averageAlphabet = "A";
        else if(averageTen >= 8.0) averageFour = 3.5, averageAlphabet = "B+";
        else if(averageTen >= 7.0) averageFour = 3.0, averageAlphabet = "B";
        else if(averageTen >= 6.5) averageFour = 2.5, averageAlphabet = "C+";
        else if(averageTen >= 5.5) averageFour = 2.0, averageAlphabet = "C";
        else if(averageTen >= 5.0) averageFour = 1.5, averageAlphabet = "D+";
        else if(averageTen >= 4.0) averageFour = 1.0, averageAlphabet = "D";
        else averageFour = 0.0, averageAlphabet = "F";
    }
};

struct Subject {
    Subject *next;
    int IDS; 
    string name; // 1 2 3 4
    Subject(): next(NULL), IDS(0), name("") {}; // Default constructor
    Grade *parentGradeNode = new Grade(); // Linked list of grade of each student
    void sortGrade() { // Bubble sort
        #define finalGradeTen grades[6]
        Grade *temp1 = parentGradeNode->next;
        temp1->head = parentGradeNode;
        while(temp1->next != NULL) {
            Grade *temp2 = parentGradeNode->next;
            while(temp2 != temp1) {
                if(temp2->finalGradeTen > temp1->finalGradeTen) {

                }
            }
        }
    };
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

// Add a element to linked list
void addNode(auto *element, auto *parentNode) {
    auto *temp = parentNode;
    while(temp->next != NULL) temp = temp->next;
    temp->next = element;
}

void Init() {
    string line, temp, name;
    int len;
    // Get student data from 
    if(studentFile) { // Existing this file
        while(getline(studentFile, line)) {
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
    if(subjectFile) { // Existing this file
        while(getline(subjectFile, line)) {
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

// Quit program
void saveAndQuit() {
    studentFile.close();
    subjectFile.close();
    exit(0);
}

// Getting grade
void getGrade() {
    
}