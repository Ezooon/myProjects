//Andrew Lucentini, lucenta
#include "FreecellGame.h"
#include "Exceptions.h"

FreecellGame::FreecellGame(){
	
}

void FreecellGame::newGame(vector<CardT> deck){
	//Four foundation piles in top right corner
    this->foundP = {PileT(),PileT(),PileT(),PileT()};
    //Four cell piles in top left corner
    this->cellP = {PileT(), PileT(), PileT(), PileT()};
    //8 Tableau piles
    this->tabP = {PileT(), PileT(), PileT(), PileT(), PileT(), PileT(), PileT(), PileT()};

	//Number of cards must be 52 and there can be no duplicate cards in the deck
	if (deck.size() !=52 || areDuplicateCards(deck)){
		throw invalid_deck();
	}
	else{
		//Add 7 cards from the deck to the first 4 tableau piles
		for (int i=0;i<4;i++){
			for (int j=0;j<7;j++){
				this->tabP[i].add(deck[7*i+j]);
			}
		}
		//Add 6 cards from the deck to the second 4 tableau piles
		for (int i=0;i<4;i++){
			for (int j=0;j<6;j++){
				this->tabP[i+4].add(deck[6*i+j+28]);
			}
		}
	}
}

CardT FreecellGame::getCard(PileType pile, int i){
	//If the pile is a foundation pile, the index must be between 0 and 4
	if (pile == foundation && i >= 0 && i < F_C_SIZE){
		//Get the card at the top of the pile only if the pile isnt empty
		if (this->foundP[i].size()==0)
			throw invalid_availability();
		else
			return this->foundP[i].top();
	}
	//If the pile is a cell pile, the index must be between 0 and 4
	else if (pile == cell && i >= 0 && i < F_C_SIZE){
		//Get the card at the top of the pile only if the pile isnt empty
		if (this->cellP[i].size()==0)
			throw invalid_availability();
		else
			return this->cellP[i].top();
	}
	//If the pile is a tableau pile, the index must be between 0 and 7
	else if (pile == tableau && i >= 0 && i < T_SIZE){
		//Get the card at the top of the pile only if the pile isnt empty
		if (this->tabP[i].size()==0)
			throw invalid_availability();
		else
			return this->tabP[i].top();
	}
	//Throw invalid index if the index is out of bounds of the pile
	else{
		throw invalid_index();
	}
}

int FreecellGame::size(PileType pile, int i){
	//Return the size of the pile depending on what kind of pile it is
	if (pile == foundation && i >= 0 && i < F_C_SIZE){
		return this->foundP[i].size();
	}
	else if (pile == cell && i >= 0 && i < F_C_SIZE){
		return this->cellP[i].size();
	}
	else if (pile == tableau && i >= 0 && i < T_SIZE){
		return this->tabP[i].size();
	}
	else{
		throw invalid_index();
	}
}

