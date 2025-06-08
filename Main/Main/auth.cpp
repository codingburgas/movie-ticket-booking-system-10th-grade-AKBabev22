#include <iostream>
#include <fstream>
#include <string>
#include "Output.h"
#include "auth.h"
using namespace std;
namespace fs = std::filesystem;

const string USER_FILE = "../Assets/User/UsersInfo.txt";

bool userExists(const string& username) {
    ifstream file(USER_FILE);
    string user, pass;
    while (file >> user >> pass) {
        if (user == username) {
            return true;
        }
    }
    return false;
}

void registerUser() {

    string username, password;
    cout << "=== Register ===" << endl;
    cout << "Enter username: ";
    cin >> username;

    if (userExists(username)) {
        cout << "Username already exists. Try a different one." << endl;
        return;
    }

    cout << "Enter password: ";
    cin >> password;

    ofstream file(USER_FILE, ios::app);
    file << username << " " << password << endl;
    file.close();

    system("cls");
    cout << "\nRegistration successful!" << endl;

    mainMenu(0);
}


bool loginUser() {

    system("cls");

    string username, password;
    cout << "=== Login ===" << endl;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    ifstream file(USER_FILE);
    string user, pass;
    while (file >> user >> pass) {
        if (user == username && pass == password) {
            cout << "\nLogin successful!" << endl;

            mainMenu(0);
            return true;
        }
    }

    cout << "\nInvalid username or password!" << endl;
    return false;
}
