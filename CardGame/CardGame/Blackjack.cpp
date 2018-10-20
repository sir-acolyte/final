#include <vector> 
#include <iostream>
#include <fstream>
#include <streambuf>
#include "Deck.h"
#include "Console.h"

using namespace std;

//global deck variables so all functions can access them
Deck cardDeck;
Deck playerDeck(0);
Deck dealerDeck(0);
//global betting variable so all functions can access it (e.g. youLose(bet))
//player starts with $250
int money = 250;
//variable for Scores.txt
ofstream scorefile;
ifstream readfile;
//user's name for high score listings
string username = "";
int highScore = 0;

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

//player/dealer specific functions for better functionality (difficulties taking in a deck parameter)

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

void setScore() {
	//put user in high score file
	string str;
	vector<string> names;
	vector<int> scores;

	//open file
	readfile.open("files\\scores.txt");

	// Read the next line from File untill it reaches the end
	while (getline(readfile, str)) {
		names.push_back(str.substr(0, str.find("-") - 1));
		scores.push_back(stoi(str.substr(str.find("-") + 2)));
	}
	//remove old and duplicate scores
	for (int i = 0; i < names.size(); i++) {
		if (names[i] == username) {
			names.erase(names.begin() + i);
			scores.erase(scores.begin() + i);
		}
	}
	str = "";
	//put old scores back in
	for (int i = 0; i < names.size(); i++) {
		str += names[i] + " - " + to_string(scores[i]) + "\n";
	}
	//add new score in
	str += username + " - " + to_string(highScore) + "\n";

	//write to file
	scorefile.open("files\\scores.txt");
	scorefile << str;
	scorefile.close();
	readfile.close();
}

//returns list of scores as a string
string getScores() {
	string str;
	vector<string> names;
	vector<int> scores;

	//open file
	readfile.open("files\\scores.txt");

	// Read the next line from File untill it reaches the end
	while (getline(readfile, str)) {
		names.push_back(str.substr(0, str.find("-") - 1));
		scores.push_back(stoi(str.substr(str.find("-") + 2)));
	}
	//remove old and duplicate scores
	for (int i = 0; i < names.size(); i++) {
		if (names[i] == username) {
			names.erase(names.begin() + i);
			scores.erase(scores.begin() + i);
		}
	}
	str = "\n";
	//put old scores back in
	for (int i = 0; i < names.size(); i++) {
		str += names[i] + " - " + to_string(scores[i]) + "\n";
	}

	readfile.close();
	return str;
}

//pulls high score from text file if matching username is entered
void getScore() {
	string str;
	vector<string> names;
	vector<int> scores;

	readfile.open("files\\scores.txt");

	// Read the next line from File untill it reaches the end
	while (getline(readfile, str)) {
		names.push_back(str.substr(0, str.find("-") - 1));
		scores.push_back(stoi(str.substr(str.find("-") + 2)));
	}
	//set high score is matching username is found
	for (int i = 0; i < names.size(); i++) {
		if (names[i] == username) {
			highScore = scores[i];
		}
	}
	//Close The File
	readfile.close();
}

//take in bet for win and lose method to determine how much to add or take away from the total money the user has
void youWin(int bet) {
	//resize and clear screen
	system("cls");
	setConsoleSize(400, 465);

	setConsoleColor("green"); cout << "\n  -----------\n    YOU WIN\n  -----------\n" << endl; setConsoleColor("yellow");
	cout << "  ___________\n '._==_==_=_.'\n .-\\:      /-.\n| (|:.     |) |\n '-|:.     |-'\n   \\::.    /\n    '::. .'\n      ) (\n    _.' '._\n   `~~~~~~~`" << endl; setConsoleColor("white");
	cout << "\nYou had a total of "; setConsoleColor("purple"); cout << playerDeck.totalValue(); setConsoleColor("white"); cout << " and the \ndealer had a total of "; setConsoleColor("purple"); cout << dealerDeck.totalValue() << ".\n"; setConsoleColor("white");
	money += bet;

	if (money > highScore) {
		highScore = money;
	}
	setConsoleColor("white"); cout << "\nYou now have "; setConsoleColor("purple"); cout << money; setConsoleColor("white"); cout << " dollars with a \nhigh score of "; setConsoleColor("purple"); cout << highScore; setConsoleColor("white"); cout << ".\n";
	//set the highest amount of money they won to high score, if current money is higher
	setScore();
}

