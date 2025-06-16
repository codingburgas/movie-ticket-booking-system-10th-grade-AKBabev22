#ifndef CINEMA_H
#define CINEMA_H

#include <string>
#include <vector>
#include "Hall.h"

class Cinema {
private:
    std::string name;
    std::vector<Hall> halls;

public:
    Cinema(const std::string& n);
    void addHall(const Hall& hall);
    const std::string& getName() const;
    const std::vector<Hall>& getHalls() const;
};

#endif
