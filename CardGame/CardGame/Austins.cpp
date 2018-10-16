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
	//get deck ready for game start
	//cardDeck.initDeck();
	cardDeck.shuffleDeck();
	convertDeck();
	//Initialize all variables here
	bool goAgain = false;
	char hitOrStand;

	//Do while loop to run at least once, then check at the end of the game if the user wants to go again
	do {
		//Deal cards to dealer and player
		dealPlayerCards(2);
		dealDealerCards(2);
		string dealerFirstCard = dealerDeck.getCard(0).getFront();

		//Print cards out to user
		setConsoleColor("purple"); cout << "-----------\n YOUR HAND\n-----------\n"; setConsoleColor("white"); cout << getPlayerHand() << endl;
		setConsoleColor("purple"); cout << "---------------------\n DEALER'S FIRST CARD\n---------------------\n"; setConsoleColor("white"); cout << dealerFirstCard << endl;
		//hitOrStand method??
		cout << "Type H to hit, or S to stand >> ";
		cin >> hitOrStand;
		switch (hitOrStand) {
		case 'H':
			//hit();
			//break;
		case 'S':
			//stand();
			//break;
		default:
			cout << "That is not a valid response, please try again >> ";
			cin >> hitOrStand;
		}

	} while (goAgain);


	system("pause");
}