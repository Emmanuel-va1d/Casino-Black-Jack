# Casino Black Jack

## Simulation of the popular card game known as Black Jack

This project is in part of my CIS-7 Discrete Structures class. I will be implementing what I learned about data structures, probabilty and algorithms in this project

# How to Play
A blackjack game has a dealer and one or more players. Each player plays against the dealer. All players
are initially dealt two cards and the dealer is dealt one card face down and one face up (these are called
the hole card and up card respectively). Each player can then hit (ask for an additional card) until her
total exceeds 21 (this is called busting) or she decides to stand (stop taking cards for the rest of the
hand). Face cards count as 10 and an ace may be counted as 1 or 11. After all of the players have
finished, the dealer reveals the hole card and plays the hand with a fixed strategy: hit on 16 or less and
stand on 17 or more.
The player loses if they busts and wins if they do not bust and the dealer does (if both the
player and the dealer bust, the player loses). Otherwise, the player wins if her total is closer to 21 than
the dealer's. If the player wins, she gets twice her bet; if she loses, she loses her money. If the dealer and
player tie it is called a "push;" the player keeps her bet but does not earn any additional money. If the
player's first two cards total 21, this is a blackjack and she wins 1.5 times her bet (unless the dealer also
has a blackjack, in which case a tie results), so she gets back 2.5 times her bet