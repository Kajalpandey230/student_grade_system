#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <iomanip>

struct Student {
    std::string name;
    int id;
    std::vector<double> grades;
};

std::map<int, Student> students; // Map to store students with ID as the key

// Function to add a new student
void addStudent() {
    std::string name;
    int id;
    
    std::cout << "Enter student name: ";
    std::cin.ignore();
    std::getline(std::cin, name);
    
    std::cout << "Enter student ID: ";
    std::cin >> id;

    if (students.find(id) != students.end()) {
        std::cout << "Student with this ID already exists!" << std::endl;
        return;
    }

    Student newStudent = {name, id, {}};
    students[id] = newStudent;
    std::cout << "Student added successfully!" << std::endl;
}

// Function to add grades to a student
void addGrade() {
    int id;
    double grade;
    
    std::cout << "Enter student ID: ";
    std::cin >> id;
    
    if (students.find(id) == students.end()) {
        std::cout << "Student not found!" << std::endl;
        return;
    }

    std::cout << "Enter grade: ";
    std::cin >> grade;

    students[id].grades.push_back(grade);
    std::cout << "Grade added successfully!" << std::endl;
}

// Function to display grades of all students
void displayGrades() {
    for (const auto& pair : students) {
        const Student& student = pair.second;
        std::cout << "Student ID: " << student.id << ", Name: " << student.name << ", Grades: ";
        for (double grade : student.grades) {
            std::cout << grade << " ";
        }
        std::cout << std::endl;
    }
}

// Function to calculate and display average grades of all students
void calculateAverage() {
    for (const auto& pair : students) {
        const Student& student = pair.second;
        if (student.grades.empty()) {
            std::cout << "Student ID: " << student.id << ", Name: " << student.name << ", Average Grade: N/A (No grades available)" << std::endl;
        } else {
            double sum = 0;
            for (double grade : student.grades) {
                sum += grade;
            }
            double average = sum / student.grades.size();
            std::cout << "Student ID: " << student.id << ", Name: " << student.name << ", Average Grade: " << std::fixed << std::setprecision(2) << average << std::endl;
        }
    }
}

// Function to save student data to a file
void saveToFile() {
    std::ofstream outFile("student_data.txt");
    if (!outFile) {
        std::cerr << "Error opening file for writing!" << std::endl;
        return;
    }
    
    for (const auto& pair : students) {
        const Student& student = pair.second;
        outFile << student.id << "," << student.name;
        for (double grade : student.grades) {
            outFile << "," << grade;
        }
        outFile << std::endl;
    }

    outFile.close();
    std::cout << "Data saved successfully!" << std::endl;
}

// Function to load student data from a file
void loadFromFile() {
    std::ifstream inFile("student_data.txt");
    if (!inFile) {
        std::cerr << "Error opening file for reading!" << std::endl;
        return;
    }
    
    students.clear(); // Clear existing data
    std::string line;
    while (std::getline(inFile, line)) {
        std::istringstream ss(line);
        std::string token;
        Student student;
        if (std::getline(ss, token, ',')) {
            student.id = std::stoi(token);
        }
        if (std::getline(ss, token, ',')) {
            student.name = token;
        }
        while (std::getline(ss, token, ',')) {
            student.grades.push_back(std::stod(token));
        }
        students[student.id] = student;
    }

    inFile.close();
    std::cout << "Data loaded successfully!" << std::endl;
}

// Main function to run the program
int main() {
    loadFromFile(); // Load data from file at startup

    int choice;
    do {
        std::cout << "\nStudent Grades Management System\n";
        std::cout << "1. Add Student\n";
        std::cout << "2. Add Grade\n";
        std::cout << "3. Display Grades\n";
        std::cout << "4. Calculate Average\n";
        std::cout << "5. Save Data\n";
        std::cout << "6. Load Data\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                addGrade();
                break;
            case 3:
                displayGrades();
                break;
            case 4:
                calculateAverage();
                break;
            case 5:
                saveToFile();
                break;
            case 6:
                loadFromFile();
                break;
            case 0:
                std::cout << "Exiting the program." << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
                break;
        }
    } while (choice != 0);

    return 0;
}
