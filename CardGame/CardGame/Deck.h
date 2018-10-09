#pragma once

#ifndef DECK_H
#define DECK_H

#include <string>
#include <iostream>
#include <algorithm>
#include "Card.h"

class Deck
{
private:
	//initialize private variables
	Card deck[52] = {};
	int deckSize = sizeof(deck) / sizeof(deck[0]);

public:
	//constructor - add cards to deck then suffles them
	Deck() {
		initDeck();
		shuffleDeck();
	}

	//fill deck with cards
	void initDeck()
	{
		int num = 0;

		//init Spades
		for (int i = 1; i <= 13; i++) {
			deck[num] = Card(i, "Spades");
			num++;
		}

		//init Hearts
		for (int i = 1; i <= 13; i++) {
			deck[num] = Card(i, "Hearts");
			num++;
		}

		//init Diamonds
		for (int i = 1; i <= 13; i++) {
			deck[num] = Card(i, "Diamonds");
			num++;
		}

		//init Clubs
		for (int i = 1; i <= 13; i++) {
			deck[num] = Card(i, "Clubs");
			num++;
		}
	}

	//return size of deck
	int getSize() {
		return deckSize;
	}

	//return card array
	Card* getDeck() {
		return deck;
	}
	//update entire deck with another one
	void updateDeck(Card *cardDeck) {
		for (int i = 0; i < getSize(); i++) {
			this->deck[i] = cardDeck[i];
		}
	}
	//update specific card in the deck
	void updateCard(Card card, int pos) {
		this->deck[pos] = card;
	}
	//return specific card in the deck
	Card getCard(int pos) {
		return deck[pos];
	}
	//shuffles the deck in random order
	void shuffleDeck() {
		std::random_shuffle(&deck[0], &deck[getSize() - 1]);
	}
};

#endif