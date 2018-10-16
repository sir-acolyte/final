#include <iostream>
#include "Blackjack.h"
#include "Console.h"

using namespace std;

int main()
{
	int game = 0;
	
	setConsoleSize(450, 800);

	setConsoleColor("purple");
	cout << "\n--------------\n";
	cout << "  CARD GAMES\n";
	cout << "--------------\n";
	setConsoleColor("white");
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

	system("pause");

	return 0;
}