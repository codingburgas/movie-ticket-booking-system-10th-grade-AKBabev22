#include <iostream>
#include <vector>
#include <string>
#include <conio.h>
#include <ctime>
#include <fstream>
#include "CardManager.h"
#include "Extra.h"
#include "../Database/Database.h"

using namespace std;

struct SeatPos 
{
    int row;
    int col;
};

void saveTicket(const string& username, const string& theater, const string& hall, const string& movie, int seatNumber, const string& purchaseDate) 
{
    ofstream file("../Database/Database/TicketsDatabase.txt", ios::app);
    file << "Username: " << username << "\n";
    file << "Theater: " << theater << "\n";
    file << "Hall: " << hall << "\n";
    file << "Movie: " << movie << "\n";
    file << "SeatNumber: " << seatNumber << "\n";
    file << "PurchaseDate: " << purchaseDate << "\n";
    file << "----------------------\n";
    file.close();
}

int selectSeat(const string& theaterName, const string& hallName, const string& movieTitle, const string& showtime) 
{
    const int rows = 10;
    const int cols = 15;

    vector<int> bookedSeats = loadBookedSeats(theaterName, hallName, movieTitle, showtime);

    vector<vector<bool>> seats(rows, vector<bool>(cols, true));

    for (int seatId : bookedSeats) 
    {
        int r = seatId / cols;
        int c = seatId % cols;
        seats[r][c] = false;
    }

    int curRow = 0;
    int curCol = 0;

    while (true) 
    {
        system("cls");

        cout << "Legend: [ ] Available  [X] Booked  [_] Your cursor\n\n";
        cout << "Select your seat (Use arrow keys). Press Enter to select. Press '1' to go back.\n\n";

        for (int r = 0; r < rows; ++r)
        {
            for (int c = 0; c < cols; ++c) 
            {
                if (r == curRow && c == curCol)
                {
                    if (seats[r][c])
                        cout << "[_]";
                    else
                        cout << "[X]";
                }

                else 
                {
                    if (seats[r][c])
                        cout << "[ ]";
                    else
                        cout << "[X]";
                }
            }
            cout << "\n";
        }

        int key = _getch();
        if (key == 224 || key == -32)
        {
            key = _getch();
            switch (key) 
            {
            case 72:
                if (curRow > 0)
                    curRow--;
                break;

            case 80:
                if (curRow < rows - 1)
                    curRow++;
                break;

            case 75:
                if (curCol > 0)
                    curCol--;
                break;

            case 77:
                if (curCol < cols - 1)
                    curCol++;
                break;
            }
        }
        else if (key == 13)
        {
            if (seats[curRow][curCol]) 
            {
                int selectedSeat = curRow * cols + curCol;
                bookedSeats.push_back(selectedSeat);

                saveBookedSeats(theaterName, hallName, movieTitle, showtime, bookedSeats);
                return selectedSeat;
            }

            else 
            {
                cout << "\nSeat already booked! Choose another seat.\n";
                system("pause");
            }
        }

        else if (key == '1') 
        {
            return -1;
        }
    }
}

