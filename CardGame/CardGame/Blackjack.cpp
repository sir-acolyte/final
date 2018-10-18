#include <vector> 
#include <iostream>
#include "Deck.h"
#include "Console.h"

using namespace std;

//global deck variables so all functions can access them
Deck cardDeck;
Deck playerDeck(0);
Deck dealerDeck(0);
//global betting variable so all functions can access it (e.g. youLose(bet))
int money = 250;

//makes jacks, kings, and queens = 10 for blackjack
void convertDeck() {
	//temporary variable to hold deck array
	vector<Card> tempDeck = cardDeck.getDeck();

	//changes cards greater that 10 to equal 10
	for (int i = 0; i < cardDeck.getSize(); i++) {
		if (tempDeck[i].getNumber() > 10) {
			tempDeck[i].setNumber(10);
		}
	}

	//updates the deck with the modified one
	cardDeck.updateDeck(tempDeck);
}

string getPlayerHand() {
	vector<Card> tempDeck = playerDeck.getDeck();
	string cards = "";
	for (int i = 0; i < playerDeck.getSize(); i++) {
		cards += tempDeck[i].getFront() + "\n";
	}
	return cards;
}

string getDealerHand() {
	vector<Card> tempDeck = dealerDeck.getDeck();
	string cards = "";
	for (int i = 0; i < dealerDeck.getSize(); i++) {
		cards += tempDeck[i].getFront() + "\n";
	}
	return cards;
}

void dealPlayerCards(int num) {
	vector<Card> tempDeck = playerDeck.getDeck();
	for (int i = 0; i < num; i++) {
		Card tempCard = cardDeck.takeCard(i);
		tempDeck.insert(tempDeck.begin() + i, tempCard);
		playerDeck.addCard(i, tempDeck[i]);
	}
}

void dealDealerCards(int num) {
	vector<Card> tempDeck = dealerDeck.getDeck();
	for (int i = 0; i < num; i++) {
		Card tempCard = cardDeck.takeCard(i);
		tempDeck.insert(tempDeck.begin() + i, tempCard);
		dealerDeck.addCard(i, tempDeck[i]);
	}
}

void youWin(int bet) {
	//resize and clear screen
	system("cls");
	setConsoleSize(400, 465);

	setConsoleColor("green"); cout << "\n  -----------\n    YOU WIN\n  -----------\n" << endl; setConsoleColor("yellow");
	cout << "  ___________\n '._==_==_=_.'\n .-\\:      /-.\n| (|:.     |) |\n '-|:.     |-'\n   \\::.    /\n    '::. .'\n      ) (\n    _.' '._\n   `~~~~~~~`" << endl; setConsoleColor("white");
	cout << "\nYou had a total of "; setConsoleColor("purple"); cout << playerDeck.totalValue(); setConsoleColor("white"); cout << " and the \ndealer had a total of "; setConsoleColor("purple"); cout << dealerDeck.totalValue() << ".\n"; setConsoleColor("white");
	money += bet * 2;
	setConsoleColor("white"); cout << "\nYou now have "; setConsoleColor("purple"); cout << money; setConsoleColor("white"); cout << " dollars." << endl;
}

void youLose(int bet) {
	//resize and clear screen
	system("cls");
	setConsoleSize(400, 465);

	setConsoleColor("red"); cout << "\n  ------------\n    YOU LOSE\n  ------------\n" << endl; setConsoleColor("white");
	cout << "You had a total of "; setConsoleColor("purple"); cout << playerDeck.totalValue(); setConsoleColor("white"); cout << " and the \ndealer had a total of "; setConsoleColor("purple"); cout << dealerDeck.totalValue() << ".\n"; setConsoleColor("white");
	money -= bet;
	setConsoleColor("white"); cout << "\nYou now have "; setConsoleColor("purple"); cout << money; setConsoleColor("white"); cout << " dollars." << endl;
}

void autoResize(boolean displayHand) {
	int defaultSize = 410;
	if (displayHand) {
		for (int i = 0; i < playerDeck.getSize() + dealerDeck.getSize(); i++) {
			setConsoleSize(400, i * 105 + (defaultSize - 100));
		}
	}
	else {
		for (int i = 0; i < playerDeck.getSize(); i++) {
			setConsoleSize(400, i * 105 + defaultSize);
		}
	}
}

