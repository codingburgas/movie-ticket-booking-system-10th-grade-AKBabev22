#include "Movie.h"

Movie::Movie(const std::string& t, const std::string& lang, const std::string& g, const std::string& date)
    : title(t), language(lang), genre(g), releaseDate(date) {
}

std::string Movie::getTitle() const { return title; }
std::string Movie::getLanguage() const { return language; }
std::string Movie::getGenre() const { return genre; }
std::string Movie::getReleaseDate() const { return releaseDate; }
