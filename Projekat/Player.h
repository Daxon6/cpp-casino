#pragma once
#include <iostream>
#include <string>
#include "Error.h"
using namespace std;
static int id = 1;
class Player {
private:
	string name;
	double balance;
public:
	Player();
	Player(string, double);
	Player(Player&, int);
	int getId();
	string getime();
	void setBalances(int balances);
	double getBalance();
	friend istream& operator >> (istream& input, Player& player);
	friend ostream& operator << (ostream&, Player player);
};