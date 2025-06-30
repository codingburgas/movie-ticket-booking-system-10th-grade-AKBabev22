#pragma once
#include <string>
#include <vector>

struct Card {
    std::string cardName;     
    std::string cardNumber;
    std::string expiryDate;   
};

class CardManager 
{

public:
    CardManager(const std::string& username);

    void loadCards();

    void saveCards() const;

    int displayCardMenu();

    void addNewCard();

    const std::vector<Card>& getCards() const;

private:

    std::string username;
    std::string filename;
    std::vector<Card> cards;
};