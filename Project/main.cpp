#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Error.h"
#include "Error30.h"
#include "Error80.h"
#include "Game.h"
#include "Player.h"
#include "Score.h"
#include "Casino.h"
#include "Pseudoroulette.h"
#include "Blackjack.h"
#include <vector>
using namespace std;

void displayMenu();
void playRoulette(Player& player);
void playBlackjack(Player& player);
Casino casino(500);

int main() {
	srand(time(0));
	string name;
	double balance;
	char choice;
	bool running = true;

	cout << "Enter your name: ";
	getline(cin, name);
	cout << "Enter your balance: ";
	cin >> balance;

	Player player(name, balance);

	casino.addGame("Roulette");
	casino.addGame("Blackjack");

	while (running) {
		displayMenu();

		int gameChoice;
		cout << "Select a game: ";
		cin >> gameChoice;

		switch (gameChoice) {
		case 1:
			playRoulette(player);
			break;
		case 2:
			playBlackjack(player);
			break;
		default:
			cout << "Please pick a valid game." << endl;
			break;
		}

		cout << "Game ended. Would you like to return to the main menu? (y/n) ";
		cin >> choice;

		if (choice == 'n') {
			running = false;
		}
	}

	cout << "Thanks for playing!" << endl;
	return 0;
}

void displayMenu() {
	cout << "Available games:" << endl;
	casino.gameList();
}

void playRoulette(Player& player) {
	// Prevent playing when player has no usable balance
	if (player.getBalance() <= 0) {
		cout << "Insufficient balance to play Roulette." << endl;
		return;
	}

	PseudoRoulette roulette;
	int guess = 0;
	int bet = 0;
	int choice;
	char guessColor = '\0';
	bool choseNumber = false;
	bool choseColor = false;

	cout << "Guess a number or a color on the roulette! (1/2) : ";
	cin >> choice;

	if (choice == 1) {
		cout << "Guess a number (0-36): " << endl;
		cin >> guess;
		choseNumber = true;
	}
	else {
		cout << "Guess a color (r/b): " << endl;
		cin >> guessColor;
		choseColor = true;
	}

	cout << "Enter the bet amount: " << endl;
	cin >> bet;

	// Validate bet
	if (bet <= 0) {
		cout << "Bet must be a positive amount." << endl;
		return;
	}
	if (bet > player.getBalance()) {
		cout << "Insufficient balance!" << endl;
		return;
	}

	if (choseNumber) {
		if (guess < 0 || guess > 36) {
			cout << "Number out of bounds. Please bet on 0..36." << endl;
			return;
		}
	}

	// Deduct bet after all validation
	player.setBalances(player.getBalance() - bet);

	// Generate outcome once and compute derived info
	int outcome = roulette.generateOutcome();
	roulette.colorCheck();
	roulette.even();

	cout << "Roulette outcome: " << outcome << " (color: " << roulette.color << ")" << endl;

	// Resolve bets:
	if (choseNumber) {
		if (guess == outcome) {
			cout << "Congratulations! You guessed the correct number!" << endl;
			// pay 35:1
			player.setBalances(player.getBalance() + bet * 35);
		}
		else {
			cout << "Unfortunately, you didn't guess the correct number." << endl;
		}
	}
	else if (choseColor) {
		// Validate color input
		if (guessColor != 'r' && guessColor != 'b' && guessColor != 'g') {
			cout << "Invalid color choice. Use 'r' for red, 'b' for black, 'g' for green." << endl;
		}
		else if (guessColor == roulette.color) {
			cout << "Congratulations! You guessed the right color!" << endl;
			// pay 2:1 
			player.setBalances(player.getBalance() + bet * 2);
		}
		else {
			cout << "Unfortunately, you didn't guess the right color." << endl;
		}
	}
	else {
		cout << "No valid bet type selected." << endl;
	}

	cout << "Your balance is: " << player.getBalance() << endl;
}

void playBlackjack(Player& player) {
	Blackjack blackjack;
	vector<int> dealerCards;
	vector<int> playerCards;

	int dealerFirstCard = blackjack.pickACard();
	dealerCards.push_back(dealerFirstCard);
	int dealerHiddenCard = blackjack.pickACard();
	dealerCards.push_back(dealerHiddenCard);

	int playerFirstCard = blackjack.pickACard();
	int playerSecondCard = blackjack.pickACard();
	playerCards.push_back(playerFirstCard);
	playerCards.push_back(playerSecondCard);

	int bet;
	cout << "Enter bet amount: ";
	cin >> bet;

	if (bet > player.getBalance()) {
		cout << "Insufficient balance!" << endl;
		return;
	}

	cout << "Dealer pulls " << dealerFirstCard << " and deals you " << playerFirstCard << " and " << playerSecondCard << "." << endl;

	player.setBalances(player.getBalance() - bet);

	// Player turn
	char choice;
	bool playerBust = false;
	while (true) {
		int playerTotal = blackjack.calculateHandTotal(playerCards);
		cout << "Your hand: " << playerTotal << endl;
		cout << "Hit or stand? (h/s) : ";
		cin >> choice;

		if (choice == 'h') {
			int newCard = blackjack.pickACard();
			playerCards.push_back(newCard);
			int newTotal = blackjack.calculateHandTotal(playerCards);
			cout << "Dealer deals you " << newCard << "." << endl;
			if (newTotal > 21) {
				cout << "It's a bust!" << endl;
				playerBust = true;
				break;
			}
		}
		else if (choice == 's') {
			break;
		}
		else {
			cout << "Error. Please choose 'h' to hit or 's' to stand." << endl;
		}
	}

	// Dealer turn
	if (!playerBust) {
		cout << "Dealer reveals hidden card: " << dealerHiddenCard << endl;

		int dealerTotal = blackjack.calculateHandTotal(dealerCards);
		while (dealerTotal < 17) {
			int newCard = blackjack.pickACard();
			dealerCards.push_back(newCard);
			cout << "Dealer pulls " << newCard << "." << endl;
			dealerTotal = blackjack.calculateHandTotal(dealerCards);
			if (dealerTotal > 21) break;
		}

		int playerTotal = blackjack.calculateHandTotal(playerCards);
		int finalDealerTotal = blackjack.calculateHandTotal(dealerCards);

		cout << "Dealer's total: " << finalDealerTotal << endl;

		if (finalDealerTotal > 21) {
			cout << "Dealer busts! You win!" << endl;
			player.setBalances(player.getBalance() + bet * 2);
		}
		else if (finalDealerTotal > playerTotal) {
			cout << "Dealer wins with " << finalDealerTotal << "!" << endl;
		}
		else if (finalDealerTotal < playerTotal) {
			cout << "You win with " << playerTotal << "!" << endl;
			player.setBalances(player.getBalance() + bet * 2);
		}
		else {
			cout << "It's a tie!" << endl;
			player.setBalances(player.getBalance() + bet);
		}
	}
	else {
		cout << "Game over! Dealer wins." << endl;
	}

	cout << "Balance: " << player.getBalance() << endl;
}
