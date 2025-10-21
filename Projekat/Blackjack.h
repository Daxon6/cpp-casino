#pragma once
#include "Game.h"
#include <time.h>
#include <vector>

class Blackjack {
protected:
	int deck[52];
	int hand[9];
	int result;
	int balance;
public:
	Blackjack();
	void start();
	void calculateResult(int card);
	int pickACard();
	int getResult();
	int getBalance();

	// Returns basic face value: 2-10 -> 2..10, J/Q/K -> 10, Ace -> 1
	static int cardFaceValue(int card);

	// Calculate best hand total for a vector of cards (Aces as 1 or 11)
	int calculateHandTotal(const std::vector<int>& cards);
};
