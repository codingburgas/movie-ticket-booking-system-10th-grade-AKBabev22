 #include <iostream>
#include <vector>
#include <string>
#include "../Database/Database.h" 
#include "Extra.h"
#include "Output.h"

using namespace std;

void viewMovies() {
    vector<Theater> theaters = loadDatabase("../Database/Database/Database.txt");

    if (theaters.empty()) {
        cout << "No movies found in the database.\n";
        system("pause");
        return;
    }

    system("cls");
    cout << "=== Available Movies ===\n\n";

    for (const auto& theater : theaters) {
        cout << "Theater: " << theater.name << "\n\n";

        for (const auto& hall : theater.halls) {
            cout << hall.name << ": " << "\n";

            for (const auto& movie : hall.movies) {
                cout << "    Movie Title: " << movie.title << "\n";
                cout << "    Language: " << movie.language << "\n";
                cout << "    Genre: " << movie.genre << "\n";
                cout << "    Release Date: " << movie.releaseDate << "\n";
                cout << "    Showtimes: ";

                for (size_t i = 0; i < movie.showtimes.size(); ++i) {
                    cout << movie.showtimes[i];
                    if (i != movie.showtimes.size() - 1)
                        cout << ", ";
                }

                cout << "\n\n";
            }
        }
    }

    cout << "Press enter to go back." << "\n\n";
    system("pause");

    mainMenu(getCurrentUser());
}