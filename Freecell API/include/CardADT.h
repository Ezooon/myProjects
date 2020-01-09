//Andrew Lucentini, lucenta
/**
 *  \file CardADT.h
 *  \brief A modlue containing the implementation of an abstract object representing a playing card
 */
#ifndef CARDADT_H
#define CARDADT_H

#include "CardTypes.h"

/**
 *  \brief Class representing a playing card
 *  \details The card is represented by a Suit and a Value
 */
class CardT 
{
	private:
		/// The suit of the card
		Suit s;
		/// The value of the card
		Value v;
	public:
		/**
		 *  \brief Constructs a new CardT with a suit and value
		 *  \param val The value of the card
		 *  \param st The suit of the card
		 */
		CardT(Value val, Suit st);

		/**
		 *  \brief Get the suit of the card
		 *  \return The suit of the card
		 */
		Suit S();

		/**
		 *  \brief Get the value of the card
		 *  \return The value of the card
		 */
		Value V();

		/**
		 *  \brief Checks if the card's suit colour is opposite to another card's suit colour
		 *  \details Hearts and diamonds have red colour, where as spades and clubs have black colour
		 *  \param card A CardT object
		 *  \return True if the card's suit is opposite to the other card's suit colour, otherwise false
		 */
		bool isOppositeColour(CardT card);

		/**
		 *  \brief Checks if the card's value is one point lower than another card's value
		 *  \details The possible values of the cards in ascending order are: ace,two,three,four,five,six,seven,eight,nine,ten,jack,queen,king
		 *           i.e ace is one less than two, three is one less than four, etc.
		 *  \param card A CardT object
		 *  \return True if the card's value is one point less than the other card's value
		 */
		bool isOneLess(CardT card);
};

#endif