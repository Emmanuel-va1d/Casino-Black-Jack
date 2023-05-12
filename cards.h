#ifndef CARDS_H
#define CARDS_H
#include <iostream>
using namespace std;

class cards {
    private:
        int test;
    public:
        cards(int test) {
            this->test = test;
            cout << test;
        }
};
#endif