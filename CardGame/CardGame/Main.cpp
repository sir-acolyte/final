#include <iostream>
#include "Blackjack.h"

using namespace std;

int main()
{
	int game = 0;
	
	cout << " _____\n|A .  |\n| /.\\ |\n|(_._)|\n|  |  |\n|_____|";
	cout << "\n--------------\n";
	cout << "  CARD GAMES\n";
	cout << "--------------\n";
	//Game list
	cout << "\n  1 - Blackjack\n";
	cout << "\nPick a game to play: ";
	//Choose game
	cin >> game;

	//clear screen
	system("cls");

	if (game == 1) {
		//If user chooses 1 - Blackjack, launch blackjack main function
		blackjack();
	}
	else {
		//if user chooses anything else exit program
		return 0;
	}

	return 0;
}