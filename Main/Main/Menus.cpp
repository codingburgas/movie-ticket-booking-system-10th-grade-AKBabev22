#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include "Output.h"
#include "auth.h"
using namespace std;

void mainMenu(int count)
{

	string menuOutput, temp;
	char arrow;

	ifstream Menu("../Assets/Menus/mainMenu.txt");

	switch(count)
	{
		case 0:
			system("cls");
			for (int i = 0; i < 16; i++)
			{
				getline(Menu, menuOutput);
				cout << menuOutput << endl;;
			}

			arrow = _getch();

			if ((int)arrow == 80)
			{
				mainMenu(1);
			}

			else if ((int)arrow == 72)
			{
				mainMenu(4);
			}

			break;

		case 1:
			system("cls");
			for (int i = 0; i < 33 && getline(Menu, menuOutput); i++)
			{
				if (i >= 17)
				{
					cout << menuOutput << endl;
				}
			}

			arrow = _getch();

			if ((int)arrow == 80)
			{
				mainMenu(2);
			}

			else if ((int)arrow == 72)
			{
				mainMenu(0);
			}

			break;

		case 2:
			system("cls");
			for (int i = 0; i < 50 && getline(Menu, menuOutput); i++)
			{
				if (i >= 34)
				{
					cout << menuOutput << endl;
				}
			}

			arrow = _getch();

			if ((int)arrow == 80)
			{
				mainMenu(3);
			}

			else if ((int)arrow == 72)
			{
				mainMenu(1);
			}

			break;

		case 3:
			system("cls");
			for (int i = 0; i < 67 && getline(Menu, menuOutput); i++)
			{
				if (i >= 51)
				{
					cout << menuOutput << endl;
				}
			}

			arrow = _getch();

			if ((int)arrow == 80)
			{
				mainMenu(4);
			}

			else if ((int)arrow == 72)
			{
				mainMenu(2);
			}

			break;

		case 4:
			system("cls");
			for (int i = 0; i < 89 && getline(Menu, menuOutput); i++)
			{
				if (i >= 68)
				{
					cout << menuOutput << endl;
				}
			}

			arrow = _getch();

			if ((int)arrow == 80)
			{
				mainMenu(0);
			}

			else if ((int)arrow == 72)
			{
				mainMenu(3);
			}

			break;
	}
}

void authMenu()
{
	int choice;

	do 
	{
		cout << "=== Movie Ticket Booking System ===" << endl;
		cout << "1. Register" << endl << "2. Login" << endl << "3. Exit" << endl << "Enter choice : ";

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
			break;

		default:
			cout << "Invalid choice." << endl;
		}
	} while (choice != 3);
}
