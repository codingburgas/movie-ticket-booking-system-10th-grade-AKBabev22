#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include "Extra.h"

using namespace std;

string getCurrentDate()
{
    time_t t = time(nullptr);
    tm now;
    localtime_s(&now, &t);
    char buf[11];
    strftime(buf, sizeof(buf), "%Y-%m-%d", &now);

    return string(buf);
}

string getCurrentUser() 
{
    ifstream file("../Database/Database/User/UsersInfo.txt");
    string username;

    if (file >> username) 
    {
        return username;
    }

    return "";
}
