//Andrew Lucentini, lucenta
#include "catch.h"
#include "CardADT.h"

TEST_CASE ("tests for CardADT", "[CardT]"){
	CardT card1(ace,hearts);
    CardT card2(two,spades);
    CardT card3(king,clubs);


    SECTION("checks the values of the cards are returned"){
        //check card1
        REQUIRE(card1.S()==hearts);
        REQUIRE(card1.V()==ace);

        //check card2
        REQUIRE(card2.S()==spades);
        REQUIRE(card2.V()==two);

        //check card3
        REQUIRE(card3.S()==clubs);
        REQUIRE(card3.V()==king);

    }

    SECTION("checks opposite colour of cards is black cards, and black cards is red cards"){
        REQUIRE(card1.isOppositeColour(CardT(two,hearts))==false);
        REQUIRE(card2.isOppositeColour(CardT(two,clubs))==false);
        REQUIRE(card2.isOppositeColour(CardT(two,diamonds))==true);
        REQUIRE(card3.isOppositeColour(CardT(three,hearts))==true);
        REQUIRE(card3.isOppositeColour(CardT(three,spades))==false);
        REQUIRE(card3.isOppositeColour(CardT(three,clubs))==false);
    }

    SECTION("checks that card passed as paramater is one less than card varaiable"){
        REQUIRE(card1.isOneLess(CardT(two,hearts))==true);
        REQUIRE(card1.isOneLess(CardT(ace,spades))==false);
        REQUIRE(card1.isOneLess(CardT(three,clubs))==false);
        REQUIRE(card2.isOneLess(CardT(three,clubs))==true);
        REQUIRE(card2.isOneLess(CardT(four,diamonds))==false);
        REQUIRE(card3.isOneLess(CardT(king,spades))==false);
        REQUIRE(card3.isOneLess(CardT(queen,clubs))==false);
    }
}
