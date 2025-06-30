#include "MovieDatabase.h"
#include <fstream>
#include <sstream>

std::vector<Theater> loadDatabase(const std::string& filename) {
    std::vector<Theater> theaters;
    std::ifstream file(filename);
    std::string line;
    Theater currentTheater;
    Hall currentHall;
    Movie currentMovie;

    while (getline(file, line)) {
        if (line.find("Theater:") != std::string::npos) {
            if (!currentHall.name.empty()) {
                currentHall.movies.push_back(currentMovie);
                currentTheater.halls.push_back(currentHall);
                currentHall = Hall();
            }
            if (!currentTheater.name.empty()) {
                theaters.push_back(currentTheater);
            }
            currentTheater = Theater();
            currentTheater.name = line.substr(line.find(":") + 2);
        }
        else if (line.find("Hall:") != std::string::npos) {
            if (!currentHall.name.empty()) {
                currentHall.movies.push_back(currentMovie);
                currentTheater.halls.push_back(currentHall);
            }
            currentHall = Hall();
            currentHall.name = line.substr(line.find(":") + 2);
            currentMovie = Movie();
        }
        else if (line.find("Movie:") != std::string::npos) {
            currentMovie = Movie();
            currentMovie.title = line.substr(line.find(":") + 2);
        }
        else if (line.find("Language:") != std::string::npos) {
            currentMovie.language = line.substr(line.find(":") + 2);
        }
        else if (line.find("Genre:") != std::string::npos) {
            currentMovie.genre = line.substr(line.find(":") + 2);
        }
        else if (line.find("ReleaseDate:") != std::string::npos) {
            currentMovie.releaseDate = line.substr(line.find(":") + 2);
        }
        else if (line.find("Showtimes:") != std::string::npos) {
            std::stringstream ss(line.substr(line.find(":") + 2));
            std::string time;
            while (getline(ss, time, ',')) {
                currentMovie.showtimes.push_back(time);
            }
        }
    }

    // Add the last read entries
    if (!currentMovie.title.empty()) currentHall.movies.push_back(currentMovie);
    if (!currentHall.name.empty()) currentTheater.halls.push_back(currentHall);
    if (!currentTheater.name.empty()) theaters.push_back(currentTheater);

    return theaters;
}
