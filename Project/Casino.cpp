#include <iostream>
#include "Casino.h"

Casino::Casino(int startingBudget) {
	budget = startingBudget;
}

int Casino::getBudget() {
	return budget;
}

void Casino::addGame(string game) {
	games.push_back(game);
}

void Casino::gameList() {
	for (int i = 0; i < games.size(); i++) {
		cout << i + 1 << ": " << games[i] << endl;
	}
}

void Casino::increaseBalance(int amount) {
	budget += amount;
}
