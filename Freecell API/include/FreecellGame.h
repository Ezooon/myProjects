//Andrew Lucentini, lucenta
/**
 *  \file FreecellGame.h
 *  \brief A modlue containing a class representing the state of a freecell game
 */
#ifndef FREECELLGAME_H
#define FREECELLGAME_H

#include "PileADT.h"

/**
 *  \brief Class representing the state of a freecell game
 *  \details The game is represented as 4 foundation PileT's, 4 cell PileT's, and 8 tableau PileT's
 */
class FreecellGame 

{
	private:

		/// The number of foundation and cell piles
		static const int F_C_SIZE = 4;

		/// The number of tableau piles
		static const int T_SIZE = 8;

		/// The 4 foundation piles typically in the top right of a freecell game
		vector<PileT> foundP;

		/// The 4 cell piles typically in the top left of a freecell game
		vector<PileT> cellP;

		/// The 8 tableau piles typically in the center of a freecell game
		vector<PileT> tabP;	

		/**
		 *  \brief Private method to determine if a vector of cards has any duplicates
		 *  \param deck A vector of CardT's representing a deck of cards
		 */
		bool areDuplicateCards(vector<CardT> deck);	
	public:

		/**
		 *  \brief Creates a new Freecell Game
		 */
		FreecellGame();

		/**
		 *  \brief Removes all of the cards (if any) in the foundP and cellP.
		 *         In addition, it loads a deck of cards into tabP. This method should be called before any other methods
		 *  \details This method assumes that the deck is shuffled. It loads 7 cards into each tabP[i]
		 *           for i = 0 through i = 3, and 6 cards into each tabP[j] for j = 4 through j = 7 (for a total of 52 cards)
		 *  \param deck An array of CardT's representing a deck of cards
		 */
		void newGame(vector<CardT> deck);

		/**
		 *  \brief Gets the top card from either foundP, cellP, or tabP at index i. The sequence used to get the card is specified by the PileType pile
		 *  \param pile The type of the pile used to extract the top element in that pile. This can be foundation, cell, or tableau, which will extract from 
		 *         foundP, cellP, or tabP, respectively.
		 *  \param i An integer used to index a given pile
		 *  \return The element at the top of the pile at index i.
		 */
		CardT getCard(PileType pile, int i);

		/**
		 *  \brief Gets the number of cards from either foundP, cellP, or tabP at index i. The sequence used to get the card is specified by the PileType pile
		 *  \param pile The type of the pile used to extract the top element in that pile. This can be foundation, cell, or tableau, which will extract from 
		 *         foundP, cellP, or tabP, respectively.
		 *  \param i An integer used to index a given pile
		 *  \return The number of cards in the pile at index i.
		 */
		int size(PileType pile, int i);

		/**
		 *  \brief Move a CardT from one pile in foundP, cellP, or tabP specified at index i to another pile in foundP, cellP, or tabP,
		 *         specified at index j. The piles specified are given by from and to.
		 *  \param from The type of the pile used to remove the top element in that pile. This can be foundation, cell, or tableau, which will extract from 
		 *         foundP, cellP, or tabP, respectively.
		 *  \param i An integer used to index the pile specified by from
		 *  \param to The type of the pile used to add the element that was removed from the pile from. This can be foundation, cell, or tableau, which will add to 
		 *         foundP, cellP, or tabP, respectively.
		 *  \param j An integer used to index the pile specified by to
		 */
		void moveCard(PileType from, PileType to, int i, int j);

		/**
		 *  \brief Determines if a given game has been won
		 *  \return True if a freecellgame has been won, else false
		 */
		bool gameWon();

		/**
		*   \brief Determines if there are any possible moves left
		*   \return True if there are no possible moves left
		*/
		bool noValidMoves();

};

#endif