//Andrew Lucentini, lucenta
/**
 *  \file PileADT.h
 *  \brief A module implementing an abstract class that represents a pile of cards
 */
#ifndef PILEADT_H
#define PILEADT_H

#include "CardADT.h"
#include "PileTypes.h"
#include <vector>

using namespace std;

/**
 *  \brief Class representing a pile (or stack) of CardT's
 *  \details The pile is initially empty (it contains no CardT's)
 */
class PileT 

{
	private:
		/// A vector of CardT's used to store the CardT's in the pile
		vector<CardT> s;
	public:
		/**
		 *  \brief Constructs a new PileT that is initially empty
		 */
		PileT();

		/**
		 *  \brief Adds a card to the top of the pile
		 *  \param card A CardT object
		 */
		void add(CardT card);

		/**
		 *  \brief Get the card at the top of the pile
		 *  \details It is assumed that this method won't be called when there are no CardT's in the Pile
		 *  \return The card at the top of the pile
		 */
		CardT top();

		/**
		 *  \brief Remove the card at the top of the pile
		 *  \details Is it assumed that this method won't be called when there are no CardT's in the Pile
		 *  \return The card that was at the top of the pile
		 */
		CardT rm();

		/**
		 *  \brief Get the number of cards in the pile
		 *  \return The number of cards in the pile
		 */
		int size();
};

#endif