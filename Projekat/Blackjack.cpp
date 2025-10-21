#include "Blackjack.h"
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

Blackjack::Blackjack() {
	start();
	result = 0;
	balance = 0;
	srand(time(0));
}

void Blackjack::start() {
	int card = 1;
	for (int i = 0; i < 52; i++) {
		if (i % 4 == 0 && i != 0) {
			card++;
		}
		deck[i] = card;
	}
	random_shuffle(deck, deck + 52);
}

void Blackjack::calculateResult(int card) {
	// kept for compatibility, but prefer calculateHandTotal for multi-card hands
	if (card >= 2 && card <= 10) {
		result += card;
	}
	else if (card >= 11 && card <= 13) {
		result += 10;
	}
	else if (card == 1) {
		// treat Ace as 11 if it doesn't bust, otherwise 1
		if (result + 11 > 21) result += 1;
		else result += 11;
	}
}

int Blackjack::pickACard() {
	int card = deck[0];
	for (int i = 0; i < 51; i++) {
		deck[i] = deck[i + 1];
	}
	deck[51] = 0;
	return card;
}

int Blackjack::getResult() {
	return result;
}

int Blackjack::getBalance() {
	return balance;
}

int Blackjack::cardFaceValue(int card) {
	if (card >= 2 && card <= 10) return card;
	if (card >= 11 && card <= 13) return 10;
	// Ace
	return 1;
}

int Blackjack::calculateHandTotal(const std::vector<int>& cards) {
	int sum = 0;
	int aces = 0;
	for (int c : cards) {
		if (c == 1) {
			aces++;
			sum += 1; // count Ace as 1 for now
		} else {
			sum += cardFaceValue(c);
		}
	}
	// Try to upgrade aces from 1 to 11 (adds +10) while not busting
	for (int i = 0; i < aces; ++i) {
		if (sum + 10 <= 21) sum += 10;
		else break;
	}
	return sum;
}
