#pragma once
#include <cstdlib>
#include <time.h>
#include "Game.h"
#include "Score.h"
class PseudoRoulette : public Game, public Score {
	int outcome;
public:
	char a;
	char color;
	bool evenNumber;
	int arr[37];
	PseudoRoulette() {
		outcome = 0;
	}
	PseudoRoulette(int outcome);
	void even();
	void colorCheck();
	void operator+= (int number);
	int operator[] (int number);
	void operator*= (char color);
	bool operator /= (Score&);
	bool operator-=(Player&);
	Player& operator+ (Player&);
	void gameStart();
	int generateOutcome();
};