#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

const char *FILENAME = "records.txt";

struct Record {
    int id;
    char name[30];
    bool isDeleted;
};

// Insert a new record
void insertRecord() {
    Record rec;
    cout << "\nEnter ID: ";
    cin >> rec.id;
    cin.ignore(); // to clear newline from input buffer
    cout << "Enter Name: ";
    cin.getline(rec.name, 30);
    rec.isDeleted = false;

    ofstream file(FILENAME, ios::binary | ios::app);
    if (!file) {
        cout << "Error opening file.\n";
        return;
    }
    file.write(reinterpret_cast<char*>(&rec), sizeof(rec));
    file.close();
    cout << "Record inserted successfully.\n";
}

// Display all valid records
void displayRecords() {
    Record rec;
    ifstream file(FILENAME, ios::binary);
    if (!file) {
        cout << "No records found.\n";
        return;
    }

    cout << "\n--- Records ---\n";
    bool found = false;
    while (file.read(reinterpret_cast<char*>(&rec), sizeof(rec))) {
        if (!rec.isDeleted) {
            cout << "ID: " << rec.id << ", Name: " << rec.name << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "No active records to display.\n";
    }
    file.close();
}

// Delete a record by marking isDeleted = true
void deleteRecord() {
    int targetId;
    cout << "\nEnter ID to delete: ";
    cin >> targetId;

    fstream file(FILENAME, ios::binary | ios::in | ios::out);
    if (!file) {
        cout << "File not found.\n";
        return;
    }

    Record rec;
    bool found = false;

    while (file.read(reinterpret_cast<char*>(&rec), sizeof(rec))) {
        if (rec.id == targetId && !rec.isDeleted) {
            rec.isDeleted = true;
            file.seekp(-static_cast<int>(sizeof(rec)), ios::cur);
            file.write(reinterpret_cast<char*>(&rec), sizeof(rec));
            found = true;
            cout << "Record deleted successfully.\n";
            break;
        }
    }

    if (!found) {
        cout << "Record not found or already deleted.\n";
    }

    file.close();
}

int main() {
    int choice;
    do {
        cout << "\n--- MENU ---\n";
        cout << "1. Insert Record\n";
        cout << "2. Display Records\n";
        cout << "3. Delete Record\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                insertRecord();
                break;
            case 2:
                displayRecords();
                break;
            case 3:
                deleteRecord();
                break;
            case 4:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 4);

    return 0;
}