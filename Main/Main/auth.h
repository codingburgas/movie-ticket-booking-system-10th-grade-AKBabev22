#pragma once
using namespace std;

void registerUser();

bool isSessionValid(string& loggedInUser);

void logoutUser();

bool loginUser();