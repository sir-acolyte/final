#include <time.h>
#include <vector> 
#include "Deck.h"

using namespace std;

Deck cardDeck;

void blackjack()
{
	Card *deck = cardDeck.getDeck();
	for (int i = 0; i < cardDeck.getSize(); i++) {
		cout << deck[i].getNumber() << " " << deck[i].getSuit() << "\n";
	}
	system("pause");
}