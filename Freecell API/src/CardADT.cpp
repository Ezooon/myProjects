//Andrew Lucentini, lucenta
#include "CardADT.h"

CardT::CardT(Value val, Suit st)
	{	//Create state variables
		this->v = val;
		this->s = st;
	}
Suit CardT::S()
{ return this->s;}

Value CardT::V()
{ return this->v;}

bool CardT::isOppositeColour(CardT card){
	//If the card is a hearts or diamonds and the other card is a clubs or spades, return true
	if ((this->s == hearts || this->s == diamonds) && (card.S() == spades || card.S() == clubs)){
		return true;
	}
	//If the card is a spades or clubs and the other card is a hearts or diamonds, return true
	if ((this->s == spades || this->s == clubs) && (card.S() == hearts || card.S() == diamonds)){
		return true;
	}
	//Else return false
	return false;
	
}

bool CardT::isOneLess(CardT card){
	//Return true if the enum value of v comes 1 before card.V()
	if ((v - card.V()) == -1)
		return true;
	return false;
}