void startBookingFlow()
{
    system("cls");

    vector<Theater> theaters = loadDatabase("../Database/Database/Database.txt");

    if (theaters.empty()) 
    {
        cout << "No cinemas found.\n";
        return;
    }

    cout << "=== Available Cinemas ===\n";
    for (size_t i = 0; i < theaters.size(); ++i)
    {
        cout << i + 1 << ". " << theaters[i].name << "\n";
    }

    int theaterChoice;
    cout << "\nSelect a cinema in the city: ";
    cin >> theaterChoice;

    if (theaterChoice < 1 || theaterChoice > theaters.size())
    {
        cout << "Invalid choice.\n";
        system("pause");
        return;
    }

    Theater& selectedTheater = theaters[theaterChoice - 1];

    while (true) 
    {
        system("cls");
        cout << "=== Movies in " << selectedTheater.name << " ===\n";

        struct MovieSelection 
        {
            size_t hallIndex;
            size_t movieIndex;
        };

        vector<MovieSelection> movieSelections;
        int movieCount = 1;

        for (size_t h = 0; h < selectedTheater.halls.size(); ++h)
        {
            Hall& hall = selectedTheater.halls[h];

            for (size_t m = 0; m < hall.movies.size(); ++m) 
            {
                Movie& movie = hall.movies[m];
                cout << movieCount << ". " << movie.title << " (Hall: " << hall.name << ")\n";
                movieSelections.push_back({ h, m });
                movieCount++;
            }
        }

        if (movieSelections.empty()) 
        {
            cout << "No movies available.\n";
            return;
        }

        int movieChoice;
        cout << "\nSelect a movie by number: ";
        cin >> movieChoice;

        if (movieChoice < 1 || movieChoice >(int)movieSelections.size()) 
        {
            cout << "Invalid choice.\n";
            system("pause");
            continue;
        }

        Movie& selectedMovie = selectedTheater.halls[movieSelections[movieChoice - 1].hallIndex].movies[movieSelections[movieChoice - 1].movieIndex];

        if (selectedMovie.showtimes.empty())
        {
            cout << "No showtimes available for this movie.\n";

            continue;
        }

        while (true) 
        {
            system("cls");

            cout << "\nShowtimes for " << selectedMovie.title << ":\n";

            for (size_t i = 0; i < selectedMovie.showtimes.size(); ++i)
            {
                cout << i + 1 << ". " << selectedMovie.showtimes[i] << "\n";
            }

            int showtimeChoice;

            cout << "\nSelect a showtime by number: ";
            cin >> showtimeChoice;

            if (showtimeChoice < 1 || showtimeChoice >(int)selectedMovie.showtimes.size()) 
            {
                cout << "Invalid choice.\n";
                system("pause");

                continue;
            }

            string chosenShowtime = selectedMovie.showtimes[showtimeChoice - 1];

            int selectedSeat = selectSeat(selectedTheater.name, selectedTheater.halls[movieSelections[movieChoice - 1].hallIndex].name, selectedMovie.title, chosenShowtime);

            if (selectedSeat == -1) 
            {
                continue;
            }

            system("cls");

            cout << "You have selected:\n";
            cout << "Movie: " << selectedMovie.title << "\n";
            cout << "Hall: " << selectedTheater.halls[movieSelections[movieChoice - 1].hallIndex].name << "\n";
            cout << "Showtime: " << chosenShowtime << "\n";
            cout << "Seat Number (ID): " << selectedSeat + 1 << " (Row: " << selectedSeat / 15 + 1 << ", Col: " << selectedSeat % 15 + 1 << ")\n";

            cout << "\nChoose payment method:\n";
            cout << "1. Pay online (credit card)\n";
            cout << "2. Pay through ticket agent (cash or card)\n";
            cout << "Select option: ";

            int paymentChoice;
            cin >> paymentChoice;

            if (paymentChoice == 1) 
            {
                system("cls");

                string username = getCurrentUser();

                CardManager cardManager(username);
                cardManager.loadCards();

                int cardIndex = cardManager.displayCardMenu();
                if (cardIndex == -1) 
                {
                    std::cout << "\nPayment cancelled.\n";
                    system("pause");

                    return;
                }

                Card selectedCard = cardManager.getCards()[cardIndex];

                system("cls");

                std::cout << "You selected card: " << selectedCard.cardName << "\n";
                std::cout << "Card Number: " << selectedCard.cardNumber << "\n";
                std::cout << "Expiry Date: " << selectedCard.expiryDate << "\n";

                std::cout << "\nProcessing payment...\n";
                system("pause");

                std::string purchaseDate = getCurrentDate();
                std::string hallName = selectedTheater.halls[movieSelections[movieChoice - 1].hallIndex].name;

                saveTicket(username, selectedTheater.name, hallName, selectedMovie.title, selectedSeat + 1, purchaseDate);

                std::cout << "\nPayment successful! Booking confirmed and ticket saved.\n";

                return;
            }

            else if (paymentChoice == 2) 
            {
                string username = getCurrentUser();

                string purchaseDate = getCurrentDate();
                string hallName = selectedTheater.halls[movieSelections[movieChoice - 1].hallIndex].name;

                saveTicket(username, selectedTheater.name, hallName, selectedMovie.title, selectedSeat + 1, purchaseDate);

                cout << "\nWARNING: Paying through ticket agent must be done at least 1 hour before the movie else your booking will get canceled\n";
                cout << "\nBooking confirmed! Your ticket has been saved.\n";
                system("pause");

                return;
            }

            else 
            {
                cout << "Invalid payment option.\n";
                system("pause");

                return;
            }
        }
    }
}