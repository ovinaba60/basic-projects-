// Student Management System
// Console application in C++ with file handling.
// Features: add, view, search, update and delete student records.
// Records are saved in students.txt (one record per line: id|name|department|cgpa).

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <limits>
#include <iomanip>
using namespace std;

struct Student {
    int id;
    string name;
    string department;
    double cgpa;
};

const string FILE_NAME = "students.txt";

vector<Student> loadStudents() {
    vector<Student> students;
    ifstream in(FILE_NAME);
    string line;
    while (getline(in, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string idStr, name, dept, cgpaStr;
        getline(ss, idStr, '|');
        getline(ss, name, '|');
        getline(ss, dept, '|');
        getline(ss, cgpaStr, '|');
        Student s;
        s.id = stoi(idStr);
        s.name = name;
        s.department = dept;
        s.cgpa = stod(cgpaStr);
        students.push_back(s);
    }
    return students;
}

void saveStudents(const vector<Student>& students) {
    ofstream out(FILE_NAME);
    for (const Student& s : students) {
        out << s.id << '|' << s.name << '|' << s.department << '|' << s.cgpa << '\n';
    }
}

int findIndexById(const vector<Student>& students, int id) {
    for (size_t i = 0; i < students.size(); i++) {
        if (students[i].id == id) return (int)i;
    }
    return -1;
}

int readInt(const string& prompt) {
    int x;
    while (true) {
        cout << prompt;
        if (cin >> x) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return x;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a number.\n";
    }
}

double readCgpa(const string& prompt) {
    double x;
    while (true) {
        cout << prompt;
        if (cin >> x && x >= 0.0 && x <= 4.0) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return x;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid CGPA. Enter a value between 0.00 and 4.00.\n";
    }
}

string readLine(const string& prompt) {
    string s;
    while (true) {
        cout << prompt;
        getline(cin, s);
        if (!s.empty() && s.find('|') == string::npos) return s;
        cout << "Input cannot be empty or contain '|'.\n";
    }
}

void printHeader() {
    cout << left << setw(8) << "ID" << setw(25) << "Name"
         << setw(15) << "Department" << "CGPA\n";
    cout << string(55, '-') << '\n';
}

void printStudent(const Student& s) {
    cout << left << setw(8) << s.id << setw(25) << s.name
         << setw(15) << s.department << fixed << setprecision(2) << s.cgpa << '\n';
}

void addStudent() {
    vector<Student> students = loadStudents();
    Student s;
    s.id = readInt("Enter ID: ");
    if (findIndexById(students, s.id) != -1) {
        cout << "A student with this ID already exists.\n";
        return;
    }
    s.name = readLine("Enter name: ");
    s.department = readLine("Enter department: ");
    s.cgpa = readCgpa("Enter CGPA (0-4): ");
    students.push_back(s);
    saveStudents(students);
    cout << "Student added successfully.\n";
}

void viewStudents() {
    vector<Student> students = loadStudents();
    if (students.empty()) {
        cout << "No records found.\n";
        return;
    }
    printHeader();
    for (const Student& s : students) printStudent(s);
}

void searchStudent() {
    vector<Student> students = loadStudents();
    int id = readInt("Enter ID to search: ");
    int idx = findIndexById(students, id);
    if (idx == -1) {
        cout << "Student not found.\n";
        return;
    }
    printHeader();
    printStudent(students[idx]);
}

void updateStudent() {
    vector<Student> students = loadStudents();
    int id = readInt("Enter ID to update: ");
    int idx = findIndexById(students, id);
    if (idx == -1) {
        cout << "Student not found.\n";
        return;
    }
    students[idx].name = readLine("Enter new name: ");
    students[idx].department = readLine("Enter new department: ");
    students[idx].cgpa = readCgpa("Enter new CGPA (0-4): ");
    saveStudents(students);
    cout << "Record updated successfully.\n";
}

void deleteStudent() {
    vector<Student> students = loadStudents();
    int id = readInt("Enter ID to delete: ");
    int idx = findIndexById(students, id);
    if (idx == -1) {
        cout << "Student not found.\n";
        return;
    }
    students.erase(students.begin() + idx);
    saveStudents(students);
    cout << "Record deleted successfully.\n";
}

int main() {
    while (true) {
        cout << "\n===== Student Management System =====\n"
             << "1. Add student\n"
             << "2. View all students\n"
             << "3. Search student by ID\n"
             << "4. Update student\n"
             << "5. Delete student\n"
             << "0. Exit\n";
        int choice = readInt("Choose an option: ");
        switch (choice) {
            case 1: addStudent(); break;
            case 2: viewStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 0: cout << "Goodbye!\n"; return 0;
            default: cout << "Invalid option. Try again.\n";
        }
    }
}
