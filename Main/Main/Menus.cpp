#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>
#include "Output.h"
using namespace std;

void mainMenu()
{
	string menuOutput;

	ifstream Menu("../Assets/Menus/mainMenu.txt");

	while (getline(Menu, menuOutput))
	{
		cout << menuOutput << endl;
	}
	
	Menu.close();
}