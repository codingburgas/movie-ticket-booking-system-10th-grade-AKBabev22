#include <iostream>
#include <fstream>
#include <string>
#include "Output.h"
using namespace std;

void mainMenu(int count)
{

	string menuOutput, temp;

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
			break;
	}
}