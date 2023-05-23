#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;

/* arrays holding card values, names and suit */
const int VALUES[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10};
const string NAMES[] = {"ACE", "TWO", "THREE", "FOUR", "FIVE", 
                        "SIX", "SEVEN", "EIGHT", "NINE", "TEN", 
                        "KING", "QUEEN", "JACK"};
const string SUIT[] = {"SPADES", "CLUBS", "HEARTS", "DIAMOND"};

/* class to handle cards */
class Card {
    public:
        int value;
        string name;
        string suit;
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
                for (int j = 0; j < 13; j++) {
                    card[i][j].value = VALUES[i];
                    card[i][j].name = NAMES[j]; 
                    card[i][j].suit = SUIT[i];
                }
            }
        }
};

/* class to handle players */
class Player {
    public:
        Card playersCard;
        string playerName;
        int cardCount;
        double playerBet;
};

/* class to handle the game's ui */
class Game {
    private:
        Player player[2];
        char choice;
        bool playing;
    public:
        void gameInfo(string name, double money) {
            player[0].playerName = name;
            player[0].playerBet = money;
            player[1].playerName = "Dealer";
            player[1].playerBet = (rand() % 9 + 1) * 12321;
            cout << name << ", do you want to join this round (Y/N)? ";
            cin >> choice;
            if (choice == 'Y' || choice == 'y') playing = true;
            else playing = false;
            system("clear");
        }
};

int main() {
    string name;
    double money;
    Game game;

    cout << "What is your name? ";
    getline(cin, name);
    cout << "What are your funds? ";
    cin >> money;

    game.gameInfo(name, money);

    return 0;
}