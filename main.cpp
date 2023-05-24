#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;

/* arrays holding card values, names and suit */
const int VALUES[] = {11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10};
const string LETTER[] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "T", "K", "Q", "J"};
const string SYMBOL[] = {"\u2660", "\u2663", "\u2665", "\u2666"};
const string NAMES[] = {"ACE", "TWO", "THREE", "FOUR", "FIVE", 
                        "SIX", "SEVEN", "EIGHT", "NINE", "TEN", 
                        "KING", "QUEEN", "JACK"};
const string SUIT[] = {"SPADES", "CLUBS", "HEARTS", "DIAMOND"};

/* class to handle cards */
class Card {
    public:
        int value;
        string symbol;
        string letter;
        string name;
        string suit;
        string getName() { 
            return name + " OF " + suit; 
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
                for (int j = 0; j < 13; j++) {
                    card[i][j].value = VALUES[j];
                    card[i][j].name = NAMES[j]; 
                    card[i][j].suit = SUIT[i];
                    card[i][j].symbol = SYMBOL[i];
                    card[i][j].letter = LETTER[j];
                }
            }
        }
};

/* class to handle players */
class Player {
    public:
        Card playersCard[5];
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
        int i = 1;
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
        void play(Deck deck) {
            bool active[5];
            player[0].playersCard[0] = deck.getHand();
            player[0].playersCard[1] = deck.getHand();
            player[1].playersCard[0] = deck.getHand();
            player[1].playersCard[1] = deck.getHand();
            while (playing) {
                dealerHand();
                playerHand();
                cin >> choice;
                if (choice == 'Y' || choice == 'y') playing = true;
                else playing = false;
                
            }
            cout << "Goodbye!" << endl;
        }
        void dealerHand() {
            cout << "\n\n\t" << player[1].playerName << "'s HAND\t\t\n\n";
            cout << " Cards\t\t\tCount: " << count(1, 1);
            cout << "\t\tBet: $" << player[1].playerBet << "\n\t\t\t┌─ ─ ─┐\n";
            cout << " " << player[1].playersCard[1].getName() << "   \t|  "; newCard(0, 1, 1);
            cout << "\t\t\t|  "; newCard(1, 1, 1);
            cout << "\t\t\t|  "; newCard(2, 1, 1);
            cout << "\t\t\t└─-"; newCard(3, 1, 1);
            cout << "\t\t\t   "; newCard(4, 1, 1);
        }
        void playerHand() {
            cout << "\n\n\t" << player[0].playerName << "'s HAND\t\t\n\n";
            cout << " Cards\t\t\tCount: " << count(0, 0);
            cout << "\t\tBet: $" << player[0].playerBet;
            cout << "\n " << player[0].playersCard[0].getName() << "   \t"; newCard(0, 0, 0);
            cout << " " << player[0].playersCard[1].getName() << "   \t"; newCard(1, 0, 0);
            cout << "\t\t\t"; newCard(2, 0, 0);
            cout << "\t\t\t"; newCard(3, 0, 0);
            cout << "\t\t\t"; newCard(4, 0, 0);
        }

        void newCard(int r, int j, int p) {
            for (j; j <= i; j++) {
                string row[] = {"┌─ ─ ─┐ ", "|" + player[p].playersCard[j].letter + "    | ",
                                "|  " + player[p].playersCard[j].symbol + "  | ", 
                                "|    " + player[p].playersCard[j].letter + "| ", "└─ ─ ─┘ "};
                string newStr = "";
            
                newStr += row[r];
                cout << newStr;
                if (j == i)
                    cout << endl;
            }
        }

        int count(int j, int p) {
            int value = 0;
            bool hasAce = false;
            for (j; j <= i; j++) {
                if (player[p].playersCard[j].value == 11)
                    hasAce = true;
                value += player[p].playersCard[j].value;
            }
            if (hasAce && value > 21)
                value -= 10;
            return value;
        }
};

int main() {
    string name;
    double money;
    Game game;
    Deck deck;

    cout << "What is your name? ";
    getline(cin, name);
    cout << "What are your funds? ";
    cin >> money;

    game.gameInfo(name, money);
    game.play(deck);

    return 0;
}