#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm> 
#include "Database.h"

using namespace std;

inline string trim(const string& s)
{
    auto start = s.find_first_not_of(" \t\r\n");
    auto end = s.find_last_not_of(" \t\r\n");
    return (start == string::npos) ? "" : s.substr(start, end - start + 1);
}

vector<Theater> loadDatabase(const string& filename)
{
    vector<Theater> theaters;
    ifstream file(filename);

    if (!file.is_open()) 
    {
        cerr << "Failed to open database file: " << filename << "\n";
        return theaters;
    }

    string line;
    Theater currentTheater;
    Hall currentHall;
    Movie currentMovie;

    while (getline(file, line)) 
    {
        line = trim(line);
        if (line.empty()) continue;

        if (line.find("Theater:") == 0) 
        {
      
            if (!currentMovie.title.empty())
            {
                currentHall.movies.push_back(currentMovie);
                currentMovie = Movie();
            }

            if (!currentHall.name.empty()) 
            {
                currentTheater.halls.push_back(currentHall);
                currentHall = Hall();
            }

            if (!currentTheater.name.empty()) 
            {
                theaters.push_back(currentTheater);
                currentTheater = Theater();
            }

            currentTheater.name = trim(line.substr(8)); 
        }
        else if (line.find("Hall:") == 0)

        {
            if (!currentMovie.title.empty())
            {
                currentHall.movies.push_back(currentMovie);
                currentMovie = Movie();
            }

            if (!currentHall.name.empty())
            {
                currentTheater.halls.push_back(currentHall);
            }

            currentHall = Hall();
            currentHall.name = trim(line.substr(5)); 
        }

        else if (line.find("Movie:") == 0) 
        {
            if (!currentMovie.title.empty()) 
            {
                currentHall.movies.push_back(currentMovie);
            }
            currentMovie = Movie();
            currentMovie.title = trim(line.substr(6)); 
        }

        else if (line.find("Language:") == 0) 
        {
            currentMovie.language = trim(line.substr(9)); 
        }

        else if (line.find("Genre:") == 0)
        {
            currentMovie.genre = trim(line.substr(6)); 
        }

        else if (line.find("ReleaseDate:") == 0) 
        {
            currentMovie.releaseDate = trim(line.substr(12)); 
        }

        else if (line.find("Showtimes:") == 0)
        {
            stringstream ss(trim(line.substr(10))); 
            string time;

            currentMovie.showtimes.clear();

            while (getline(ss, time, ',')) 
            {
                currentMovie.showtimes.push_back(trim(time));
            }
        }
    }

    if (!currentMovie.title.empty())
    {
        currentHall.movies.push_back(currentMovie);
    }

    if (!currentHall.name.empty())
    {
        currentTheater.halls.push_back(currentHall);
    }

    if (!currentTheater.name.empty()) 
    {
        theaters.push_back(currentTheater);
    }

    return theaters;
}

vector<int> loadBookedSeats(const string& theaterName, const string& hallName, const string& movieTitle, const string& showtime) 
{
    vector<int> bookedSeats;
    ifstream file("../Database/Database/SeatBookings.txt");
    string line;

    bool match = false;

    while (getline(file, line)) 
    {
        if (line.find("Theater:") != string::npos) 
        {
            match = (line.substr(line.find(":") + 2) == theaterName);
        }

        else if (match && line.find("Hall:") != string::npos)
        {
            match = (line.substr(line.find(":") + 2) == hallName);
        }

        else if (match && line.find("Movie:") != string::npos) 
        {
            match = (line.substr(line.find(":") + 2) == movieTitle);
        }

        else if (match && line.find("Showtime:") != string::npos)
        {
            match = (line.substr(line.find(":") + 2) == showtime);
        }

        else if (match && line.find("BookedSeats:") != string::npos)
        {
            string seatsStr = line.substr(line.find(":") + 2);
            stringstream ss(seatsStr);
            string seatIdStr;

            while (getline(ss, seatIdStr, ','))
            {
                try 
                {
                    int seatId = stoi(seatIdStr);
                    bookedSeats.push_back(seatId);
                }
                catch (...) {}
            }
            break; 
        }
    }

    return bookedSeats;
}

// Save booked seats
void saveBookedSeats(const string& theaterName, const string& hallName, const string& movieTitle, const string& showtime, const vector<int>& bookedSeats) 
{
    ifstream fileIn("../Database/Database/SeatBookings.txt");
    vector<string> lines;
    string line;
    bool found = false;
    size_t i = 0;

    while (getline(fileIn, line)) 
    {
        lines.push_back(line);
    }

    fileIn.close();

    // Search for matching block
    for (i = 0; i < lines.size(); ++i) 
    {
        if (lines[i].find("Theater:") != string::npos && lines[i].substr(lines[i].find(":") + 2) == theaterName) 
        {
            size_t j = i + 1;
            bool hallMatch = false, movieMatch = false, showtimeMatch = false;

            while (j < lines.size() && !lines[j].empty())
            {
                if (lines[j].find("Hall:") != string::npos)
                    hallMatch = (lines[j].substr(lines[j].find(":") + 2) == hallName);
                if (hallMatch && lines[j].find("Movie:") != string::npos)
                    movieMatch = (lines[j].substr(lines[j].find(":") + 2) == movieTitle);
                if (hallMatch && movieMatch && lines[j].find("Showtime:") != string::npos)
                    showtimeMatch = (lines[j].substr(lines[j].find(":") + 2) == showtime);

                if (hallMatch && movieMatch && showtimeMatch && lines[j].find("BookedSeats:") != string::npos) {
                    // Replace BookedSeats line
                    string newSeatsLine = "BookedSeats: ";
                    for (size_t k = 0; k < bookedSeats.size(); ++k) {
                        newSeatsLine += to_string(bookedSeats[k]);
                        if (k != bookedSeats.size() - 1)
                            newSeatsLine += ",";
                    }
                    lines[j] = newSeatsLine;
                    found = true;
                    break;
                }
                j++;
            }
            break;
        }
    }

    if (!found) 
    {
        lines.push_back("Theater: " + theaterName);
        lines.push_back("Hall: " + hallName);
        lines.push_back("Movie: " + movieTitle);
        lines.push_back("Showtime: " + showtime);

        string newSeatsLine = "BookedSeats: ";

        for (size_t k = 0; k < bookedSeats.size(); ++k)
        {
            newSeatsLine += to_string(bookedSeats[k]);

            if (k != bookedSeats.size() - 1)
                newSeatsLine += ",";
        }

        lines.push_back(newSeatsLine);
    }

    ofstream fileOut("../Database/Database/SeatBookings.txt");
    for (const auto& l : lines)
    {
        fileOut << l << "\n";
    }

    fileOut.close();
}
