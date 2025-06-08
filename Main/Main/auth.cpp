#include <iostream>
#include <fstream>
#include <string>
#include "Output.h"
#include "auth.h"

const string USER_FILE = "users.txt";

const string BASE_USER_DIR = "../Assets/User";

bool userExists(const string& username) {
    ifstream file(USER_FILE);
    string user, pass;
    while (file >> user >> pass) {
        if (user == username) {
            return true;
        }
    }
    return false;
}

void registerUser() {


}


bool loginUser() {

}
