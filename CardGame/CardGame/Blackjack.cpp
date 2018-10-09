#include <time.h>
#include <vector> 
#include "Deck.h"

using namespace std;

Deck cardDeck;

void blackjack()
{
	for (int i = 0; i < cardDeck.getSize(); i++) {
		cout << cardDeck.getCard(i).getFace() << " of " << cardDeck.getCard(i).getSuit() << "\n";
	}
	cout << "\n";
	cardDeck.shuffleDeck();
	for (int i = 0; i < cardDeck.getSize(); i++) {
		cout << cardDeck.getCard(i).getFace() << " of " << cardDeck.getCard(i).getSuit() << "\n";
	}

	system("pause");
}