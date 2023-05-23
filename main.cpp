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
class Cards {
    public:
        int value;
        string suit,
               name;
        Cards(const int& value, const string& suit, const string& name) {
            this->value = value;
            this->suit = suit;
            this->name = suit + " OF " + name;
        }
        Cards() {}
};

class Deck : public Cards {
    private:
        Cards card[4][13];
    public:
        void assignCards() {
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 13; j++) {
                    card[i][j] = Cards(VALUES[j], NAMES[j], SUIT[i]);
                }
            }
        }
        Cards randomCard() {
            srand(static_cast <int>(time(0)));
            return card[rand() % 4][rand() % 13];
        }
};

int main() {

    Deck card;
    card.assignCards();
    cout << card.randomCard().name << endl;

    return 0;
}