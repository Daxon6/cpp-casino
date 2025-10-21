#include "Score.h"

Score::Score() {
	result = 0;
}

Score::Score(Player player, int result) {
	player = player;
	result = result;
}

int Score::getResult() {
	return result;
}

Player Score::getPlayer() {
	return player;
}

void Score::setResult(int result) {
	result = result;
}

void Score::setPlayer(Player player) {
	player = player;
}

ostream& operator << (ostream& output, Score score) {
	output << "Player: " << score.player << endl;
	output << "Result: " << score.result << endl;
	return output;
}