#include "PseudoRoulette.h"

PseudoRoulette::PseudoRoulette(int outcome) {
	// initialize member properly
	this->outcome = outcome;

	// initialize full range 0..36
	for (int i = 0; i < 37; i++) {
		arr[i] = 0;
	}

	color = 'r';
	balance = 0;
	evenNumber = false;
}

int PseudoRoulette::generateOutcome() {
	// DO NOT reseed here; seeding should be done once in main
	this->outcome = rand() % 37; // 0..36
	return this->outcome;
}

void PseudoRoulette::even() {
	// treat 0 as special (not counted as even bet)
	if (this->outcome == 0) {
		evenNumber = false;
		return;
	}

	if (this->outcome % 2 == 0) {
		evenNumber = true;
	}
	else {
		evenNumber = false;
	}
}

void PseudoRoulette::colorCheck() {
	// 0 is typically green in roulette
	if (outcome == 0) {
		color = 'g';
		return;
	}

	if (outcome >= 1 && outcome <= 10) {
		if (outcome % 2 == 1) {
			color = 'r';
		}
		else {
			color = 'b'; // black
		}
	}
	else if (outcome >= 11 && outcome <= 18) {
		if (outcome % 2 == 0) {
			color = 'r';
		}
		else {
			color = 'b';
		}
	}
	else if (outcome >= 19 && outcome <= 28) {
		if (outcome % 2 == 1) {
			color = 'r';
		}
		else {
			color = 'b';
		}
	}
	else if (outcome >= 29 && outcome <= 36) {
		if (outcome % 2 == 0) {
			color = 'r';
		}
		else {
			color = 'b';
		}
	}
}
//Setting elements in an array
void PseudoRoulette::operator+= (int broj) {
	if (broj >= 0 && broj <= 36) arr[broj] = 1;
}
//Accessing an element from the array
int PseudoRoulette::operator[](int broj) {
	if (broj >= 0 && broj <= 36) return arr[broj];
	return 0;
}
//Color set
void PseudoRoulette::operator*=(char color) {
	this->color = color;
}
//Setting an even number
bool PseudoRoulette::operator/=(Score& score) {
	return evenNumber = true;
}
//Deleting an even number
bool PseudoRoulette::operator-=(Player& player) {
	return evenNumber = false;
}
//Player balance change
Player& PseudoRoulette::operator+(Player& player) {
	player.setBalances(player.getBalance() + 1);
	return player;
}

void PseudoRoulette::gameStart() {
	generateOutcome();
	even();
	colorCheck();
}