#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;

/* arrays holding card values, names and suit */
const int VALUES[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10};
const string NAMES[] = {"ACE", "TWO", "THREE", "FOUR", 
                            "FIVE", "SIX", "SEVEN", "EIGHT", "NINE", 
                            "TEN", "KING", "QUEEN", "JACK"};
const string SUIT[] = {"SPADES", "CLUBS", "HEARTS", "DIAMOND"};

/* class to handle cards */
class Card {
    public:
        int value;
        string name;
        string suit;
        void cardInfo(const int value, const string name, const string suit) {
            this->value = value;
            this->name = name;
            this->suit = suit;
        }
};

/* class to handle a deck */
class Deck {
    private: 
        Card card[4][13];
    public:
        Card getHand() {
            Card hand;
            hand = card[rand() % 4][rand() % 13];
            return hand;
        }
        Deck() {
            srand(static_cast <int>(time(0)));
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 13; j++) 
                    card[i][j].cardInfo(VALUES[i], NAMES[j], SUIT[i]);
            }
        }
};

int main() {
    Deck deck;
    cout << deck.getHand().name;
    cout << deck.getHand().name;

    return 0;
}