#include "Blackjack.h"
#include "Console.h"
#include <iostream>
#include <thread>
#include <Windows.h>
#include <Mmsystem.h>
#pragma comment(lib, "winmm.lib")

using namespace std;

void playMusic() {
	while (true) {
		//PlaySound(TEXT("files\\test.wav"), NULL, SND_LOOP);
	}
}

int main()
{
	//set console size and title
	setConsoleSize(400, 500);
	setConsoleTitle("Blackjack");
	setConsoleColor("purple");
	cout << "\n-------------\n";
	cout << "  BLACKJACK\n";
	cout << "-------------\n";
	setConsoleColor("white");

	//thread t1(playMusic);

	//call game function
	blackjack();

	cout << "\nExiting...";
	Sleep(1000);

	return 0;
}