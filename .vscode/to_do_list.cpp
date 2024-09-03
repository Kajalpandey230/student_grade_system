#include <iostream>
#include <vector>
#include <string>
#include<math.h>

// Struct to represent a Task with a description and a completion status
struct Task {
    std::string description;
    bool isCompleted;
};

// Class to manage the to-do list and its tasks
class ToDoList {
private:
    std::vector<Task> tasks; // Vector to store the list of tasks

public:
    // Method to add a new task to the list
    void addTask(const std::string& taskDescription) {
        Task newTask = {taskDescription, false}; // Create a new Task struct with description and completion status
        tasks.push_back(newTask); // Add the new task to the vector
        std::cout << "Task added successfully!" << std::endl;
    }

    // Method to mark a task as completed by its index
    void markTaskAsCompleted(size_t taskIndex) {
        if (taskIndex >= tasks.size()) { // Check if the task index is out of bounds
            std::cout << "Invalid task number!" << std::endl;
            return;
        }
        tasks[taskIndex].isCompleted = true; // Mark the task as completed
        std::cout << "Task marked as completed!" << std::endl;
    }

    // Method to display all tasks
    void displayTasks() const {
        if (tasks.empty()) { // Check if the task list is empty
            std::cout << "No tasks available." << std::endl;
            return;
        }

        std::cout << "Current Tasks:" << std::endl;
        for (size_t i = 0; i < tasks.size(); ++i) { // Iterate through the vector to display each task
            std::cout << i + 1 << ". " << tasks[i].description
                      << (tasks[i].isCompleted ? " [Completed]" : " [Pending]") << std::endl;
        }
    }

    // Method to get the size of the task list
    size_t getSize() const {
        return tasks.size();
    }
};

// Main function to run the to-do list application
int main() {
    ToDoList todoList; // Create an instance of the ToDoList class
    int choice; // Variable to store user's choice from the menu
    
    do {
        // Display menu options
        std::cout << "\nTo-Do List Application\n";
        std::cout << "1. Add Task\n";
        std::cout << "2. Mark Task as Completed\n";
        std::cout << "3. View Tasks\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice; // Get user's choice

        // Check if input is valid
        if (std::cin.fail()) {
            std::cin.clear(); // Clear the error state
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
            std::cout << "Invalid input. Please enter a number." << std::endl;
            continue; // Restart the loop
        }

        switch (choice) {
            case 1: {
                // Add a new task
                std::string taskDescription;
                std::cout << "Enter task description: ";
                std::cin.ignore(); // Ignore leftover newline character from previous input
                std::getline(std::cin, taskDescription); // Get the full line of input for task description
                todoList.addTask(taskDescription); // Add the new task to the list
                break;
            }
            case 2: {
                // Mark a task as completed
                int taskNumber;
                std::cout << "Enter task number to mark as completed: ";
                std::cin >> taskNumber; // Get task number input from user

                // Validate task number input and ensure it's within the list bounds
                if (std::cin.fail() || taskNumber <= 0 || static_cast<size_t>(taskNumber) > todoList.getSize()) {
                    std::cin.clear(); // Clear the error state
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
                    std::cout << "Invalid task number!" << std::endl;
                } else {
                    todoList.markTaskAsCompleted(static_cast<size_t>(taskNumber) - 1); // Convert to zero-based index
                }
                break;
            }
            case 3:
                // Display all tasks
                todoList.displayTasks();
                break;
            case 0:
                // Exit the application
                std::cout << "Exiting the program." << std::endl;
                break;
            default:
                // Handle invalid menu choices
                std::cout << "Invalid choice. Please try again." << std::endl;
                break;
        }
    } while (choice != 0); // Continue looping until the user chooses to exit

    return 0;
}
