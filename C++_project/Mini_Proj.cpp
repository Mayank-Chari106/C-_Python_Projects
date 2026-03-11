#include <iostream>
#include <fstream>      // For reading/writing files
#include <vector>       // For storing student records
#include <algorithm>    // For find_if and remove_if
#include <sstream>      // For stringstream (line parsing)
using namespace std;

// ============================================================
//                STUDENT CLASS (OOP)
// ============================================================
class Student {
public:
    int rollNo;
    string name;
    string course;
    float marks;
    double attendance;
    static const int total_days; // Declare only — define below

    // Constructor with default values
    Student(int r = 0, string n = "", string c = "", float m = 0.0, double a = 0)
        : rollNo(r), name(n), course(c), marks(m)
    {
        // Convert raw attendance (days present) into percentage
        attendance = (a / total_days) * 100;
    }

    // Function to display one student's details
    void display() const {
        cout << "Roll No: " << rollNo
             << " | Name: " << name
             << " | Course: " << course
             << " | Marks: " << marks
             << " | Attendance: " << attendance << "%" << endl;
    }
};

// ✅ Define the static member (fixes previous compile error)
const int Student::total_days = 100;

// ============================================================
//                FILE HANDLING FUNCTIONS
// ============================================================

// Save all student records to file
void saveToFile(const vector<Student>& students) {
    ofstream file("students.txt");   // Open file (overwrite old data)
    if (!file) {
        cerr << "Error: Unable to open file for writing.\n";
        return;
    }

    for (const auto& s : students) {
        file << s.rollNo << ","
             << s.name << ","
             << s.course << ","
             << s.marks << ","
             << s.attendance << "\n";
    }
    file.close();
}

// Load all students from file safely
vector<Student> loadFromFile() {
    vector<Student> students;
    ifstream file("students.txt");
    if (!file)
        return students; // If file not found, return empty list

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

        // Skip invalid or incomplete lines
        if (rollStr.empty() || marksStr.empty() || attendanceStr.empty())
            continue;

        try {
            int roll = stoi(rollStr);
            float marks = stof(marksStr);
            double attendance = stod(attendanceStr);

            students.push_back(Student(roll, name, course, marks, attendance));
        }
        catch (const invalid_argument&) {
            cerr << "Warning: Skipping invalid line -> " << line << endl;
        }
        catch (const out_of_range&) {
            cerr << "Warning: Number out of range -> " << line << endl;
        }
    }

    file.close();
    return students;
}

// ============================================================
//                HELPER FUNCTION: AVERAGE MARKS
// ============================================================
void showAverageMarks(const vector<Student>& students) {
    if (students.empty()) {
        cout << "No records available.\n";
        return;
    }

    float total = 0;
    for (const auto& s : students)
        total += s.marks;

    float avg = total / students.size();
    cout << "Average Marks of all students: " << avg << endl;
}

// ============================================================
//                MAIN PROGRAM (SWITCH CASE MENU)
// ============================================================
int main() {
    vector<Student> students = loadFromFile();  // Load data from file
    int choice;

    do {
        cout << "\n===== Student Management System =====\n";
        cout << "1. Add Student\n";
        cout << "2. Display All Students\n";
        cout << "3. Search Student by Roll No\n";
        cout << "4. Delete Student\n";
        cout << "5. Update Student\n";
        cout << "6. Show Average Marks\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            // ---------------- ADD STUDENT ----------------
            case 1: {
                int roll;
                string name, course;
                float marks;
                double daysPresent;

                cout << "Enter Roll No: ";
                cin >> roll;
                cout << "Enter Name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter Course: ";
                getline(cin, course);
                cout << "Enter Marks: ";
                cin >> marks;
                cout << "Enter Attendance (days present out of 100): ";
                cin >> daysPresent;

                students.push_back(Student(roll, name, course, marks, daysPresent));
                saveToFile(students);
                cout << "Student added successfully!\n";
                break;
            }

            // ---------------- DISPLAY ALL STUDENTS ----------------
            case 2: {
                cout << "\n--- Student List ---\n";
                if (students.empty())
                    cout << "No student records found.\n";
                else
                    for (const auto& s : students) s.display();
                break;
            }

            // ---------------- SEARCH STUDENT ----------------
            case 3: {
                int roll;
                cout << "Enter Roll No to search: ";
                cin >> roll;

                auto it = find_if(students.begin(), students.end(),
                                  [roll](const Student& s) { return s.rollNo == roll; });

                if (it != students.end())
                    it->display();
                else
                    cout << "Student not found!\n";
                break;
            }

            // ---------------- DELETE STUDENT ----------------
            case 4: {
                int roll;
                cout << "Enter Roll No to delete: ";
                cin >> roll;

                auto it = remove_if(students.begin(), students.end(),
                                    [roll](const Student& s) { return s.rollNo == roll; });

                if (it != students.end()) {
                    students.erase(it, students.end());
                    saveToFile(students);
                    cout << "Student deleted successfully!\n";
                } else {
                    cout << "Student not found!\n";
                }
                break;
            }

            // ---------------- UPDATE STUDENT ----------------
            case 5: {
                int roll;
                cout << "Enter Roll No to update: ";
                cin >> roll;

                auto it = find_if(students.begin(), students.end(),
                                  [roll](Student& s) { return s.rollNo == roll; });

                if (it != students.end()) {
                    cout << "Enter new name: ";
                    cin.ignore();
                    getline(cin, it->name);
                    cout << "Enter new course: ";
                    getline(cin, it->course);
                    cout << "Enter new marks: ";
                    cin >> it->marks;
                    cout << "Enter new attendance (days present out of 100): ";
                    double daysPresent;
                    cin >> daysPresent;
                    it->attendance = (daysPresent / Student::total_days) * 100;

                    saveToFile(students);
                    cout << "Student updated successfully!\n";
                } else {
                    cout << "Student not found!\n";
                }
                break;
            }

            // ---------------- AVERAGE MARKS ----------------
            case 6:
                showAverageMarks(students);
                break;

            // ---------------- EXIT ----------------
            case 7:
                cout << "Exiting... All data saved.\n";
                break;

            // ---------------- INVALID OPTION ----------------
            default:
                cout << "Invalid choice! Please enter 1–7.\n";
        }

    } while (choice != 7);

    return 0;
}
