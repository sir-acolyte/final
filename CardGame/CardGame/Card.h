#pragma once

#ifndef CARD_H
#define CARD_H

#include <string>
#include <iostream>

class Card
{
	private:
		//initialize private variables
		int cardNumber;
		std::string cardSuit;
	
	public:
		//constructor
		Card() {};
		Card(int number, std::string suit) {
			this->cardNumber = number;
			this->cardSuit = suit;
		}

		//return the number of the Card object
		int getNumber() {
			return cardNumber;
		}
		//set the number of the Card object
		void setNumber(int number) {
			this->cardNumber = number;
		}

		//return the suit of the Card object
		std::string getSuit() {
			return cardSuit;
		}
		//set the suit of the Card object
		void setSuit(std::string suit) {
			this->cardSuit = suit;
		}
};

#endif