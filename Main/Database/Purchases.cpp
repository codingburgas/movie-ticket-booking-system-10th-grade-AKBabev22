
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "Purchases.h"

using namespace std;

void viewPurchases(const string& currentUsername) {
    ifstream file("../Database/Database/TicketsDatabase.txt"); // Adjust path if needed
    if (!file.is_open()) {
        cout << "No purchases found.\n";
        return;
    }

    struct Purchase {
        string theater;
        string hall;
        string movie;
        int seatNumber;
        string date;
    };

    vector<Purchase> userPurchases;
    string line;

    string username, theater, hall, movie, seatStr, date;

    while (getline(file, line)) {
        if (line.find("Username: ") == 0)
            username = line.substr(10);
        else if (line.find("Theater: ") == 0)
            theater = line.substr(9);
        else if (line.find("Hall: ") == 0)
            hall = line.substr(6);
        else if (line.find("Movie: ") == 0)
            movie = line.substr(7);
        else if (line.find("SeatNumber: ") == 0)
            seatStr = line.substr(12);
        else if (line.find("PurchaseDate: ") == 0)
            date = line.substr(14);
        else if (line.find("----") == 0) {
            // End of a purchase block
            if (username == currentUsername) {
                Purchase p;
                p.theater = theater;
                p.hall = hall;
                p.movie = movie;
                p.seatNumber = stoi(seatStr);
                p.date = date;
                userPurchases.push_back(p);
            }

            // Reset fields for next block
            username = theater = hall = movie = seatStr = date = "";
        }
    }

    file.close();

    // Sort newest to oldest by date (assuming lexicographical YYYY-MM-DD format)
    sort(userPurchases.begin(), userPurchases.end(), [](const Purchase& a, const Purchase& b) {
        return a.date > b.date;
        });

    if (userPurchases.empty()) {
        cout << "You have no purchases.\n";
        return;
    }

    cout << "=== Your Ticket Purchases ===\n\n";
    for (const auto& p : userPurchases) {
        cout << "Theater: " << p.theater << "\n";
        cout << "Hall: " << p.hall << "\n";
        cout << "Movie: " << p.movie << "\n";
        cout << "Seat Number: " << p.seatNumber << "\n";
        cout << "Date: " << p.date << "\n";
        cout << "------------------------------\n";
    }
}