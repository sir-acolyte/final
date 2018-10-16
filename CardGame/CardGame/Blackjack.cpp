#include <vector> 
#include "Deck.h"
#include "Console.h"

using namespace std;

Deck cardDeck;
Deck playerDeck(0);
Deck dealerDeck(0);

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

void blackjack()
{
	//Initialize all variables here
	bool goAgain = false;
	bool hitStandLoop = true;
	bool dealerPart = false;
	char hitOrStand;
	char yesOrNo;

	//Do while loop to run at least once, then check at the end of the game if the user wants to go again
	do {
		//get deck ready for game start
		playerDeck.clearDeck();
		dealerDeck.clearDeck();
		cardDeck.initDeck();
		cardDeck.shuffleDeck();
		convertDeck();

		//clear screen from previous game, if necessary
		system("cls");

		//Deal cards to dealer and player
		dealPlayerCards(2);
		dealDealerCards(2);
		string dealerFirstCard = dealerDeck.getCard(0).getFront();

		//Print cards out to user
		setConsoleColor("purple"); cout << "-----------\n YOUR HAND\n-----------\n"; setConsoleColor("white"); cout << getPlayerHand() << endl;
		setConsoleColor("purple"); cout << "---------------------\n DEALER'S FIRST CARD\n---------------------\n"; setConsoleColor("white"); cout << dealerFirstCard << endl;
		while (hitStandLoop) {
			cout << "Type H to hit, or S to stand >> ";
			cin >> hitOrStand;
			switch (hitOrStand) {
			case 'H':
				//deal new card to player
				dealPlayerCards(1);
				//clear the screen to keep things neat
				system("cls");
				//print out new hand, and dealers first card again (in case they forgot)
				setConsoleColor("purple"); cout << "-----------\n YOUR HAND\n-----------\n"; setConsoleColor("white"); cout << getPlayerHand() << endl;
				setConsoleColor("purple"); cout << "---------------------\n DEALER'S FIRST CARD\n---------------------\n"; setConsoleColor("white"); cout << dealerFirstCard << endl;
				//check players hand for total amount
				//if greater than 21, bust, go to you lose method
				if (playerDeck.totalValue() > 21) {
					hitStandLoop = false;
					//youLose();
				} //if equal to 21, blackjack! go to you win method
				else if (playerDeck.totalValue() == 21) {
					hitStandLoop = false;
					//youWin();
				} //if none of the above, continue through loop normally
				else if (playerDeck.totalValue() < 21) {
					hitStandLoop = true;
				}
				break;
			case 'S':
				cout << "Total hand value is: " << playerDeck.totalValue();
				hitStandLoop = false;
				if (playerDeck.totalValue() > 21) {
					hitStandLoop = false;
					//youLose();
				}
				else if (playerDeck.totalValue() == 21) {
					hitStandLoop = false;
					//youWin();
				}
				else if (playerDeck.totalValue() < 21) {
					hitStandLoop = false;
					//player is eligible to go up against dealers hand now
					dealerPart = true;
				}
				break;
			default:
				cout << "That is not a valid response, please try again >> ";
				cin >> hitOrStand;
			}
		}

		while (dealerPart) {
			system("cls");
			setConsoleColor("purple"); cout << "-------------\n DEALER HAND\n-------------\n"; setConsoleColor("white"); cout << getDealerHand() << endl;
			
			//check dealers hand, now that user is finished
			//if dealers hand is greater, immediate loss
			if (dealerDeck.totalValue() > playerDeck.totalValue()) {
				dealerPart = false;
				//youLose();
			} //if the dealers hand is below 17, hit once
			else if (dealerDeck.totalValue() < 17) {
				dealDealerCards(1);
			} //if dealers hand is greater than or equal to 17, check dealers hand against players
			else if (dealerDeck.totalValue() >= 17) {
				if (dealerDeck.totalValue() > playerDeck.totalValue()) {
					//youLose();
				}
				else {
					//youWin();
				}
				dealerPart = false;
			} //if the dealer busts, immediate win for the user
			else if (dealerDeck.totalValue() > 21) {
				dealerPart = false;
				//youWin();
			}
			else if (dealerDeck.totalValue() == playerDeck.totalValue()) {
				//tie();
			}
		}

		cout << "\nPlay again (y/n)? >> ";
		cin >> yesOrNo;
		switch (yesOrNo) {
		case 'y':
			goAgain = true;
			break;

		case 'n':
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