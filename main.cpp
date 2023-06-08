#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
using namespace std;

/* arrays holding card values, names and suit */
const int VALUES[] = {11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10};
const string LETTER[] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "T", "K", "Q", "J"};
const string SYMBOL[] = {"\u2660", "\u2663", "\u2665", "\u2666"};
const string NAMES[] = {"ACE", "TWO", "THREE", "FOUR", "FIVE", 
                        "SIX", "SEVEN", "EIGHT", "NINE", "TEN", 
                        "KING", "QUEEN", "JACK"};
const string SUIT[] = {"SPADES", "CLUBS", "HEARTS", "DIAMOND"};
const double ADV[] = {9.8, 13.4, 18.0, 23.2, 23.9, 14.3, 5.4, -4.3, -16.9, -16.9, -16.9, -16.9, -16.0};

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
        vector<Card> dealtCards;
        bool repeats = false;
    public:
        Card getHand() {
            Card hand;
            do {
                hand = card[rand() % 4][rand() % 13];
                for (int i = 0; i < dealtCards.size(); i++) {
                    if (dealtCards[i].suit == hand.suit && dealtCards[i].name == hand.name)
                        repeats = true;
                }
            } while (repeats);
            dealtCards.push_back(hand);

            return hand;
        }
        double probability(int count) {
            int remainingCards = 52 - dealtCards.size();
            int favorableOutcomes = 0;
            for (int suit = 0; suit < 4; suit++) {
                for (int rank = 0; rank < 13; rank++) {
                    Card simulatedCard = card[suit][rank];
                    if (!isCardDealt(simulatedCard)) {
                        int simulatedCount = count + simulatedCard.value;
                        if (simulatedCount == 21)
                            favorableOutcomes++;
                    }
                }
            }
            double probability = static_cast<double>(favorableOutcomes) / remainingCards * 100;
            return probability;
        }
        bool isCardDealt(Card card) {
            for (int i = 0; i < dealtCards.size(); i++) {
                if (dealtCards[i].suit == card.suit && dealtCards[i].name == card.name)
                    return true;
            }
            return false;
        }
        Deck() {
            srand(static_cast <int>(time(0)));
            dealtCards.reserve(52);
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
        int choice;
        bool playing = true;
        bool stand[2] = {false, true};
        bool active[5][2] = {{true, true}, {true, true}, {false, false}, 
                            {false, false}, {false, false}};
        int i[2] = {1, 1};
    public:
        void gameInfo(string name, double money) {
            player[0].playerName = name;
            player[0].playerBet = money;
            player[1].playerName = "Dealer";
            player[1].playerBet = (rand() % 9 + 1) * 12321;
            do {
                cout << " " << name << ", Play(1) or Quit(2) ";
                cin >> choice;
            } while (choice != 1 && choice != 2);
            if (choice == 1) playing = true;
            else playing = false;
            system("clear");
        }
        
        void play() {
            player[0].playersCard[0] = deck.getHand();
            player[0].playersCard[1] = deck.getHand();
            player[1].playersCard[0] = deck.getHand();
            player[1].playersCard[1] = deck.getHand();
            while (playing) {
                system("clear");
                dealerHand();
                playerHand();
                if (count(0, 0) == 21)
                    stand[0] = true;
                if (stand[0] == false) {
                    do {
                        cout << " Hit(1) or Stand(2) ";
                        cin >> choice;
                    } while (choice != 1 && choice != 2);
                }
                if (choice == 1) {
                    i[0]++;
                    i[1]++;
                    active[i[0]][0] = true;
                    player[0].playersCard[i[0]] = deck.getHand();
                }
                else {
                    stand[0] = true;
                    stand[1] = false;
                }
                if (count(0, 1) < 17 && stand[1] == false) {
                    if (choice == 2)
                        i[1]++;
                    player[1].playersCard[i[1]] = deck.getHand();
                    active[i[1]][1] = true;
                }
                else 
                    stand[1] = true;
                winCondition();
            }
        }
        void dealerHand() {
            cout << "\n\n\t" << player[1].playerName << "'s HAND\t\t\n\n";
            cout << " Cards\t\tCount: " << count(1, 1);
            cout << "\tBet: $" << player[1].playerBet << "\n\t\t\t┌─ ─ ─┐\n";
            cout << " " << player[1].playersCard[1].getName(active[1][1]) << "   \t|  "; newCard(0, 1, 1);
            cout << " " << player[1].playersCard[2].getName(active[2][1]) << "   \t|  "; newCard(1, 1, 1);
            cout << " " << player[1].playersCard[3].getName(active[3][1]) << "   \t|  "; newCard(2, 1, 1);
            cout << " " << player[1].playersCard[4].getName(active[4][1]) << "   \t└─-"; newCard(3, 1, 1);
            cout << "\t\t\t   "; newCard(4, 1, 1);
        }
        void playerHand() {
            cout << "\n\n\t" << player[0].playerName << "'s HAND\t\t\n\n";
            cout << " Cards\t\tCount: " << count(0, 0);
            cout << "\tBet: $" << player[0].playerBet;
            cout << " \tAdv.: " << playerAdvantage() << endl;
            cout << " " << player[0].playersCard[0].getName(active[0][0]) << "   \t"; newCard(0, 0, 0);
            cout << " " << player[0].playersCard[1].getName(active[1][0]) << "   \t"; newCard(1, 0, 0);
            cout << " " << player[0].playersCard[2].getName(active[2][0]) << "   \t"; newCard(2, 0, 0);
            cout << " " << player[0].playersCard[3].getName(active[3][0]) << "   \t"; newCard(3, 0, 0);
            cout << " " << player[0].playersCard[4].getName(active[4][0]) << "   \t"; newCard(4, 0, 0);
            cout << setprecision(2) << " Probability: " << deck.probability(count(0, 0)) << "%\n";
            cout << setprecision(0) << fixed;
        }

        void newCard(int r, int j, int p) {
            for (j; j <= i[p]; j++) {
                string row[] = {"┌─ ─ ─┐ ", "|" + player[p].playersCard[j].letter + "    | ",
                                "|  " + player[p].playersCard[j].symbol + "  | ", 
                                "|    " + player[p].playersCard[j].letter + "| ", "└─ ─ ─┘ "};
                string newStr = "";
                if (active[j][p]) 
                    newStr += row[r];
                cout << newStr;
                if (j == i[p])
                    cout << endl;
            }
        }

        int count(int j, int p) {
            int value = 0;
            int A = 0;
            bool hasAce = false;
            for (j; j <= i[p]; j++) {
                if (player[p].playersCard[j].value == 11)
                    A++;
                value += player[p].playersCard[j].value;
            }
            while (A != 0) {
                if (value > 21)
                    value -= 10;
                A--;
            }
            return value;
        }

        void winCondition() {
            if (stand[0] == true && stand[1] == true || count(0, 0) > 21 || count(1, 1) > 21) {
                system("clear");
                if (count(0, 0) > count(0, 1) && count(0, 0) <= 21 || count(0, 1) > 21 && count(0, 1) > 21 ) {
                    player[1].playerBet -= player[0].playerBet * 0.5;
                    player[0].playerBet *= 1.5;
                    cout << "\n\t\tYOU WIN! ";
                }
                else if (count(0, 0) < count(0, 1) && count(0, 1) <= 21 || count(0, 0) > 21 && count(0, 1) <= 21) {
                    player[1].playerBet += player[0].playerBet;
                    player[0].playerBet = 0;
                    cout << "\n\t\tYOU LOSE! ";
                }
                else
                    cout << "\n\t\tTIE ";
                for (int j = 1; j >= 0; j--) {
                    cout << "\n\n\t" << player[j].playerName << "'s CARDS\t\t\n\n";
                    cout << " Cards\t\t\tCount: " << count(0, j);
                    cout << "\t\tBet: $" << player[j].playerBet << endl;
                    cout << " " << player[j].playersCard[0].getName(active[0][j]) << "   \t"; newCard(0, 0, j);
                    cout << " " << player[j].playersCard[1].getName(active[1][j]) << "   \t"; newCard(1, 0, j);
                    cout << " " << player[j].playersCard[2].getName(active[2][j]) << "   \t"; newCard(2, 0, j);
                    cout << " " << player[j].playersCard[3].getName(active[3][j]) << "   \t"; newCard(3, 0, j);
                    cout << " " << player[j].playersCard[4].getName(active[4][j]) << "   \t"; newCard(4, 0, j);
                }
                do {
                    cout << " " << player[0].playerName << ", Play(1) or Quit(2) ";
                    cin >> choice;
                } while (choice != 1 && choice != 2);
                if (choice == 1) {
                    if (player[1].playerBet == 0) {
                        system("clear");
                        cout << " Come again";
                        playing = false;
                    }
                    else if (player[0].playerBet == 0) {
                        system("clear");
                        cout << " Bet: $";
                        cin >> player[0].playerBet;
                        reset();
                    }
                    else
                        reset();
                }
                else
                    playing = false;
            }
        }
        void reset() {
            player[0].playersCard[0] = deck.getHand();
            player[0].playersCard[1] = deck.getHand();
            player[1].playersCard[0] = deck.getHand();
            player[1].playersCard[1] = deck.getHand();
            stand[0] = false;
            stand[1] = true;
            for (int i = 2; i < 6; i++) {
                for (int j = 0; j < 2; j++)
                    active[i][j] = false;
            }
            i[0] = 1;
            i[1] = 1;   
        }
        double playerAdvantage() {
            double adv = 0;
            for (int i = 0; i < 13; ++i) {
                if (player[1].playersCard[1].value == VALUES[i]) {
                    if (VALUES[i] == 11)
                        adv = -16.0f;
                    else if (VALUES[i] == 8)
                        adv = -16.9f;
                    else
                        adv = ADV[i - 1];
                }
            }
        return adv;
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