void youLose(int bet) {
	//resize and clear screen
	system("cls");
	setConsoleSize(400, 465);

	setConsoleColor("red"); cout << "\n  ------------\n    YOU LOSE\n  ------------\n" << endl; setConsoleColor("white");
	cout << "You had a total of "; setConsoleColor("purple"); cout << playerDeck.totalValue(); setConsoleColor("white"); cout << " and the \ndealer had a total of "; setConsoleColor("purple"); cout << dealerDeck.totalValue() << ".\n"; setConsoleColor("white");
	money -= bet;
	if (money > highScore) {
		highScore = money;
	}
	setConsoleColor("white"); cout << "\nYou now have "; setConsoleColor("purple"); cout << money; setConsoleColor("white"); cout << " dollars with a \nhigh score of "; setConsoleColor("purple"); cout << highScore; setConsoleColor("white"); cout << ".\n";
	setScore();
}
//auto set console size based on how many cards are on screen, for formatting
void autoResize(boolean displayHand) {
	int defaultSize = 410;
	if (displayHand) {
		for (int i = 0; i < playerDeck.getSize() + dealerDeck.getSize(); i++) {
			setConsoleSize(400, i * 105 + (defaultSize - 100));
		}
	}
	else {
		for (int i = 0; i < playerDeck.getSize(); i++) {
			setConsoleSize(400, i * 105 + defaultSize);
		}
	}
}

