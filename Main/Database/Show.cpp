#include "Show.h"

Show::Show(const Movie& m, const std::string& slot)
    : movie(m), timeSlot(slot) {
}

Movie Show::getMovie() const { return movie; }
std::string Show::getTimeSlot() const { return timeSlot; }
