#include <iostream>
#include <fstream>
#include <string>
#include "Output.h"
#include "auth.h"
using namespace std;

const string USER_FILE = "../Database/Database/User/UsersInfo.txt";
const string SESSION_FILE = "../Database/Database/User/UserSession.txt";

bool userExists(string username)
{
    ifstream file(USER_FILE);
    string user, pass;

    while (file >> user >> pass)
    {
        if (user == username) 
        {
            file.close();

            return true;
        }
    }

    file.close();

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
        system("pause");
        return;
    }

    cout << "Enter password: ";
    cin >> password;

    ofstream file(USER_FILE, ios::app);
    file << username << " " << password << endl;

    file.close();

    system("cls");

    cout << "Registration successful! Please log in." << endl;

    system("pause");

    authMenu();
}

bool isSessionValid(string& loggedInUser)
{
    ifstream sessionIn(SESSION_FILE);

    if (!sessionIn.is_open()) 
    {
        return false; 
    }

    string username;
    time_t loginTime;

    if (!(sessionIn >> username >> loginTime)) 
    {
        sessionIn.close();
        return false; 
    }

    sessionIn.close();

    time_t currentTime = time(0);
    double secondsPassed = difftime(currentTime, loginTime);

    if (secondsPassed < 7200) 
    {
        loggedInUser = username;
        return true;
    }

    // Session expired
    ofstream clear(SESSION_FILE, ios::trunc);
    clear.close();
    return false;
}

void logoutUser() 
{
    ofstream clear(SESSION_FILE, ios::trunc);
    clear.close();

    system("cls");

    cout << "Logout successful." << endl;
    system("pause");

    authMenu();
}

bool loginUser()
{
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

            system("pause");

            // Save session
            ofstream sessionOut(SESSION_FILE);
            time_t now = time(0);
            sessionOut << username << " " << now;
            sessionOut.close();

            mainMenu(username); 
            return true;
        }
    }

    cout << "Invalid username or password!" << endl;

    system("pause");

    return false;
}
