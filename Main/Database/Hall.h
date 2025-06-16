#ifndef HALL_H
#define HALL_H

#include <vector>
#include "Show.h"

class Hall {
private:
    int hallNumber;
    std::vector<Show> shows;

public:
    Hall(int number);
    void addShow(const Show& show);
    const std::vector<Show>& getShows() const;
    int getHallNumber() const;
};

#endif
