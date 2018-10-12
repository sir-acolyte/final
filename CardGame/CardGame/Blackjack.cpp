#include <time.h>
#include <vector> 
#include "Deck.h"

using namespace std;

Deck cardDeck;
Deck playerDeck;

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

void dealCards(int num) {
	vector<Card> tempDeck = playerDeck.getDeck();
	for (int i = 0; i < num; i++) {
		Card tempCard = cardDeck.takeCard(0);
		tempDeck.insert(tempDeck.begin(), tempCard);
	}
	for (int i = 0; i < num; i++) {
		playerDeck.addCard(i, tempDeck[i]);
	}
}

void blackjack()
{
	//get deck ready for game start
	//cardDeck.initDeck();
	//cardDeck.shuffleDeck();
	convertDeck();

	for (int i = 0; i < cardDeck.getSize(); i++) {
		cout << cardDeck.getCard(i).getFront() << "\n";
	}

	system("pause");
}