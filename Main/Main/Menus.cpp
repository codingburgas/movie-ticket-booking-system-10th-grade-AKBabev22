#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include "Output.h"
#include "auth.h"
#include "Booking.h"
using namespace std;

void mainMenu() {
    int count = 0;
    char arrow;

    while (true) {
        system("cls");
        ifstream Menu("../Assets/Menus/mainMenu.txt");
        string menuOutput;

        for (int i = 0; i < 89 && getline(Menu, menuOutput); i++) {
            if ((count == 0 && i < 16) ||
                (count == 1 && i >= 17 && i < 33) ||
                (count == 2 && i >= 34 && i < 50) ||
                (count == 3 && i >= 51 && i < 67) ||
                (count == 4 && i >= 68 && i < 89)) {
                cout << menuOutput << endl;
            }
        }

        arrow = _getch();
        if (arrow == -32 || arrow == 224) {
            arrow = _getch();
        }

        if (arrow == 80) {
            count = (count + 1) % 5;
        }
        else if (arrow == 72) {
            count = (count - 1 + 5) % 5;
        }
        else if (arrow == 13) {
            switch (count) {
            case 0:
                // View Movies
                break;
            case 1:
                // Choose Location
                break;
            case 2:
                startBookingFlow();
                break;
            case 3:
                // Purchases
                break;
            case 4:
                logoutUser();
                return;
            }
        }
    }
}




void authMenu() {
    int choice;
    string loggedInUser;

    // Check if the session is still valid before showing options
    if (isSessionValid(loggedInUser)) {
        mainMenu();  
        return;
    }

    do {
        system("cls");

        cout << "=== Movie Ticket Booking System ===" << endl;
        cout << "1. Register" << endl;
        cout << "2. Login" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            registerUser();
            break;

        case 2:
            loginUser(); 
            break;

        case 3:
            cout << "Goodbye!" << endl;
            break;

        default:
            cout << "Invalid choice." << endl;
        }

        // Re-check session after login attempt
        if (isSessionValid(loggedInUser)) {
            mainMenu();
            break;
        }

    } while (choice != 3);
}

