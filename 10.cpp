#include <iostream>
#include <string>
using namespace std;

#define MAX_SIZE 100

enum Priority {
    SERIOUS,      // Top priority (0)
    NON_SERIOUS,  // Medium priority (1)
    GENERAL       // Least priority (2)
};

struct Patient {
    string name;
    Priority priority;
};

class PriorityQueue {
private:
    Patient patients[MAX_SIZE];
    int size;

public:
    PriorityQueue() {
        size = 0;
    }

    // Check if the queue is empty
    bool isEmpty() {
        return size == 0;
    }

    // Check if the queue is full
    bool isFull() {
        return size == MAX_SIZE;
    }

    // Add a patient to the queue based on priority
    void enqueue(string name, Priority priority) {
        if (isFull()) {
            cout << "Queue is full. Cannot add more patients.\n";
            return;
        }

        Patient newPatient;
        newPatient.name = name;
        newPatient.priority = priority;

        int i = size - 1;
        
        // Find the correct position based on priority
        while (i >= 0 && patients[i].priority > newPatient.priority) {
            patients[i + 1] = patients[i];
            i--;
        }

        patients[i + 1] = newPatient;
        size++;
        cout << "Patient " << name << " added to the queue.\n";
    }

    // Remove and return the highest priority patient
    Patient dequeue() {
        if (isEmpty()) {
            cout << "Queue is empty. No patients to serve.\n";
            return {"", GENERAL}; // Return empty patient
        }

        Patient servedPatient = patients[0];
        
        // Shift all elements to the left
        for (int i = 0; i < size - 1; i++) {
            patients[i] = patients[i + 1];
        }

        size--;
        return servedPatient;
    }

    // Display all patients in the queue
    void display() {
        if (isEmpty()) {
            cout << "No patients in the queue.\n";
            return;
        }

        cout << "Current patients in queue:\n";
        for (int i = 0; i < size; i++) {
            cout << "Name: " << patients[i].name << ", Priority: ";
            switch (patients[i].priority) {
                case SERIOUS: cout << "Serious"; break;
                case NON_SERIOUS: cout << "Non-serious"; break;
                case GENERAL: cout << "General checkup"; break;
            }
            cout << endl;
        }
    }
};

int main() {
    PriorityQueue hospitalQueue;
    int choice;
    string name;
    int priority;

    while (true) {
        cout << "\nHospital Patient Management System\n";
        cout << "1. Add Patient\n";
        cout << "2. Serve Next Patient\n";
        cout << "3. Display Queue\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter patient name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter priority (0-Serious, 1-Non-serious, 2-General checkup): ";
                cin >> priority;
                if (priority < 0 || priority > 2) {
                    cout << "Invalid priority level.\n";
                } else {
                    hospitalQueue.enqueue(name, static_cast<Priority>(priority));
                }
                break;
            case 2: {
                Patient served = hospitalQueue.dequeue();
                if (served.name != "") {
                    cout << "Serving patient: " << served.name << " (";
                    switch (served.priority) {
                        case SERIOUS: cout << "Serious"; break;
                        case NON_SERIOUS: cout << "Non-serious"; break;
                        case GENERAL: cout << "General checkup"; break;
                    }
                    cout << ")\n";
                }
                break;
            }
            case 3:
                hospitalQueue.display();
                break;
            case 4:
                cout << "Exiting system.\n";
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}