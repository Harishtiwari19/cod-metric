#include <iostream>
#include <vector>
#include <fstream>
#include <string>
using namespace std;


struct Student {
    string name;
    int roll;
    float grade;
};


void addStudent(vector<Student> &students);
void displayStudents(const vector<Student> &students);
void deleteStudent(vector<Student> &students, int roll);
void saveToFile(const vector<Student> &students, const string &filename);
void loadFromFile(vector<Student> &students, const string &filename);

int main() {
    vector<Student> students;
    string filename = "students.txt";
    int choice;

    
    loadFromFile(students, filename);

    do {
        cout << "\n----- Student Record Manager -----\n";
        cout << "1. Add Student\n";
        cout << "2. Display All Students\n";
        cout << "3. Delete Student by Roll Number\n";
        cout << "4. Save & Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addStudent(students);
                break;
            case 2:
                displayStudents(students);
                break;
            case 3: {
                int roll;
                cout << "Enter roll number to delete: ";
                cin >> roll;
                deleteStudent(students, roll);
                break;
            }
            case 4:
                saveToFile(students, filename);
                cout << "Records saved. Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 4);

    return 0;
}


void addStudent(vector<Student> &students) {
    Student s;
    cout << "Enter name: ";
    cin.ignore(); 
    getline(cin, s.name);
    cout << "Enter roll number: ";
    cin >> s.roll;
    cout << "Enter grade: ";
    cin >> s.grade;

    students.push_back(s);
    cout << "Student added successfully.\n";
}

void displayStudents(const vector<Student> &students) {
    if (students.empty()) {
        cout << "No student records to display.\n";
        return;
    }
    cout << "\n--- Student Records ---\n";
    for (const auto &s : students) {
        cout << "Name: " << s.name
             << ", Roll: " << s.roll
             << ", Grade: " << s.grade << endl;
    }
}

void deleteStudent(vector<Student> &students, int roll) {
    bool found = false;
    for (auto it = students.begin(); it != students.end(); ++it) {
        if (it->roll == roll) {
            students.erase(it);
            cout << "Student with roll " << roll << " deleted.\n";
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "No student found with roll number " << roll << ".\n";
    }
}

void saveToFile(const vector<Student> &students, const string &filename) {
    ofstream outFile(filename);
    for (const auto &s : students) {
        outFile << s.name << "," << s.roll << "," << s.grade << "\n";
    }
    outFile.close();
}

void loadFromFile(vector<Student> &students, const string &filename) {
    ifstream inFile(filename);
    if (!inFile) return; 
    string line;
    while (getline(inFile, line)) {
        Student s;
        size_t pos1 = line.find(',');
        size_t pos2 = line.find(',', pos1 + 1);

        s.name = line.substr(0, pos1);
        s.roll = stoi(line.substr(pos1 + 1, pos2 - pos1 - 1));
        s.grade = stof(line.substr(pos2 + 1));

        students.push_back(s);
    }
    inFile.close();
}
