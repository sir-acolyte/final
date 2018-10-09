#pragma once

#ifndef DECK_H
#define DECK_H

#include <string>
#include <iostream>
#include "Card.h"

class Deck
{
private:
	//initialize private variables
	Card deck[52] = {};
	int deckSize = sizeof(deck) / sizeof(deck[0]);

public:
	//constructor
	Deck() {
		initDeck();
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
};

#endif