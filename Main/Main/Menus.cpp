#include <iostream>
#include <string>
#include <conio.h>
#include "Output.h"
#include "auth.h"
#include "Booking.h"
using namespace std;

#include <iostream>
using namespace std;

void mainMenu() {
    while (true) {
        system("cls");
        cout << "=== Main Menu ===\n";
        cout << "1. View Movies\n";
        cout << "2. Choose Location\n";
        cout << "3. Book Tickets\n";
        cout << "4. View Purchases\n";
        cout << "5. Logout\n";
        cout << "Select an option (1-5): ";

        int choice;
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number between 1 and 5.\n";
            system("pause");
            continue;
        }

        switch (choice) {
        case 1:
            viewMovies();
            break;
        case 2:
            // Choose Location
            cout << "Choosing location...\n";
            break;
        case 3:
            startBookingFlow();
            break;
        case 4:
            // Purchases
            cout << "Viewing purchases...\n";
            break;
        case 5:
            logoutUser();
            return;
        default:
            cout << "Invalid choice. Please select a number between 1 and 5.\n";
            break;
        }

        system("pause");
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

