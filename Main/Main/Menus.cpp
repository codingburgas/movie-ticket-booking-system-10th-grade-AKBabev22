#include <iostream>
#include <fstream>
#include <string>
#include "Output.h"
using namespace std;

void mainMenu()
{
	int choice;
	string menuOutput;

	ifstream Menu("../Assets/Menus/mainMenu.txt");

	while (getline(Menu, menuOutput))
	{
		cout << menuOutput << endl;
	}

	cin >> choice;
	
	Menu.close();
}