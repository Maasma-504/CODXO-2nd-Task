#include <iostream>
#include <fstream>
#include <string>
#include <conio.h> 
#include <unordered_map> 
using namespace std;

// Hash function for password hashing (simple XOR-based example, use a better hash function in production)
string hashPassword(const string& password) {
    string hashed = password;
    for (char& c : hashed) {
        c ^= 0x5A; // Simple XOR operation with a fixed key (not secure for real-world use)
    }
    return hashed;
}

void login(const unordered_map<string, string>& users);
void registration(unordered_map<string, string>& users);
void forgot(const unordered_map<string, string>& users);
unordered_map<string, string> loadUsers();
void saveUsers(const unordered_map<string, string>& users);

int main() {
    unordered_map<string, string> users = loadUsers();

    int c;
    cout << "\t\t\t_________________________________________\n\n\n";
    cout << "\t\t\t          Welcome to the Login Page      \n\n\n";
    cout << "\t\t\t_________        MENU        ____________\n\n\n";
    cout << "\t|  Press 1 to LOGIN                     |\n";
    cout << "\t|  Press 2 to REGISTER                  |\n";
    cout << "\t|  Press 3 if you forgot your PASSWORD  |\n";
    cout << "\t|  Press 4 to EXIT                      |\n";
    cout << "\n\t\t\t Please enter your choice: ";
    cin >> c;
    cout << endl;

    switch (c) {
        case 1:
            login(users);
            break;
        case 2:
            registration(users);
            break;
        case 3:
            forgot(users);
            break;
        case 4:
            cout << "\t\t\t Thank you! \n\n\n";
            break;
        default:
            system("cls");
            cout << "\t\t\t Please select from the option given above \n" << endl;
            main();
    }
}

void login(const unordered_map<string, string>& users) {
    string userId, password;
    system("cls");
    cout << "\t\t\t Please enter the username and password: \n";
    cout << "\t\t\t USERNAME: ";
    cin >> userId;
    cout << "\t\t\t PASSWORD: ";
    char ch;
    while ((ch = _getch()) != '\r') { // Masking password input
        password += ch;
        cout << '*';
    }
    cout << endl;

    auto it = users.find(userId);
    if (it != users.end() && it->second == hashPassword(password)) {
        system("cls");
        cout << "\n" << userId << "\n Your LOGIN is successful\n Thanks for logging in! \n";
        main();
    } else {
        cout << "\n LOGIN ERROR \n Please check your username and password\n";
        main();
    }
}

void registration(unordered_map<string, string>& users) {
    string ruserId, rpassword;
    system("cls");
    cout << "\t\t\t Enter the username: ";
    cin >> ruserId;
    cout << "\t\t\t Enter the password: ";
    char ch;
    while ((ch = _getch()) != '\r') { // Masking password input
        rpassword += ch;
        cout << '*';
    }
    cout << endl;

    if (users.find(ruserId) == users.end()) {
        users[ruserId] = hashPassword(rpassword);
        saveUsers(users);
        system("cls");
        cout << "\n\t\t\t Registration is successful! \n";
    } else {
        cout << "\n\t\t\t Username already exists. Please choose a different username. \n";
    }
    main();
}

void forgot(const unordered_map<string, string>& users) {
    int option;
    system("cls");
    cout << "\t\t\t You forgot the password? No worries \n";
    cout << "Press 1 to search your id by username \n";
    cout << "Press 2 to go to the main menu \n";
    cout << "\t\t\t Enter your choice: ";
    cin >> option;

    switch (option) {
        case 1: {
            string suserId;
            cout << "\n\t\t\t Enter the username which you remembered: ";
            cin >> suserId;

            auto it = users.find(suserId);
            if (it != users.end()) {
                cout << "\n\n Your account is found \n";
                cout << "\n\n Your password is: " << it->second << endl;
            } else {
                cout << "\n\t Sorry! Your account is not found! \n";
            }
            main();
            break;
        }
        case 2:
            main();
            break;
        default:
            cout << "\t\t\t Wrong choice! Please try again \n";
            forgot(users);
    }
}

unordered_map<string, string> loadUsers() {
    unordered_map<string, string> users;
    ifstream input("records.txt");
    if (input) {
        string id, pass;
        while (input >> id >> pass) {
            users[id] = pass;
        }
        input.close();
    }
    return users;
}

void saveUsers(const unordered_map<string, string>& users) {
    ofstream output("records.txt");
    for (const auto& pair : users) {
        output << pair.first << " " << pair.second << endl;
    }
}
