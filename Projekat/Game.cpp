#include "Game.h"
#include "Error30.h"
#include <algorithm>
#include <string>
#include <vector>

Game::Game(string name) {
	if (name.length() > 30) {
		throw Error30();
	}
	this->name = name;
}

string Game::getName() {
	return name;
}

int Game::getResult(int value) {
	for (int i = 0; i < results.size(); i++) {
		if (results[i] == value) {
			return results[i];
		}
	}
	cout << "Result doesn't exist" << endl;
	return 0;
}

void Game::addResult(int result) {
	results.push_back(result);
}

void Game::sortResults() {
	sort(results.begin(), results.end());
}

void Game::sortResultsReverse() {
	sort(results.rbegin(), results.rend());
}

void Game::runGame() {
	cout << "Your game is starting " << name << endl;
}

void Game::setBalance(double balance) {
	this->balance = balance;
}

void Game::dataOutput() {
	cout << "Game: " << name << endl;
	cout << "Results: " << endl;
	cout << "Balance: " << balance << endl;
}