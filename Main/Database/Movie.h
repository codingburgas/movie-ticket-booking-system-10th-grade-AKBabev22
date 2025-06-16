#ifndef MOVIE_H
#define MOVIE_H

#include <string>
#include <vector>

class Movie {
private:
    std::string title;
    std::string language;
    std::string genre;
    std::string releaseDate;

public:
    Movie(const std::string& t, const std::string& lang, const std::string& g, const std::string& date);

    std::string getTitle() const;
    std::string getLanguage() const;
    std::string getGenre() const;
    std::string getReleaseDate() const;
};

#endif
