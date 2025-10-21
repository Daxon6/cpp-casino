#pragma once
#include <iostream>
#include <string>
#include "Player.h"
using namespace std;
class Score {
public:
	int result;
	Player player;
	Score();
	Score(Player, int);
	int getResult();
	Player getPlayer();
	void setResult(int);
	void setPlayer(Player);
	friend ostream& operator << (ostream&, Score);
};