#pragma once
#include "Game.h"
#include "Player.h"
#include <vector>
#include <string>
using namespace std;
class Casino {
protected:
	vector<string> games;
	int balance;
	int budget;
public:
	Casino(int startingBudget);
	int getBudget();
	void addGame(string game);
	void gameList();
	void increaseBalance(int amount);
	void gameStart(string game, int balance);
};