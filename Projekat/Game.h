#pragma once
#include "Player.h"
#include "Score.h"
#include <algorithm>
#include <iostream>
#include <vector>
class Game {
protected:
	string name;
	vector<int> results;
	double balance;
public:
	Game(string name);
	string getName();
	int getResult(int value);
	void addResult(int result);
	void sortResults();
	void sortResultsReverse();
	void runGame();
	void setBalance(double balance);
	void dataOutput();
	friend ostream& operator << (ostream& output, Game player);
	Game() {}
};