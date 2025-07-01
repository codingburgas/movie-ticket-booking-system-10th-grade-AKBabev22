#include <string>
#include <vector>

using namespace std;

struct Movie 
{
    string title;
    string language;
    string genre;
    string releaseDate;
    vector<string> showtimes;
};

struct Hall
{
    string name;
    vector<Movie> movies;
};

struct Theater 
{
    string name;
    vector<Hall> halls;
};


vector<Theater> loadDatabase(const string& filename);

vector<int> loadBookedSeats(const string& theaterName, const string& hallName, const string& movieTitle, const string& showtime);

void saveBookedSeats(const string& theaterName, const string& hallName, const string& movieTitle, const string& showtime, const vector<int>& bookedSeats);