void blackjack()
{
	//Initialize all variables here
	bool goAgain = false;
	bool hitStandLoop = true;
	bool dealerPart = false;
	char hitOrStand;
	char yesOrNo = 'Y';
	char displayHand = 'N';
	int bet = 0;

	//print high scores
	cout << getScores();
	setConsoleColor("cyan"); cout << "\nEnter your username >> "; setConsoleColor("white");
	cin >> username;
	//gets existing score from username
	getScore();

	//Do while loop to run at least once, then check at the end of the game if the user wants to go again
	do {
		//exit game if money reaches 0
		if (money <= 0) {
			cout << "Not enough money, sorry!" << endl;
			Sleep(1000);
			break;
		}

		//get decks ready for game start
		playerDeck.clearDeck();
		dealerDeck.clearDeck();
		cardDeck.initDeck();
		cardDeck.shuffleDeck();
		convertDeck();

		//clear screen from previous game, if there was one
		system("cls");

		//Deal cards to dealer and player
		dealPlayerCards(2);
		dealDealerCards(2);
		//turn dealer's first card into a string for easier output
		string dealerFirstCard = dealerDeck.getCard(0).getFront();
		string playerFirstCard = playerDeck.getCard(0).getFront();

		setConsoleSize(400, 540);
		//Print cards out to user (first time), so they can make a decision based on their hand
		setConsoleColor("purple"); cout << "\n-------------\n  YOUR HAND\n-------------\n"; setConsoleColor("white"); cout << playerFirstCard << endl;
		setConsoleColor("purple"); cout << "\n---------------\n  DEALER HAND\n---------------\n"; setConsoleColor("white"); cout << dealerFirstCard << endl;
		//print total amount of money to user
		cout << "\nYou have "; setConsoleColor("purple"); cout << money; setConsoleColor("white"); cout << " dollars.";
		//ask user how much they would like to bet
		setConsoleColor("cyan"); cout << "\nEnter amount to bet >> "; setConsoleColor("white");
		cin >> bet;
		//makes sure user only enter and amount they can afford
		while (bet > money || bet < 0) {
			setConsoleColor("red"); cout << "\nInvalid amount."; setConsoleColor("white");
			cout << "\nYou have "; setConsoleColor("purple"); cout << money; setConsoleColor("white"); cout << " dollars.";
			//ask user how much they would like to bet
			setConsoleColor("cyan"); cout << "\nEnter amount to bet >> "; setConsoleColor("white");
			cin >> bet;
		}
		
		//clear and resize screen
		system("cls");
		autoResize(false);
		//Print cards out to user (second)
		setConsoleColor("purple"); cout << "\n-------------\n  YOUR HAND\n-------------\n"; setConsoleColor("white"); cout << getPlayerHand() << endl;
		setConsoleColor("purple"); cout << "\n---------------\n  DEALER HAND\n---------------\n"; setConsoleColor("white"); cout << dealerFirstCard << endl;
		
		while (hitStandLoop) {
			setConsoleColor("cyan"); cout << "\nHit (H) or Stand (S) >> "; setConsoleColor("white"); cin >> hitOrStand;
			hitOrStand = toupper(hitOrStand);

			switch (hitOrStand) {
			default:
				int numAce;
				int acePos;

				cout << "That is not a valid response, please try again.\n";
				break;
			case 'H':
				//deal new card to player
				dealPlayerCards(1);

				//clear and resize the screen to keep things neat
				autoResize(false);
				system("cls");

				//print out new hand, and dealers first card again (in case they forgot)
				setConsoleColor("purple"); cout << "\n-------------\n  YOUR HAND\n-------------\n"; setConsoleColor("white"); cout << getPlayerHand() << endl;
				setConsoleColor("purple"); cout << "\n---------------\n  DEALER HAND\n---------------\n"; setConsoleColor("white"); cout << dealerFirstCard << endl;

				//check players hand for total amount
				//if greater than 21, bust, go to you lose method
				if (playerDeck.totalValue() > 21) {
					hitStandLoop = false;
					youLose(bet);
				} //if equal to 21, blackjack! go to you win method
				else if (playerDeck.totalValue() == 21) {
					hitStandLoop = false;
					youWin(bet);
				} //if none of the above, continue through loop normally
				else if (playerDeck.totalValue() < 21) {
					hitStandLoop = true;
				}
				break;
			case 'S':
				//same logic as if they would hit, just no dealing cards this time
				hitStandLoop = false;
				numAce = 0;
				acePos = 0;

				//-----Checks if there is a single ace in the deck and asks the user what value it should be-----//
				for (int i = 0; i < playerDeck.getSize(); i++) {
					if (playerDeck.getCard(i).getNumber() == 1) {
						numAce += 1;
						acePos = i;
					}
				}
				if (numAce == 1) {
					setConsoleColor("cyan"); cout << "\nEnter ace value (1/11) >> "; setConsoleColor("white");
					cin >> numAce;
					while (numAce != 1 && numAce != 11) {
						setConsoleColor("red"); cout << "\nInvalid amount."; setConsoleColor("white");
						setConsoleColor("cyan"); cout << "\nEnter ace value (1/11) >> "; setConsoleColor("white");
						cin >> numAce;
					}
					vector<Card> tempDeck = playerDeck.getDeck();
					tempDeck[acePos].setNumber(numAce);
					playerDeck.updateDeck(tempDeck);
				}
				//----------------------------------------------------------------------------------------------//

				if (playerDeck.totalValue() > 21) {
					hitStandLoop = false;
					youLose(bet);
				}
				else if (playerDeck.totalValue() == 21) {
					hitStandLoop = false;
					youWin(bet);
				}
				else if (playerDeck.totalValue() < 21) {
					hitStandLoop = false;
					//player is eligible to go up against dealers hand now
					dealerPart = true;
				}
				break;
			}
			
		}
		//where the dealer checks their cards, "end game"
		while (dealerPart) {
			//clear and resize screen
			system("cls");
			
			//check dealers hand, now that user is finished
			//if dealers hand is greater, immediate loss
			if (dealerDeck.totalValue() > playerDeck.totalValue() && dealerDeck.totalValue() <= 21) {
				dealerPart = false;
				youLose(bet);
			} //if the dealers hand is below 17, hit once
			else if (dealerDeck.totalValue() < 17 && dealerDeck.totalValue() <= 21) {
				dealDealerCards(1);
			} //if dealers hand is greater than or equal to 17 and below 21, check dealers hand against players
			else if (dealerDeck.totalValue() >= 17 && dealerDeck.totalValue() <= 21) {
				if (dealerDeck.totalValue() > playerDeck.totalValue()) {
					youLose(bet);
				} //if the dealer and the player tie, the house wins
				else if (dealerDeck.totalValue() == playerDeck.totalValue()) {
					youLose(bet);
				} //if all else fails, then the player wins
				else {
					youWin(bet);
				}
				dealerPart = false;
			} //if the dealer busts, immediate win for the user
			else if (dealerDeck.totalValue() > 21) {
				dealerPart = false;
				youWin(bet);
			} //check for a tie right from the start, if true then immediate loss
			else if (dealerDeck.totalValue() == playerDeck.totalValue()) {
				youLose(bet);
			}
		}
		//ask the user if they want to see the cards the dealer had
		setConsoleColor("cyan"); cout << "\nDisplay hand (Y/N)? >> "; setConsoleColor("white"); cin >> displayHand;
		//toupper method so it can take in lowercase or uppercase regardless
		displayHand = toupper(displayHand);
		switch (displayHand) {
		case 'Y':
			system("cls");
			autoResize(true);

			setConsoleColor("purple"); cout << "\n-------------\n  YOUR HAND\n-------------\n"; setConsoleColor("white"); cout << getPlayerHand() << endl;
			setConsoleColor("purple"); cout << "\n---------------\n  DEALER HAND\n---------------\n"; setConsoleColor("white"); cout << getDealerHand() << endl;
			break;

		case 'N':
			break;
		default: //exits option to choose whether to see the hand or not, not exiting the game itself
			cout << "\nInvalid answer, exiting...";
			goAgain = false;
		}
		//asks the user if they would like to play again
			setConsoleColor("cyan"); cout << "\nPlay again (Y/N)? >> "; setConsoleColor("white"); cin >> yesOrNo;
			yesOrNo = toupper(yesOrNo);
			switch (yesOrNo) {
			case 'Y':
				goAgain = true;
				break;
			case 'N':
				goAgain = false;
				break;
			default: //exits the actual game
				cout << "\nInvalid answer, exiting...";
				goAgain = false;
			}

		//resets the values of most booleans, so it acts like a new game
		dealerPart = false;
		hitStandLoop = true;
	} while (goAgain);
}