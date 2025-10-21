#include "Player.h"
#include "Error80.h"

Player::Player() {
	name = "";
	balance = 0;
}

Player::Player(string name, double balance) {
	if (name.length() > 80) {
		throw Error80();
	}
	this->name = name;
	this->balance = balance;
}

Player::Player(Player& player, int id) {
	id = id;
	name = player.name;
	balance = player.balance;
}

int Player::getId() {
	return id;
}

string Player::getime() {
	return string(name);
}

double Player::getBalance() {
	return balance;
}

void Player::setBalances(int balances) {
	balance = balances;
}

istream& operator >>(istream& input, Player& player) {
	input >> player.name;
	input >> player.balance;
	return input;
}

ostream& operator<<(ostream& output, Player player) {
	output << "ID: " << id++ << endl;
	output << "Ime igraca: " << player.name << endl;
	output << "Balans: " << player.balance << endl;
	return output;
}