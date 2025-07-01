#include "CardManager.h"
#include <fstream>
#include <iostream>
#include <limits>

using namespace std;

CardManager::CardManager(const string& username) : username(username)
{
    filename = "../Database/Database/cards_" + username + ".txt";
}

// Loads saved card data from the user's file into memory
void CardManager::loadCards() 
{
    cards.clear();
    ifstream file(filename);
    if (!file.is_open()) return;

    string line;
    while (getline(file, line))
    {
        if (line.empty()) continue;

        Card c;
        c.cardName = line;

        if (!getline(file, c.cardNumber)) break;
        if (!getline(file, c.expiryDate)) break;

        cards.push_back(c);
    }
    file.close();
}

// Saves all loaded cards to the user's file, overwriting any existing content
void CardManager::saveCards() const
{
    ofstream file(filename, ios::trunc);

    for (const auto& c : cards)
    {
        file << c.cardName << "\n" << c.cardNumber << "\n" << c.expiryDate << "\n";
    }
}

// Displays a menu for the user to select a saved card or add a new one
int CardManager::displayCardMenu()
{
    while (true)
    {
        system("cls");

        cout << "=== Saved Cards for " << username << " ===\n";

        for (size_t i = 0; i < cards.size(); ++i) 
        {
            cout << i + 1 << ". " << cards[i].cardName << "\n";
        }

        cout << cards.size() + 1 << ". Add new card\n";
        cout << cards.size() + 2 << ". Cancel\n";
        cout << "Select option: ";

        int choice;
        cin >> choice;

        if (cin.fail() || choice < 1 || choice >(int)cards.size() + 2) 
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Invalid choice. Try again.\n";
            system("pause");

            continue;
        }

        if (choice == (int)cards.size() + 1)
        {
            addNewCard();
            continue;
        }

        else if (choice == (int)cards.size() + 2)
        {
            return -1;
        }

        else
        {
            return choice - 1;
        }
    }
}

// Allows the user to enter a new card's information and saves it
void CardManager::addNewCard() 
{
    system("cls");
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    Card newCard;

    cout << "Enter a name for this card: ";
    getline(cin, newCard.cardName);

    cout << "Enter card number: ";
    getline(cin, newCard.cardNumber);

    cout << "Enter expiry date (MM/YY): ";
    getline(cin, newCard.expiryDate);

    string cvv;
    cout << "Enter CVV: ";
    getline(cin, cvv);

    cards.push_back(newCard);
    saveCards();

    cout << "\nCard added successfully!\n";
    system("pause");
}

// Provides access to the current list of loaded cards
const vector<Card>& CardManager::getCards() const 
{
    return cards;
}
