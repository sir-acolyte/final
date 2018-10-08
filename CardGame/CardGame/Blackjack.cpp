#include <time.h>
#include "Card.h"

using namespace std;

void test()
{
	Card card1(4, "Hearts");

	cout << "\nNumber: " << card1.getNumber();
	cout << "\nSuit: " << card1.getSuit();

	card1.setNumber(8);

	cout << "\nNumber: " << card1.getNumber() << "\n";
	system("pause");
}

void blackjack()
{
	cout << "Blackjack";

	test();
}