#include <time.h>
#include <vector> 
#include "Deck.h"

using namespace std;

Deck cardDeck;

//makes jacks, kings, and queens = 10 for blackjack
void convertDeck() {
	//temporary variable to hold deck array
	Card *deck = cardDeck.getDeck();

	//changes cards greater that 10 to equal 10
	for (int i = 0; i < cardDeck.getSize(); i++) {
		if (deck[i].getNumber() > 10) {
			deck[i].setNumber(10);
		}
	}

	//updates the deck with the modified one
	cardDeck.updateDeck(deck);
}

void blackjack()
{
	//get deck ready for game start
	cardDeck.initDeck();
	cardDeck.shuffleDeck();
	convertDeck();

	for (int i = 0; i < cardDeck.getSize(); i++) {
		cout << cardDeck.getCard(i).getFace() << " of " << cardDeck.getCard(i).getSuit() << "\n";
	}
	
	cout << "\n";
	for (int i = 0; i < cardDeck.getSize(); i++) {
		cout << cardDeck.getCard(i).getFace() << " of " << cardDeck.getCard(i).getNumber() << "\n";
	}

	system("pause");
}