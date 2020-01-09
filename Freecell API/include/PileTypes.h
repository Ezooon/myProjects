//Andrew Lucentini, lucenta
/**
 *  \file PileTypes.h
 *  \brief File implementing names for the types of card piles existing in freecell
 */
#ifndef PILETYPES_H
#define PILETYPES_H

/**
 *  \brief A type representing the possible card pile type in freecell. Foundation piles are the piles typically
 *         located in the top right corner of freecell. Cell piles are the piles typically located in the top left
 *         corner of freecell. Tableau piles are the 8 piles in the center of freecell.
 */
enum PileType {foundation, cell, tableau};

#endif