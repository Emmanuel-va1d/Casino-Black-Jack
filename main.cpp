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
    private:
        int value;
        string suit,
               name;
    public:
        void printDeck() {
            cout << name << endl;
        }
        Cards(const int& value, const string& suit, const string& name) {
            this->value = value;
            this->suit = suit;
            this->name = suit + " OF " + name;
        }
        Cards() {
            value = 0;
            suit = "";
            name = "";
        }
};

int main() {
    Cards card[4][13];

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 13; j++) {
            card[i][j] = Cards(VALUES[j], NAMES[j], SUIT[i]);
            card[i][j].printDeck();
        }
    }

    return 0;
}