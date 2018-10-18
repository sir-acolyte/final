#include "Blackjack.h"
#include "Console.h"
#include <iostream>

using namespace std;

int main()
{
	int game = 0;
	//set console size and title
	setConsoleSize(400, 500);
	setConsoleFontSize(16);
	setConsoleTitle("Blackjack");
	//text formatting and printing out
	setConsoleColor("purple");
	cout << "\n--------------\n";
	cout << "  CARD GAMES\n";
	cout << "--------------\n";
	setConsoleColor("white");
	//Game start
	cout << "\n  1 - Blackjack\n";
	setConsoleColor("cyan");  cout << "\nPick a game to play: "; setConsoleColor("white");
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

	cout << "\nExiting...";
	Sleep(1000);

	return 0;
}