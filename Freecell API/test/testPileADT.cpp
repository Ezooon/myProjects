//Andrew Lucentini, lucenta
#include "catch.h"
#include "PileADT.h"

TEST_CASE ("tests for PileT", "[PileT]"){
	CardT card1(ace,hearts);
    CardT card2(four,clubs);
    CardT card3(three,spades);
    CardT card4(queen,diamonds);
    PileT pile = PileT();


    SECTION("get number of elements in pile"){
        REQUIRE(pile.size()==0);
    }

    //Put two cards in the pile
    pile.add(card3);
    pile.add(card1);

    SECTION("get top card in pile"){
        REQUIRE(pile.top().V()==ace);
        REQUIRE(pile.top().S()==hearts);
    }

    SECTION("get number of elements in pile"){
        REQUIRE(pile.size()==2);
    }

    //Add another card 
    pile.add(card4);

    SECTION("get new top card in pile"){
        REQUIRE(pile.top().V()==queen);
        REQUIRE(pile.top().S()==diamonds);
    }

    //remove top, save top in cardRemoved
    CardT cardRemoved = pile.rm();
    SECTION("get new top card in pile, check that card4 was removed"){
        REQUIRE(cardRemoved.V()==card4.V());
        REQUIRE(cardRemoved.S()==card4.S());
        REQUIRE(pile.top().V()==ace);
        REQUIRE(pile.top().S()==hearts);
    }

    //remove last remaining cards
    pile.rm();
    pile.rm();
    SECTION("check size to ensure all cards were successfully removed"){
        REQUIRE(pile.size()==0);
    }
}