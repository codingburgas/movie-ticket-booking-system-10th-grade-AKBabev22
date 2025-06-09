#include <iostream>
#include <fstream>
#include <string>
#include "Output.h"
#include "auth.h"
using namespace std;

const string USER_FILE = "../Assets/User/UsersInfo.txt";

bool userExists(string username)
{
    ifstream file(USER_FILE);
    string user, pass;

    while (file >> user >> pass)
    {
        if (user == username) 
        {
            return true;
        }
    }
    return false;
}

void registerUser()
{

    string username, password;

    cout << "=== Register ===" << endl;
    cout << "Enter username: ";
    cin >> username;

    if (userExists(username))
    {
        cout << "Username already exists. Try a different one." << endl;
        return;
    }

    cout << "Enter password: ";
    cin >> password;

    ofstream file(USER_FILE, ios::app);
    file << username << " " << password << endl;

    file.close();

    system("cls");

    cout << "Registration successful!" << endl;

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

    while (file >> user >> pass) 
    {
        if (user == username && pass == password)
        {
            cout << "Login successful!" << endl;

            mainMenu(0);

            return true;
        }
    }

    cout << "Invalid username or password!" << endl;

    return false;
}
