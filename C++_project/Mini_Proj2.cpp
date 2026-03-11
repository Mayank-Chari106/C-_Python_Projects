#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
using namespace std;

// -------------------------
// CLASS DEFINITION
// -------------------------
class Student {
public:
    int rollNo;
    string name;
    string course;
    float marks;
    double attendance;
    static const int total_days {100};

    Student(int r = 0, string n = "", string c = "", float m = 0.0, double a = 0)
        : rollNo(r), name(n), course(c), marks(m)
    {
        attendance = (a / total_days) * 100;
    }

    void display() const {
        cout << "Roll No: " << rollNo
             << " | Name: " << name
             << " | Course: " << course
             << " | Marks: " << marks
             << " | Attendance: " << attendance << "%" << endl;
    }
};

// ✅ Definition of static member
const int Student::total_days;

// -------------------------
// GLOBAL VARIABLES
// -------------------------
vector<Student> students;

// -------------------------
// FILE HANDLING FUNCTIONS
// -------------------------
void saveToFile() {
    ofstream file("students.txt");
    for (auto &s : students) {
        file << s.rollNo << ","
             << s.name << ","
             << s.course << ","
             << s.marks << ","
             << s.attendance << "\n";
    }
    file.close();
}

void loadFromFile() {
    students.clear();
    ifstream file("students.txt");
    if (!file) return; // no file yet

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string rollStr, name, course, marksStr, attendanceStr;

        getline(ss, rollStr, ',');
        getline(ss, name, ',');
        getline(ss, course, ',');
        getline(ss, marksStr, ',');
        getline(ss, attendanceStr, ',');

        try {
            if (rollStr.empty() || marksStr.empty() || attendanceStr.empty())
                continue;

            int roll = stoi(rollStr);
            float marks = stof(marksStr);
            double attendance = stod(attendanceStr);

            students.push_back(Student(roll, name, course, marks, attendance));
        }
        catch (const invalid_argument&) {
            cerr << "Warning: Skipping invalid line -> " << line << endl;
        }
        catch (const out_of_range&) {
            cerr << "Warning: Out of range values in line -> " << line << endl;
        }
    }
    file.close();

    // ✅ Always sort by roll number after loading
    sort(students.begin(), students.end(), [](const Student &a, const Student &b) {
        return a.rollNo < b.rollNo;
    });
}

// -------------------------
// TEACHER FUNCTIONS
// -------------------------
void addStudent() {
    int roll;
    string name, course;
    float marks;
    double daysPresent;

    cout << "Enter Roll Number: ";
    cin >> roll;
    cin.ignore();
    cout << "Enter Name: ";
    getline(cin, name);
    cout << "Enter Course: ";
    getline(cin, course);
    cout << "Enter Marks (out of 100): ";
    cin >> marks;
    cout << "Enter Days Present (out of 100): ";
    cin >> daysPresent;

    students.push_back(Student(roll, name, course, marks, daysPresent));

    // ✅ Sort every time after addition
    sort(students.begin(), students.end(), [](const Student &a, const Student &b) {
        return a.rollNo < b.rollNo;
    });

    saveToFile();
    cout << "✅ Student added successfully!\n";
}

void viewAllStudents() {
    if (students.empty()) {
        cout << "No students found.\n";
        return;
    }

    cout << "\n----- Student List (Sorted by Roll No) -----\n";
    for (auto &s : students) s.display();
}

// -------------------------
// STUDENT FUNCTIONS
// -------------------------
void viewMyRecord() {
    int roll;
    cout << "Enter your Roll Number: ";
    cin >> roll;

    bool found = false;
    for (auto &s : students) {
        if (s.rollNo == roll) {
            cout << "\n--- Student Record ---\n";
            s.display();
            if (s.marks >= 40 && s.attendance >= 75)
                cout << "Status: ✅ PASS\n";
            else
                cout << "Status: ❌ FAIL\n";
            found = true;
            break;
        }
    }
    if (!found) cout << "No record found for Roll No " << roll << ".\n";
}

// -------------------------
// MAIN MENU
// -------------------------
int main() {
    loadFromFile();
    int choice;

    do {
        cout << "\n===== STUDENT MANAGEMENT SYSTEM =====\n";
        cout << "1. Teacher Menu\n";
        cout << "2. Student Menu\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            int tchoice;
            do {
                cout << "\n--- TEACHER MENU ---\n";
                cout << "1. Add Student\n";
                cout << "2. View All Students\n";
                cout << "3. Back to Main Menu\n";
                cout << "Enter choice: ";
                cin >> tchoice;

                switch (tchoice) {
                case 1: addStudent(); break;
                case 2: viewAllStudents(); break;
                case 3: cout << "Returning...\n"; break;
                default: cout << "Invalid option.\n"; break;
                }
            } while (tchoice != 3);
            break;
        }

        case 2:
            viewMyRecord();
            break;

        case 3:
            cout << "Exiting program... Goodbye!\n";
            break;

        default:
            cout << "Invalid option.\n";
            break;
        }
    } while (choice != 3);

    return 0;
}
