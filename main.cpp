#include<bits/stdc++.h>
using namespace std;

// Define, macro
#define averageTen grades[5]
#define finalGradeFour grades[6]

// Data
struct Grade {
    Grade *next;
    int IDST;
    string fullName;
    string averageAlphabet; 
    double grades[7]; // This array indicate for lab1, lab2, progressTest1 ,
    // progressTest2, finalTest,
    // averageTen, averageFour;
    // If this student does not have this component grade yet, it will set -1 by default 
    Grade(): next(nullptr), IDST(0), averageAlphabet(""), fullName("") {}; // Default constructor
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
    string name;
    Subject(): next(nullptr), IDS(0), name("") {}; // Default constructor
    Grade *parentGradeNode = new Grade(); // Linked list of grade of each student
    void sortGrade() { // Bubble sort
        Grade *temp1 = parentGradeNode->next;
        while(temp1 != nullptr) {
            Grade *temp2 = parentGradeNode->next;
            while(temp2 != temp1) {
                if(temp2->averageTen > temp1->averageTen) {
                    // Exchanging data with each other
                    swap(temp1->IDST, temp2->IDST);
                    swap(temp1->fullName, temp2->fullName);
                    swap(temp1->averageAlphabet, temp2->averageAlphabet);
                    swap(temp1->grades, temp2->grades);
                } 
                temp2 = temp2->next;
            }
            temp1 = temp1->next;
        }
    };
    void showGradeList() {
        int count = 0;
        Grade *student = parentGradeNode->next;
        while(student != NULL) {
            count++;
            if(count == 1) cout << name << '\n';
            cout << student->IDST << ' ' << student->fullName << ' ';
            for(int i=0;i<7;i++) cout << student->grades[i] << ' ';
            cout << '\n';
            student = student->next;
        }
    };
};
Subject *subjectList = new Subject();
int currentSubjectCounter = 0;

struct Student {
    Student *next;
    int IDST;
    Subject *parentSubjectNode = subjectList; // Linked list of subject, it refers to global Linked list of Subject
    string fullName;
    Student(): next(nullptr), IDST(0), fullName("") {}; // Default constructor 
    void modifyGrade(int idOfSubject, int idOfGrade, double value) {
        Subject *currentSubject = parentSubjectNode->next;
        while(currentSubject->IDS != idOfSubject) currentSubject = currentSubject->next;
        Grade *currentGrade = currentSubject->parentGradeNode->next;
        while(currentGrade->IDST != IDST) currentGrade = currentGrade->next;
        currentGrade->grades[idOfGrade] = value;
    }
    void showGrade() {
        int count = 0;
        Subject *currentSubject = parentSubjectNode->next;
        while(currentSubject != nullptr) {
            Grade *currentStudent = currentSubject->parentGradeNode->next;
            while(currentStudent != nullptr) {
                if(currentStudent->IDST == IDST) {
                    count++;
                    if(count == 1) cout << IDST << ' ' << fullName << '\n';
                    cout << currentSubject->name << ": ";
                    for(int i=0;i<7;i++) cout << currentStudent->grades[i] << ' ';
                    cout << '\n';
                    break;
                }
                currentStudent = currentStudent->next;
            }
            currentSubject = currentSubject->next;
        } 
        if(count == 0) cout << "This student does not join any class!";
    }
};
Student *studentsList = new Student();

fstream studentFile("StudentsList.txt");
fstream subjectFile("SubjectsList.txt");

// Function
void Init();
void addSubject();
void addStudent();
void addGrade();
void addNode();
void saveAndQuit();

int main() {
    Init();
    return 0;
}

// Add element to a linked list
void addNode(auto *element, auto *parentNode) {
    auto *temp = parentNode;
    while(temp->next != nullptr) temp = temp->next;
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
                int len1, count;
                while(getline(gradesList, line1)) {
                    temp1 = "", count = 1;
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
                                gr->grades[count-3] = stod(temp1);
                                temp1 = "";
                                count++;
                            }
                        } else temp1 = temp1 + line1[j];
                    }
                    gr->grades[6] = stod(temp1);
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

// Add subject
void addSubject() {
    string name;
    cout << "Enter your subject name: "; cin >> name;
    // Add subject to linked list
    Subject *element = new Subject();
    element->name = name;
    element->IDS = currentSubjectCounter + 1;
    currentSubjectCounter++;
    addNode(element, subjectList->next);
    // Writing subject to file
}

// Add student
void addStudent() {
    string fullName;
    int IDST;
    cout << "Enter your ID student: "; cin >> IDST;
    Student *temp = studentsList;
    while(temp->next != NULL) {
        if(temp->next->IDST == IDST) {
            cout << "This student has been added!";
            return;
        }
        temp = temp->next;
    }
    cout << "Enter your student's name: "; cin >> fullName;
    Student *element = new Student();
    element->fullName = fullName;
    element->IDST = IDST;
    temp->next = element;
}

// Add grade

// Quit program
void saveAndQuit() {
    studentFile.close();
    subjectFile.close();
    exit(0);
}