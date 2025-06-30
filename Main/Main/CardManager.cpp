#include "CardManager.h"
#include <fstream>
#include <iostream>
#include <limits>

// Constructor: Initializes a CardManager with a username and generates a filename for storing cards
CardManager::CardManager(const std::string& username) : username(username) {
    filename = "cards_" + username + ".txt";
}

// Loads saved card data from the user's file into memory
void CardManager::loadCards() {
    cards.clear();
    std::ifstream file(filename);
    if (!file.is_open()) return;

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;

        Card c;
        c.cardName = line;

        if (!std::getline(file, c.cardNumber)) break;
        if (!std::getline(file, c.expiryDate)) break;

        cards.push_back(c);
    }
    file.close();
}

// Saves all loaded cards to the user's file, overwriting any existing content
void CardManager::saveCards() const {
    std::ofstream file(filename, std::ios::trunc);
    for (const auto& c : cards) {
        file << c.cardName << "\n"
            << c.cardNumber << "\n"
            << c.expiryDate << "\n";
    }
}

// Displays a menu for the user to select a saved card or add a new one
int CardManager::displayCardMenu() {
    while (true) {
        system("cls");
        std::cout << "=== Saved Cards for " << username << " ===\n";
        for (size_t i = 0; i < cards.size(); ++i) {
            std::cout << i + 1 << ". " << cards[i].cardName << "\n";
        }
        std::cout << cards.size() + 1 << ". Add new card\n";
        std::cout << cards.size() + 2 << ". Cancel\n";
        std::cout << "Select option: ";

        int choice;
        std::cin >> choice;

        if (std::cin.fail() || choice < 1 || choice >(int)cards.size() + 2) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid choice. Try again.\n";
            system("pause");
            continue;
        }

        if (choice == (int)cards.size() + 1) {
            addNewCard();
            continue;
        }
        else if (choice == (int)cards.size() + 2) {
            return -1;
        }
        else {
            return choice - 1;
        }
    }
}

// Allows the user to enter a new card's information and saves it
void CardManager::addNewCard() {
    system("cls");
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    Card newCard;

    std::cout << "Enter a name for this card: ";
    std::getline(std::cin, newCard.cardName);

    std::cout << "Enter card number: ";
    std::getline(std::cin, newCard.cardNumber);

    std::cout << "Enter expiry date (MM/YY): ";
    std::getline(std::cin, newCard.expiryDate);

    std::string cvv;
    std::cout << "Enter CVV: ";
    std::getline(std::cin, cvv);

    cards.push_back(newCard);
    saveCards();

    std::cout << "\nCard added successfully!\n";
    system("pause");
}

// Provides access to the current list of loaded cards
const std::vector<Card>& CardManager::getCards() const {
    return cards;
}
