#include <iostream>
#include <string>
#include <cstdlib>
#include <conio.h>
#include "Output.h"
#include "Extra.h"
#include "auth.h"
#include "Booking.h"
#include "../Database/Purchases.h"
using namespace std;

void mainMenu(string username) 
{
    while (true) 
    {
        system("cls");
        cout << "=== Main Menu ===\n";
        cout << "1. View Movies\n";
        cout << "2. Book Tickets\n";
        cout << "3. View Purchases\n";
        cout << "4. Logout\n";
        cout << "5. Exit\n";
        cout << "Your choice: ";

        int choice;
        cin >> choice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number between 1 and 5.\n";
            system("pause");

            continue;
        }

        switch (choice) 
        {
        case 1:
            viewMovies();
            break;

        case 2:
            startBookingFlow();
            break;

        case 3:
            viewPurchases(username);
            break;

        case 4:
            logoutUser();
            break;

        case 5:
            cout << "Thank you for choosing us.\n";
            system("pause");

            exit(1);
            return;

        default:
            cout << "Invalid choice. Please select a number between 1 and 5.\n";
            break;
        }

        system("pause");
    }
}





void authMenu() 
{
    int choice;
    string loggedInUser;

    if (isSessionValid(loggedInUser)) 
    {
        mainMenu(loggedInUser);
        return;
    }

    do 
    {
        system("cls");

        cout << "=== Authentication ===" << endl;
        cout << "1. Register" << endl;
        cout << "2. Login" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) 
        {
        case 1:
            registerUser();
            break;

        case 2:
            loginUser(); 
            break;

        case 3:
            cout << "Goodbye!" << endl;
            system("pause");

            exit(1);

            break;

        default:
            cout << "Invalid choice." << endl;
        }

        // Re-check session after login attempt
        if (isSessionValid(loggedInUser))
        {
            mainMenu(getCurrentUser());
            break;
        }

    } while (choice != 3);
}

