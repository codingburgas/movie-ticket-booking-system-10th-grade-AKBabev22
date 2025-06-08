#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include "Output.h"
#include "auth.h"
using namespace std;
namespace fs = std::filesystem;

const string USER_FILE = "users.txt";

const string BASE_USER_DIR = "../Assets/User";

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

    // Save to main user file
    ofstream file(USER_FILE, ios::app);
    file << username << " " << password << endl;
    file.close();

    // Create user folder
    string userFolderPath = BASE_USER_DIR + "\\" + username;
    try {
        if (!fs::exists(BASE_USER_DIR)) {
            fs::create_directory(BASE_USER_DIR);
        }
        if (fs::create_directory(userFolderPath)) {
            string infoFilePath = userFolderPath + "\\Info.txt";
            ofstream infoFile(infoFilePath);
            infoFile << "Username: " << username << endl;
            infoFile << "Password: " << password << endl;
            infoFile.close();
            cout << "\nUser directory and Info.txt created successfully." << endl;
        }
        else {
            cerr << "\nFailed to create user folder." << endl;
        }
    }
    catch (const fs::filesystem_error& e) {
        cerr << "Filesystem error: " << e.what() << endl;
        return;
    }

    system("cls");
    cout << "\nRegistration successful!" << endl;

    // Send to main menu
    mainMenu(0);
}


bool loginUser() {

}
