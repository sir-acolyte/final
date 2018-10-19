#include "Blackjack.h"
#include "Console.h"
#include <iostream>

using namespace std;

int main()
{
	//set console size and title
	setConsoleSize(400, 500);
	setConsoleTitle("Blackjack");
	setConsoleColor("purple");
	cout << "\n--------------\n";
	cout << "  BLACKJACK\n";
	cout << "--------------\n";
	setConsoleColor("white");

	//call game function
	blackjack();

	cout << "\nExiting...";
	Sleep(1000);

	return 0;
}