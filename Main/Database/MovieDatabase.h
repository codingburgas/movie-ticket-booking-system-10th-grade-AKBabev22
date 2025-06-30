#ifndef MOVIEDATABASE_H
#define MOVIEDATABASE_H

#include <string>
#include <vector>

struct Movie {
    std::string title;
    std::string language;
    std::string genre;
    std::string releaseDate;
    std::vector<std::string> showtimes;
};

struct Hall {
    std::string name;
    std::vector<Movie> movies;
};

struct Theater {
    std::string name;
    std::vector<Hall> halls;
};

// Loads theater data from a .txt file
std::vector<Theater> loadDatabase(const std::string& filename);

#endif // MOVIEDATABASE_H
