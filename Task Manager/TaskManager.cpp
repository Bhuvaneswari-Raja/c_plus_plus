#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <chrono>
#include <iomanip>
#include "Profile.h"

using namespace std;

struct Task {
    string title;
    string description;
    string timestamp;
    bool completed;

    // Default constructor
    Task() : title(""), description(""), timestamp(""), completed(false) {}

    // Parameterized constructor
    Task(const string& t, const string& d, const string& time)
        : title(t), description(d), timestamp(time), completed(false) {}
};

void displayMenu();
void addTask(map<int, Task>& tasks, const string& filename, int& taskID);
void displayTasks(const map<int, Task>& tasks);
void markTaskCompleted(map<int, Task>& tasks, const string& filename);
void deleteTask(map<int, Task>& tasks, const string& filename);
void saveTasksToFile(const map<int, Task>& tasks, const string& filename);
void loadTasksFromFile(map<int, Task>& tasks, const string& filename, int& taskID);

int main() {
    Profile userProfile;
    map<int, Task> tasks;
    string profileFile = "profile.txt";
    string taskFile = "tasks.txt";
    int taskID = 1;

    //cout << "User Profile: -> ";
    //cout << addressof(userProfile);
    

    userProfile.LoadProfile(profileFile); 
    loadTasksFromFile(tasks, taskFile, taskID);

    int choice = 0;

    do {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                addTask(tasks, taskFile, taskID);
                break;
            case 2:
                displayTasks(tasks);
                break;
            case 3:
                markTaskCompleted(tasks, taskFile);
                break;
            case 4:
                deleteTask(tasks, taskFile);
                break;
            case 5:
                userProfile.DisplayProfile();
                break;
            case 6: {
                string name, email;
                cout << "Enter new name: ";
                getline(cin, name);
                cout << "Enter new email: ";
                getline(cin, email);
                userProfile.SetName(name);
                userProfile.SetEmail(email);
                userProfile.SaveProfile(profileFile);
                break;
            }
            case 7:
                cout << "Exiting Task Manager. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 7);

    return 0;
}

void displayMenu() {
    cout << "\nTask Manager Menu:\n";
    cout << "1. Add Task\n";
    cout << "2. Display Tasks\n";
    cout << "3. Mark Task as Completed\n";
    cout << "4. Delete Task\n";
    cout << "5. View Profile\n";
    cout << "6. Edit Profile\n";
    cout << "7. Exit\n";
}

void addTask(map<int, Task>& tasks, const string& filename, int& taskID) {
    string title, description;

    cout << "Enter task title: ";
    getline(cin, title);
    cout << "Enter task description: ";
    getline(cin, description);

    auto now = chrono::system_clock::now();
    time_t currentTime = chrono::system_clock::to_time_t(now);
    string timestamp = ctime(&currentTime);
    timestamp.pop_back(); // Remove newline character

    tasks[taskID] = Task(title, description, timestamp);
    taskID++;
    saveTasksToFile(tasks, filename);

    cout << "Task added successfully!\n";
}

void displayTasks(const map<int, Task>& tasks) {
    if (tasks.empty()) {
        cout << "No tasks to display!\n";
        return;
    }

    cout << "\nTasks:\n";
    for (map<int, Task>::const_iterator it = tasks.begin(); it != tasks.end(); ++it) {
        const int& id = it->first;
        const Task& task = it->second;
        cout << id << ". " << task.title
             << " [" << (task.completed ? "Completed" : "Pending") << "]\n";
        cout << "   Description: " << task.description << "\n";
        cout << "   Timestamp: " << task.timestamp << "\n";
    }
}

void markTaskCompleted(map<int, Task>& tasks, const string& filename) {
    if (tasks.empty()) {
        cout << "No tasks available to mark as completed!\n";
        return;
    }

    int taskNum;
    displayTasks(tasks);
    cout << "Enter the task number to mark as completed: ";
    cin >> taskNum;

    map<int, Task>::iterator it = tasks.find(taskNum);
    if (it != tasks.end()) {
        it->second.completed = true;
        saveTasksToFile(tasks, filename);
        cout << "Task marked as completed!\n";
    } else {
        cout << "Invalid task number!\n";
    }
}

void deleteTask(map<int, Task>& tasks, const string& filename) {
    if (tasks.empty()) {
        cout << "No tasks available to delete!\n";
        return;
    }

    int taskNum;
    displayTasks(tasks);
    cout << "Enter the task number to delete: ";
    cin >> taskNum;

    if (tasks.erase(taskNum)) {
        saveTasksToFile(tasks, filename);
        cout << "Task deleted successfully!\n";
    } else {
        cout << "Invalid task number!\n";
    }
}

void saveTasksToFile(const map<int, Task>& tasks, const string& filename) {
    ofstream outFile(filename);
    if (outFile.is_open()) {
        for (map<int, Task>::const_iterator it = tasks.begin(); it != tasks.end(); ++it) {
            outFile << it->first << "|" << it->second.title << "|"
                    << it->second.description << "|" << it->second.timestamp << "|"
                    << it->second.completed << "\n";
        }
        outFile.close();
    } else {
        cout << "Error saving tasks to file.\n";
    }
}

void loadTasksFromFile(map<int, Task>& tasks, const string& filename, int& taskID) {
    ifstream inFile(filename);
    if (inFile.is_open()) {
        tasks.clear();
        string title, description, timestamp;
        int id;
        bool completed;
        while (inFile >> id) {
            inFile.ignore(); // Ignore the delimiter
            getline(inFile, title, '|');
            getline(inFile, description, '|');
            getline(inFile, timestamp, '|');
            inFile >> completed;
            inFile.ignore(); // Ignore the newline character
            tasks[id] = Task(title, description, timestamp);
            tasks[id].completed = completed;
            taskID = max(taskID, id + 1); // Ensure taskID continues correctly
        }
        inFile.close();
    } else {
        cout << "No existing tasks found. Starting fresh.\n";
    }
    
}
