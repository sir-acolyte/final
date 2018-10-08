#include <iostream>
#include "Blackjack.h"

using namespace std;

int main()
{
	int game = 0;

	cout << "\n--------------\n";
	cout << "  CARD GAMES\n";
	cout << "--------------\n";
	//Game list
	cout << "\n  1 - Blackjack\n  2 - Texas Hold'em\n";
	cout << "\nPick a game to play: ";
	//Choose game
	cin >> game;

	if (game == 1) {
		//If user chooses 1 - Blackjack, launch blackjack main function
		blackjack();
	}
	else if (game == 2) {
		//if user chooses 2 - Texas Hold'em, launch texas holdem main function
		//texas();
	}
	else {
		return 0;
	}

	return 0;
}