void blackjack()
{
	//Initialize all variables here
	bool goAgain = false;
	bool hitStandLoop = true;
	bool dealerPart = false;
	char hitOrStand;
	char yesOrNo = 'Y';
	char displayHand = 'N';
	int bet = 0;

	//Do while loop to run at least once, then check at the end of the game if the user wants to go again
	do {
		//get deck ready for game start
		playerDeck.clearDeck();
		dealerDeck.clearDeck();
		cardDeck.initDeck();
		cardDeck.shuffleDeck();
		convertDeck();

		//clear screen from previous game, and resizes window
		system("cls");

		//Deal cards to dealer and player
		dealPlayerCards(2);
		dealDealerCards(2);
		string dealerFirstCard = dealerDeck.getCard(0).getFront();

		setConsoleSize(400, 540);
		//Print cards out to user
		setConsoleColor("purple"); cout << "\n-------------\n  YOUR HAND\n-------------\n"; setConsoleColor("white"); cout << getPlayerHand() << endl;
		setConsoleColor("purple"); cout << "\n---------------\n  DEALER HAND\n---------------\n"; setConsoleColor("white"); cout << dealerFirstCard << endl;
		//print total amount of money to user
		cout << "\nYou have "; setConsoleColor("purple"); cout << money; setConsoleColor("white"); cout << " dollars.";
		//ask user how much they would like to bet
		setConsoleColor("cyan"); cout << "\nEnter amount to bet >> "; setConsoleColor("white");
		cin >> bet;
		//makes sure user only enter and amount they can afford
		while (bet > money || bet < 0) {
			setConsoleColor("red"); cout << "\nInvalid amount."; setConsoleColor("white");
			cout << "\nYou have "; setConsoleColor("purple"); cout << money; setConsoleColor("white"); cout << " dollars.";
			//ask user how much they would like to bet
			setConsoleColor("cyan"); cout << "\nEnter amount to bet >> "; setConsoleColor("white");
			cin >> bet;
		}
		setConsoleTitle("Betting " + to_string(bet) + " dollars");
		
		//clear and resize screen
		system("cls");
		autoResize(false);
		//Print cards out to user
		setConsoleColor("purple"); cout << "\n-------------\n  YOUR HAND\n-------------\n"; setConsoleColor("white"); cout << getPlayerHand() << endl;
		setConsoleColor("purple"); cout << "\n---------------\n  DEALER HAND\n---------------\n"; setConsoleColor("white"); cout << dealerFirstCard << endl;
		
		while (hitStandLoop) {
			setConsoleColor("cyan"); cout << "\nHit (H) or Stand (S) >> "; setConsoleColor("white"); cin >> hitOrStand;
			hitOrStand = toupper(hitOrStand);
			switch (hitOrStand) {
			case 'H':
				//deal new card to player
				dealPlayerCards(1);

				//clear and resize the screen to keep things neat
				autoResize(false);
				system("cls");

				//print out new hand, and dealers first card again (in case they forgot)
				setConsoleColor("purple"); cout << "\n-------------\n  YOUR HAND\n-------------\n"; setConsoleColor("white"); cout << getPlayerHand() << endl;
				setConsoleColor("purple"); cout << "\n---------------\n  DEALER HAND\n---------------\n"; setConsoleColor("white"); cout << dealerFirstCard << endl;

				//check players hand for total amount
				//if greater than 21, bust, go to you lose method
				if (playerDeck.totalValue() > 21) {
					hitStandLoop = false;
					youLose(bet);
				} //if equal to 21, blackjack! go to you win method
				else if (playerDeck.totalValue() == 21) {
					hitStandLoop = false;
					youWin(bet);
				} //if none of the above, continue through loop normally
				else if (playerDeck.totalValue() < 21) {
					hitStandLoop = true;
				}
				break;
			case 'S':
				hitStandLoop = false;
				if (playerDeck.totalValue() > 21) {
					hitStandLoop = false;
					youLose(bet);
				}
				else if (playerDeck.totalValue() == 21) {
					hitStandLoop = false;
					youWin(bet);
				}
				else if (playerDeck.totalValue() < 21) {
					hitStandLoop = false;
					//player is eligible to go up against dealers hand now
					dealerPart = true;
				}
				break;
			default:
				cout << "That is not a valid response, please try again.\n";
			}
			//auto set console size based on how many cards are on screen
		}

		

		while (dealerPart) {
			//clear and resize screen
			system("cls");
			
			//check dealers hand, now that user is finished
			//if dealers hand is greater, immediate loss
			if (dealerDeck.totalValue() > playerDeck.totalValue() && dealerDeck.totalValue() <= 21) {
				dealerPart = false;
				youLose(bet);
			} //if the dealers hand is below 17, hit once
			else if (dealerDeck.totalValue() < 17 && dealerDeck.totalValue() <= 21) {
				dealDealerCards(1);

				//resize the screen to keep things neat

			} //if dealers hand is greater than or equal to 17, check dealers hand against players
			else if (dealerDeck.totalValue() >= 17 && dealerDeck.totalValue() <= 21) {
				if (dealerDeck.totalValue() > playerDeck.totalValue()) {
					youLose(bet);
				}
				else if (dealerDeck.totalValue() == playerDeck.totalValue()) {
					youLose(bet);
				}
				else {
					youWin(bet);
				}
				dealerPart = false;
			} //if the dealer busts, immediate win for the user
			else if (dealerDeck.totalValue() > 21) {
				dealerPart = false;
				youWin(bet);
			}
			else if (dealerDeck.totalValue() == playerDeck.totalValue()) {
				youLose(bet);
			}
		}

		setConsoleColor("cyan"); cout << "\nDisplay hand (Y/N)? >> "; setConsoleColor("white"); cin >> displayHand;
		displayHand = toupper(displayHand);
		switch (displayHand) {
		case 'Y':
			system("cls");
			autoResize(true);

			setConsoleColor("purple"); cout << "\n-------------\n  YOUR HAND\n-------------\n"; setConsoleColor("white"); cout << getPlayerHand() << endl;
			setConsoleColor("purple"); cout << "\n---------------\n  DEALER HAND\n---------------\n"; setConsoleColor("white"); cout << getDealerHand() << endl;
			break;

		case 'N':
			break;
		default:
			cout << "\nInvalid answer, exiting...";
			goAgain = false;
		}

		setConsoleColor("cyan"); cout << "\nPlay again (Y/N)? >> "; setConsoleColor("white"); cin >> yesOrNo;
		yesOrNo = toupper(yesOrNo);
		switch (yesOrNo) {
		case 'Y':
			goAgain = true;
			break;
		case 'N':
			goAgain = false;
			break;
		default:
			cout << "\nInvalid answer, exiting...";
			goAgain = false;
		}

		dealerPart = false;
		hitStandLoop = true;
	} while (goAgain);
}