#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <string>
#include <cstring>
#include <vector>

using namespace std;

// Student class to store student information
class Student {
private:
    char name[50];
    int rollNo;
    char course[30];
    int marks[5];
    int total;
    float percentage;
    char grade;

public:
    // Constructor
    Student() {
        rollNo = 0;
        total = 0;
        percentage = 0.0;
        grade = 'F';
        strcpy(name, "");
        strcpy(course, "");
        for (int i = 0; i < 5; i++) {
            marks[i] = 0;
        }
    }

    // Function to calculate total marks
    void calculateTotal() {
        total = 0;
        for (int i = 0; i < 5; i++) {
            total += marks[i];
        }
    }

    // Function to calculate percentage
    void calculatePercentage() {
        percentage = (total / 5.0);
    }

    // Function to assign grade based on percentage
    void assignGrade() {
        if (percentage >= 80) {
            grade = 'A';
        } else if (percentage >= 60) {
            grade = 'B';
        } else if (percentage >= 40) {
            grade = 'C';
        } else if (percentage >= 33) {
            grade = 'D';
        } else {
            grade = 'F';
        }
    }

    // Function to input student data
    void inputData() {
        cout << "\n\t\t===== Enter Student Details =====\n";
        
        cout << "\n\tEnter Student Name: ";
        cin.ignore();
        cin.getline(name, 50);
        
        cout << "\tEnter Roll Number: ";
        cin >> rollNo;
        
        cout << "\tEnter Course Name: ";
        cin.ignore();
        cin.getline(course, 30);
        
        cout << "\n\tEnter Marks for 5 Subjects (out of 100):\n";
        for (int i = 0; i < 5; i++) {
            cout << "\tSubject " << (i + 1) << ": ";
            cin >> marks[i];
            
            // Validation for marks
            while (marks[i] < 0 || marks[i] > 100) {
                cout << "\tInvalid marks! Enter marks between 0-100: ";
                cin >> marks[i];
            }
        }
        
        calculateTotal();
        calculatePercentage();
        assignGrade();
    }

    // Function to display student data in table format
    void displayData() {
        cout << left << setw(20) << name 
             << setw(12) << rollNo 
             << setw(20) << course 
             << setw(10) << total 
             << setw(12) << fixed << setprecision(2) << percentage 
             << setw(8) << grade << endl;
    }

    // Function to display detailed student data
    void displayDetailedData() {
        cout << "\n\t\t===== Student Result Details =====\n";
        cout << "\n\tName           : " << name;
        cout << "\n\tRoll Number    : " << rollNo;
        cout << "\n\tCourse         : " << course;
        cout << "\n\n\tMarks Details:";
        for (int i = 0; i < 5; i++) {
            cout << "\n\tSubject " << (i + 1) << "     : " << marks[i];
        }
        cout << "\n\t" << string(40, '-');
        cout << "\n\tTotal Marks    : " << total << " / 500";
        cout << "\n\tPercentage     : " << fixed << setprecision(2) << percentage << "%";
        cout << "\n\tGrade          : " << grade;
        cout << "\n\t" << string(40, '=') << "\n";
    }

    // Function to write student data to file
    void writeToFile(ofstream &outFile) {
        outFile << name << "|" 
                << rollNo << "|" 
                << course << "|";
        for (int i = 0; i < 5; i++) {
            outFile << marks[i] << "|";
        }
        outFile << total << "|" 
                << percentage << "|" 
                << grade << endl;
    }

    // Function to append student data to file
    void appendToFile() {
        ofstream outFile("student_records.txt", ios::app);
        if (outFile) {
            writeToFile(outFile);
            outFile.close();
        } else {
            cout << "\n\tError: Unable to open file for writing!\n";
        }
    }

    // Function to read student data from file
    bool readFromFile(ifstream &inFile) {
        char delim;
        inFile.getline(name, 50, '|');
        if (inFile.eof()) return false;
        
        inFile >> rollNo >> delim;
        inFile.getline(course, 30, '|');
        
        for (int i = 0; i < 5; i++) {
            inFile >> marks[i] >> delim;
        }
        
        inFile >> total >> delim;
        inFile >> percentage >> delim;
        inFile >> grade;
        inFile.ignore();
        
        return true;
    }

    // Function to get roll number
    int getRollNo() {
        return rollNo;
    }
};

// Function prototypes
void displayHeader();
void displayMenu();
void insertRecord();
void displayRecords();
void deleteRecord();
void searchRecord();
void modifyRecord();
void clearScreen();
void pauseScreen();

int main() {
    int choice;
    
    do {
        clearScreen();
        displayHeader();
        displayMenu();
        
        cout << "\n\tEnter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                insertRecord();
                break;
            case 2:
                displayRecords();
                break;
            case 3:
                searchRecord();
                break;
            case 4:
                modifyRecord();
                break;
            case 5:
                deleteRecord();
                break;
            case 6:
                cout << "\n\n\t\tThank you for using Student Result Management System!\n";
                cout << "\t\t" << string(50, '=') << "\n\n";
                pauseScreen();
                break;
            default:
                cout << "\n\tInvalid choice! Please try again.\n";
                pauseScreen();
        }
    } while (choice != 6);
    
    return 0;
}

