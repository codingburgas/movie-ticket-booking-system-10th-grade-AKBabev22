#include "Hall.h"

Hall::Hall(int number) : hallNumber(number) {}

void Hall::addShow(const Show& show) {
    shows.push_back(show);
}

const std::vector<Show>& Hall::getShows() const {
    return shows;
}

int Hall::getHallNumber() const {
    return hallNumber;
}
