#include <vector> 
#include "Deck.h"

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

void dealCards(Deck deck) {
	vector<Card> tempDeck = playerDeck.getDeck();
	for (int i = 0; i < 2; i++) {
		Card tempCard = cardDeck.takeCard(i);
		tempDeck.insert(tempDeck.begin() + i, tempCard);
		playerDeck.addCard(i, tempDeck[i]);
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
		dealCards(playerDeck);
		//dealCards(dealerDeck);
		//string dealerFirstCard = dealerDeck.getCard(0).getFace();
		//Print cards out to user
		cout << "Your hand is: " << playerDeck.getAllCards() << endl;
		//cout << "The dealer's first card is: " << dealerFirstCard << endl;
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