//Andrew Lucentini, lucenta
#include "PileADT.h"

PileT::PileT(){
}

void PileT::add(CardT card){
	//Add card to top of vector
	this->s.push_back(card);
}

CardT PileT::top(){
	//It is assumed that this method won't be called when the size of the PileT is 0
	return this->s.back();
}

CardT PileT::rm(){
	//Extract the top card before removing the card from s
	//It is assumed that this method won't be called when the size of the PileT is 0
	CardT card = this->s.back();
	this->s.pop_back();
	return card;
}

int PileT::size(){
	return this->s.size();
}
