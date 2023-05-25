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
        string getName(bool active) { 
            if (active) return name + " OF " + suit; 
            else return "            ";
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
        Deck deck;
        char choice;
        bool playing;
        bool stand[2] = {false, false};
        bool active[5][2] = {{true, true}, {true, true}, {false, false}, 
                            {false, false}, {false, false}};
        int i = 1;
    public:
        void gameInfo(string name, double money) {
            player[0].playerName = name;
            player[0].playerBet = money;
            player[1].playerName = "Dealer";
            player[1].playerBet = (rand() % 9 + 1) * 123212;
            cout << " " << name << ", Play(1) or Quit(2) ";
            cin >> choice;
            if (choice == '1') playing = true;
            else playing = false;
            system("clear");
        }
        void play() {
            player[0].playersCard[0] = deck.getHand();
            player[0].playersCard[1] = deck.getHand();
            player[1].playersCard[0] = deck.getHand();
            player[1].playersCard[1] = deck.getHand();
            while (playing) {
                active[i][0] = true;
                dealerHand();
                playerHand();
                system("clear");
                dealerHand();
                playerHand();
                cout << " Hit(1) or Stand(2)? ";
                cin >> choice;
                if (choice == '1') {
                    i++;
                    player[0].playersCard[i] = deck.getHand();
                    if (count(1, 1) < 17) {
                        player[1].playersCard[i] = deck.getHand();
                        active[i][1] = true;
                    }
                }
                else playing = false;
            }
            cout << "Goodbye!" << endl;
        }
        void dealerHand() {
            cout << "\n\n\t" << player[1].playerName << "'s HAND\t\t\n\n";
            cout << " Cards\t\t\tCount: " << count(1, 1);
            cout << "\t\tBet: $" << player[1].playerBet << "\n\t\t\t┌─ ─ ─┐\n";
            cout << " " << player[1].playersCard[1].getName(active[1][1]) << "   \t|  "; newCard(0, 1, 1);
            cout << " " << player[1].playersCard[2].getName(active[2][1]) << "   \t|  "; newCard(1, 1, 1);
            cout << " " << player[1].playersCard[3].getName(active[3][1]) << "   \t|  "; newCard(2, 1, 1);
            cout << " " << player[1].playersCard[4].getName(active[4][1]) << "   \t└─-"; newCard(3, 1, 1);
            cout << "\t\t\t   "; newCard(4, 1, 1);
        }
        void playerHand() {
            cout << "\n\n\t" << player[0].playerName << "'s HAND\t\t\n\n";
            cout << " Cards\t\t\tCount: " << count(0, 0);
            cout << "\t\tBet: $" << player[0].playerBet << endl;
            cout << " " << player[0].playersCard[0].getName(active[0][0]) << "   \t"; newCard(0, 0, 0);
            cout << " " << player[0].playersCard[1].getName(active[1][0]) << "   \t"; newCard(1, 0, 0);
            cout << " " << player[0].playersCard[2].getName(active[2][0]) << "   \t"; newCard(2, 0, 0);
            cout << " " << player[0].playersCard[3].getName(active[3][0]) << "   \t"; newCard(3, 0, 0);
            cout << " " << player[0].playersCard[4].getName(active[4][0]) << "   \t"; newCard(4, 0, 0);
        }

        void newCard(int r, int j, int p) {
            for (j; j <= i; j++) {
                string row[] = {"┌─ ─ ─┐ ", "|" + player[p].playersCard[j].letter + "    | ",
                                "|  " + player[p].playersCard[j].symbol + "  | ", 
                                "|    " + player[p].playersCard[j].letter + "| ", "└─ ─ ─┘ "};
                string newStr = "";
                if (active[j][p]) 
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

        void winCondition() {
            if (stand[0] == true && stand[1] == true)
        } 
};

int main() {
    string name;
    double money;
    Game game;

    cout << " Name: ";
    getline(cin, name);
    cout << " Bet: $";
    cin >> money;

    game.gameInfo(name, money);
    game.play();

    return 0;
}