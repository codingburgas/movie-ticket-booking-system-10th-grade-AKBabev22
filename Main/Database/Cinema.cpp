#include "Cinema.h"

Cinema::Cinema(const std::string& n) : name(n) {}

void Cinema::addHall(const Hall& hall) {
    halls.push_back(hall);
}

const std::string& Cinema::getName() const {
    return name;
}

const std::vector<Hall>& Cinema::getHalls() const {
    return halls;
}
