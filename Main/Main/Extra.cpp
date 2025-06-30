#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include "Extra.h"

using namespace std;

string getCurrentDate() {
    time_t t = time(nullptr);
    tm now;
    localtime_s(&now, &t);
    char buf[11];
    strftime(buf, sizeof(buf), "%Y-%m-%d", &now);
    return string(buf);
}