void FreecellGame::moveCard(PileType from, PileType to, int i, int j){

	//Move card from tableau pile to tableau pile
	if (from == tableau && i >= 0 && i < T_SIZE &&
		to == tableau && j >= 0 && j < T_SIZE){

		//If the tableau pile at i is empty, throw invalid size error
		if (this->tabP[i].size()==0){			
			throw invalid_move();
		} 
		//If the tableau pile at j is empty, add the card from the top of tableau pile at i
		else if (this->tabP[j].size() == 0){	
			CardT topcard = this->tabP[i].rm();
			this->tabP[j].add(topcard);
		}
		//If the card at tableau pile i is the opposite colour and is one less than the card at the top of tableau pile j, move to pile j
		else if (this->tabP[i].top().isOppositeColour(this->tabP[j].top()) &&
				 this->tabP[i].top().isOneLess(this->tabP[j].top())){ 
			CardT topcard = this->tabP[i].rm();
			this->tabP[j].add(topcard);
		}
		else{
			throw invalid_move();
		}

	}

	//Move card from tableau pile to cellPile
	else if (from == tableau && i >= 0 && i < T_SIZE &&
			 to == cell && j >= 0 && j < F_C_SIZE){
		//if the tableau pile is empty or the cell pile is not empty, throw invalid_move error
		if (this->tabP[i].size()==0 || this->cellP[j].size() != 0){
			throw invalid_move();
		}
		//If the case above is false, move the card at the top of the tableau pile at index i to the cell at index j
		else{
			CardT topcard = this->tabP[i].rm();
			this->cellP[j].add(topcard);
		}
	}

	//Move card from tableau pile to foundationPile
	else if (from == tableau && i >= 0 && i < T_SIZE &&
			 to == foundation && j >= 0 && j < F_C_SIZE){
		//If the tableau pile is empty, return an error
		if (this->tabP[i].size() == 0){
			throw invalid_move();
		}
		//Else if the foundation pile is empty, move the card to that pile if and only if that card is an ace
		else if(this->foundP[j].size()==0){

			if (this->tabP[i].top().V() == ace){
				CardT topcard = this->tabP[i].rm();
				this->foundP[j].add(topcard);
			}
			else{
				throw invalid_move();
			}

		}
		//Else only move the card if it is the same suit and one value greater than the card on the top of the foundation pile at j
		else if (this->foundP[j].top().isOneLess(this->tabP[i].top()) &&
			 	 this->foundP[j].top().S() == this->tabP[i].top().S()){
			CardT topcard = this->tabP[i].rm();
			this->foundP[j].add(topcard);
		}
		else{
			throw invalid_move();
		}
	}

	//Move card from this->cellPile to this->cellPile
	else if (from == cell && i >= 0 && i < F_C_SIZE &&
			 to == cell && j >= 0 && j < F_C_SIZE){
		//If the cell at index i is empty or the cell at index j is not empty, throw invalid_move()
		if (this->cellP[i].size() == 0 || this->cellP[j].size() != 0){
			throw invalid_move();
		}
		//Else move the card from the cell pile at index i to the cell pile at index j
		else{
			CardT topcard = this->cellP[i].rm();
			this->cellP[j].add(topcard);
		}
	}

	//Move card from cellPile to tableau pile
	else if (from == cell && i >= 0 && i < F_C_SIZE &&
			 to == tableau && j >= 0 && j < T_SIZE){
		//If the this->cellPile is empty, throw invalid_move()
		if (this->cellP[i].size() == 0){
			throw invalid_move();
		}
		//Else if the tableau pile is empty, move the card from the this->cellPile to the tableu Pile
		else if (this->tabP[j].size()==0){
			CardT topcard = this->cellP[i].rm();
			this->tabP[j].add(topcard);

		}
		//Else move the card if and only if the cards have opposite colour and the card is one value less than the top card in this->tabP[j]
		else if (this->cellP[i].top().isOppositeColour(this->tabP[j].top()) &&
				 this->cellP[i].top().isOneLess(this->tabP[j].top())){
			CardT topcard = this->cellP[i].rm();
			this->tabP[j].add(topcard);
		}
		else{
			throw invalid_move();
		}
	}
	//Move card from cellPile to foundation pile
	else if (from == cell && i >= 0 && i < F_C_SIZE &&
			 to == foundation && j >= 0 && j < F_C_SIZE){
		//If the cell pile is empty, throw invalid_move()
		if (this->cellP[i].size() == 0){
			throw invalid_move();
		}
		//Else if the foundation pile is empty, move the card if and only if that card is an ace
		else if(this->foundP[j].size()==0){

			if (this->cellP[i].top().V() == ace){
				CardT topcard = this->cellP[i].rm();
				this->foundP[j].add(topcard);
			}
			else{
				throw invalid_move();
			}

		}
		//Else move the card if and only if the card is opposite colour and one value greater than the card at the top of the foundation pile
		else if (this->foundP[j].top().isOneLess(this->cellP[i].top()) &&
			 	 this->foundP[j].top().S() == this->cellP[i].top().S()){
			CardT topcard = this->cellP[i].rm();
			this->foundP[j].add(topcard);
		}
		else{
			throw invalid_move();
		}
	}
	//Move from foundation pile to foundation pile
	else if (from == foundation && i >= 0 && i < F_C_SIZE &&
		to == foundation && j >= 0 && j < F_C_SIZE){
		//If the foundation pile at this->foundP[i] is empty, throw invalid_move()
		if (this->foundP[i].size() == 0 ){
			throw invalid_move();
		}
		//Else if the foundation pile at this->foundP[j] is empty, move the top card from this->foundP[i] to this->foundP[j] if and only if that card is an ace
		else if(this->foundP[j].size()==0){

			if (this->foundP[i].top().V() == ace){
				CardT topcard = this->foundP[i].rm();
				this->foundP[j].add(topcard);
			}
			else{
				throw invalid_move();
			}
		}
		//Else throw invalid_move()
		else{
			throw invalid_move();
		}

	}	
	//Move from foundation pile to this->cellPile
	else if (from == foundation && i >= 0 && i < F_C_SIZE &&
		to == cell && j >= 0 && j < F_C_SIZE){
		//If the foundation pile is empty, throw invalid_move()
		if (this->foundP[i].size() == 0){
			throw invalid_move();
		}
		//Else if the cell pile is empty, move the card from the top of the foundation pile to the cell pile
		else if (this->cellP[j].size() == 0){
			CardT topcard = this->foundP[i].rm();
			this->cellP[j].add(topcard);
		}
		//Else throw invalid_move()
		else{
			throw invalid_move();
		}

	}	
	//Move from foundation pile to tableauPile
	else if (from == foundation && i >= 0 && i < F_C_SIZE &&
		to == tableau && j >= 0 && j < T_SIZE){
		//If the foundation pile is empty, throw invalid_move()
		if (this->foundP[i].size()==0){
			throw invalid_move();
		}
		//Else if the tableau pile is empty, move the card
		else if(this->tabP[j].size()==0){
			CardT topcard = this->foundP[i].rm();
			this->tabP[j].add(topcard);
		}
		//Else if neither are empty, move the card if and only if the card has an opposite colour and is one value less than the card at the top of the tableau pile
		else if (this->foundP[i].top().isOneLess(this->tabP[j].top()) &&
			 	 this->tabP[j].top().isOppositeColour(this->foundP[i].top())){
			CardT topcard = this->foundP[i].rm();
			this->tabP[j].add(topcard);
		}
		//Else throw invalid_move
		else{
			throw invalid_move();
		}

	}
	//If none of the cases above work, throw invalid_move()
	else{
		throw invalid_move();
	}
}


bool FreecellGame::gameWon(){
	//Return true only if the number of cards in each foundation pile is equal to 13
	for (int i=0;i<F_C_SIZE;i++){
		if (this->foundP[i].size()!=13)
			return false;
	}
	return true;

}
bool FreecellGame::noValidMoves(){
	//Return false if there are spaces in cell piles
	for (int i=0;i <F_C_SIZE;i++){
		if (this->cellP[i].size() == 0)
			return false;
	}
	//Check if you can move from a tableau pile from first pile
	for (int i=1;i<T_SIZE;i++){
		if (tabP[0].top().isOneLess(tabP[i].top()) && tabP[0].top().isOppositeColour(tabP[i].top()))
			return false;
	}
	return true;
}


bool FreecellGame::areDuplicateCards(vector<CardT> deck){
	//Check that for all cards in the deck, there are no duplicate cards
	for (int i=0; i<deck.size()-1;i++){
		for (int j=i+1;j<deck.size();j++){
			if (deck[i].S() == deck[j].S() &&
				deck[i].V() == deck[j].V())
				return true;
		}
	}
	return false;

}