// Function to display system header
void displayHeader() {
    cout << "\n\t" << string(70, '=') << endl;
    cout << "\t\t   STUDENT RESULT MANAGEMENT SYSTEM" << endl;
    cout << "\t" << string(70, '=') << endl;
}

// Function to display main menu
void displayMenu() {
    cout << "\n\t\t===== MAIN MENU =====\n";
    cout << "\n\t\t1. Insert New Record";
    cout << "\n\t\t2. Display All Records";
    cout << "\n\t\t3. Search Record";
    cout << "\n\t\t4. Modify Record";
    cout << "\n\t\t5. Delete Record";
    cout << "\n\t\t6. Exit";
    cout << "\n\n\t\t" << string(30, '-') << endl;
}

// Module 1: Insert Record
void insertRecord() {
    clearScreen();
    displayHeader();
    
    Student student;
    student.inputData();
    student.appendToFile();
    
    cout << "\n\n\t\tRecord inserted successfully!\n";
    cout << "\n\tStudent Details:\n";
    student.displayDetailedData();
    
    pauseScreen();
}

// Module 2: Display All Records
void displayRecords() {
    clearScreen();
    displayHeader();
    
    ifstream inFile("student_records.txt");
    
    if (!inFile) {
        cout << "\n\t\tNo records found or unable to open file!\n";
        pauseScreen();
        return;
    }
    
    Student student;
    int count = 0;
    
    cout << "\n\t\t===== ALL STUDENT RECORDS =====\n\n";
    cout << "\t" << string(90, '-') << endl;
    cout << "\t" << left << setw(20) << "Name" 
         << setw(12) << "Roll No" 
         << setw(20) << "Course" 
         << setw(10) << "Total" 
         << setw(12) << "Percentage" 
         << setw(8) << "Grade" << endl;
    cout << "\t" << string(90, '-') << endl;
    
    while (student.readFromFile(inFile)) {
        cout << "\t";
        student.displayData();
        count++;
    }
    
    cout << "\t" << string(90, '-') << endl;
    cout << "\n\tTotal Records: " << count << endl;
    
    inFile.close();
    pauseScreen();
}

// Module 3: Search Record
void searchRecord() {
    clearScreen();
    displayHeader();
    
    int searchRoll;
    cout << "\n\tEnter Roll Number to Search: ";
    cin >> searchRoll;
    
    ifstream inFile("student_records.txt");
    
    if (!inFile) {
        cout << "\n\t\tNo records found or unable to open file!\n";
        pauseScreen();
        return;
    }
    
    Student student;
    bool found = false;
    
    while (student.readFromFile(inFile)) {
        if (student.getRollNo() == searchRoll) {
            student.displayDetailedData();
            found = true;
            break;
        }
    }
    
    if (!found) {
        cout << "\n\t\tRecord not found for Roll Number: " << searchRoll << endl;
    }
    
    inFile.close();
    pauseScreen();
}

// Module 4: Modify Record
void modifyRecord() {
    clearScreen();
    displayHeader();
    
    int modifyRoll;
    cout << "\n\tEnter Roll Number to Modify: ";
    cin >> modifyRoll;
    
    ifstream inFile("student_records.txt");
    
    if (!inFile) {
        cout << "\n\t\tNo records found or unable to open file!\n";
        pauseScreen();
        return;
    }
    
    // Read all records into a vector
    vector<Student> students;
    Student student;
    bool found = false;
    
    while (student.readFromFile(inFile)) {
        if (student.getRollNo() == modifyRoll) {
            found = true;
            cout << "\n\tRecord found! Enter new details:\n";
            student.inputData();
            cout << "\n\t\tRecord modified successfully!\n";
        }
        students.push_back(student);
    }
    
    inFile.close();
    
    if (found) {
        // Write all records back to file
        ofstream outFile("student_records.txt");
        for (size_t i = 0; i < students.size(); i++) {
            students[i].writeToFile(outFile);
        }
        outFile.close();
    } else {
        cout << "\n\t\tRecord not found for Roll Number: " << modifyRoll << endl;
    }
    
    pauseScreen();
}

// Module 5: Delete Record
void deleteRecord() {
    clearScreen();
    displayHeader();
    
    int deleteRoll;
    cout << "\n\tEnter Roll Number to Delete: ";
    cin >> deleteRoll;
    
    ifstream inFile("student_records.txt");
    
    if (!inFile) {
        cout << "\n\t\tNo records found or unable to open file!\n";
        pauseScreen();
        return;
    }
    
    // Read all records into a vector
    vector<Student> students;
    Student student;
    bool found = false;
    
    while (student.readFromFile(inFile)) {
        if (student.getRollNo() == deleteRoll) {
            found = true;
            cout << "\n\t\tRecord deleted successfully!\n";
            cout << "\n\tDeleted Record Details:\n";
            student.displayDetailedData();
        } else {
            students.push_back(student);
        }
    }
    
    inFile.close();
    
    if (found) {
        // Write remaining records back to file
        ofstream outFile("student_records.txt");
        for (size_t i = 0; i < students.size(); i++) {
            students[i].writeToFile(outFile);
        }
        outFile.close();
    } else {
        cout << "\n\t\tRecord not found for Roll Number: " << deleteRoll << endl;
    }
    
    pauseScreen();
}

// Function to clear screen
void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Function to pause screen
void pauseScreen() {
    cout << "\n\n\tPress Enter to continue...";
    cin.ignore();
    cin.get();
}
