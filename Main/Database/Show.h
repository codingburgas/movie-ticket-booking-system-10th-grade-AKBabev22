#ifndef SHOW_H
#define SHOW_H

#include <string>
#include "Movie.h"

class Show {
private:
    Movie movie;
    std::string timeSlot;

public:
    Show(const Movie& m, const std::string& slot);

    Movie getMovie() const;
    std::string getTimeSlot() const;
};

#endif
