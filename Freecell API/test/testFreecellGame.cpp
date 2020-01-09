//Andrew Lucentini, lucenta
#include "catch.h"
#include "FreecellGame.h"

TEST_CASE ("tests for FreecellGame", "[FreecellGame]"){
    //Deck of cards
    vector<CardT> deck = {
    CardT(two,spades),  CardT(nine,diamonds),CardT(ace,clubs),   CardT(jack,clubs),    CardT(seven,clubs),   CardT(four,diamonds),CardT(three,diamonds),
    CardT(eight,hearts),CardT(five,spades),  CardT(three,clubs), CardT(eight,clubs),   CardT(nine,hearts),   CardT(eight,spades), CardT(six,spades),
    CardT(seven,spades),CardT(jack,hearts),  CardT(four,spades), CardT(ace,spades),    CardT(two,hearts),    CardT(king,clubs),   CardT(queen,diamonds),
    CardT(five,clubs),  CardT(jack,diamonds),CardT(king,hearts), CardT(five,hearts),    CardT(eight,diamonds),CardT(six,clubs),    CardT(three,hearts),
    CardT(ten,spades),  CardT(seven,hearts), CardT(queen,hearts),CardT(jack,spades),   CardT(nine,clubs),    CardT(four,clubs),
    CardT(three,spades),CardT(six,diamonds), CardT(two,diamonds),CardT(six,hearts),    CardT(five,diamonds), CardT(ace,hearts),
    CardT(ten,hearts),  CardT(ten,diamonds), CardT(four,hearts), CardT(seven,diamonds),CardT(ace,diamonds),  CardT(two,clubs),
    CardT(queen,spades),CardT(queen,clubs),  CardT(ten,clubs),   CardT(king,diamonds), CardT(king,spades),   CardT(nine,spades)};

    //Create freecell Game
    FreecellGame game = FreecellGame();

    SECTION("attempt to create game with incorrect number of cards"){
        vector<CardT> deckWrong = {CardT(nine,clubs),CardT(ten,hearts)};
        REQUIRE_THROWS_AS(game.newGame(deckWrong), std::exception);
    }

    SECTION("create game with duplicate cards in the deck, check error was raised"){
         vector<CardT> duplicate = {
    CardT(two,spades),  CardT(nine,clubs),CardT(ace,clubs),   CardT(jack,clubs),    CardT(seven,clubs),   CardT(four,diamonds),CardT(three,diamonds),
    CardT(eight,hearts),CardT(five,spades),  CardT(three,clubs), CardT(eight,clubs),   CardT(nine,hearts),   CardT(eight,spades), CardT(six,spades),
    CardT(seven,spades),CardT(jack,hearts),  CardT(four,spades), CardT(ace,spades),    CardT(two,hearts),    CardT(king,clubs),   CardT(queen,diamonds),
    CardT(five,clubs),  CardT(jack,diamonds),CardT(king,hearts), CardT(five,hearts),    CardT(eight,diamonds),CardT(six,clubs),    CardT(three,hearts),
    CardT(ten,spades),  CardT(seven,hearts), CardT(queen,hearts),CardT(jack,spades),   CardT(nine,clubs),    CardT(four,clubs),
    CardT(three,spades),CardT(six,diamonds), CardT(two,diamonds),CardT(six,hearts),    CardT(five,diamonds), CardT(ace,hearts),
    CardT(ten,hearts),  CardT(ten,diamonds), CardT(four,hearts), CardT(seven,diamonds),CardT(ace,diamonds),  CardT(two,clubs),
    CardT(queen,spades),CardT(queen,clubs),  CardT(ten,clubs),   CardT(king,diamonds), CardT(king,spades),   CardT(nine,spades)};

        REQUIRE_THROWS_AS(game.newGame(duplicate), std::exception);
    }

    //Create new game with proper deck
    game.newGame(deck);

    SECTION("check that the sizes of the piles are correct"){
        for (int i=0; i < 4;i++){
            REQUIRE(game.size(foundation,i)==0);
            REQUIRE(game.size(foundation,i)==0);
        }
        for (int i=0; i < 4;i++){
            REQUIRE(game.size(tableau,i)==7);
        }

        for (int i=4; i < 8;i++){
            REQUIRE(game.size(tableau,i)==6);
        }
    }

    SECTION("check that the size method produces an error when incorrect index is used for a given pile type"){
        REQUIRE_THROWS_AS(game.size(foundation,4), std::exception);
        REQUIRE_THROWS_AS(game.size(foundation,-1), std::exception);
        REQUIRE_THROWS_AS(game.size(tableau,8), std::exception);
        REQUIRE_THROWS_AS(game.size(tableau,-1), std::exception);
        REQUIRE_THROWS_AS(game.size(cell,4), std::exception);
        REQUIRE_THROWS_AS(game.size(cell,-1), std::exception);
    }

    SECTION("check the correct cards are in the top of the piles by essentially testing the get function and the newGame function"){
        REQUIRE((game.getCard(tableau,0).S() == diamonds && game.getCard(tableau,0).V() == three));
        REQUIRE((game.getCard(tableau,1).S() == spades && game.getCard(tableau,1).V() == six));
        REQUIRE((game.getCard(tableau,2).S() == diamonds && game.getCard(tableau,2).V() == queen));
        REQUIRE((game.getCard(tableau,3).S() == hearts && game.getCard(tableau,3).V() == three));
        REQUIRE((game.getCard(tableau,4).S() == clubs && game.getCard(tableau,4).V() == four));
        REQUIRE((game.getCard(tableau,5).S() == hearts && game.getCard(tableau,5).V() == ace));
        REQUIRE((game.getCard(tableau,6).S() == clubs && game.getCard(tableau,6).V() == two));
        REQUIRE((game.getCard(tableau,7).S() == spades && game.getCard(tableau,7).V() == nine));
    }

    SECTION("check the get method produces the correct errors"){
        REQUIRE_THROWS_AS(game.getCard(tableau,8), std::exception);
        REQUIRE_THROWS_AS(game.getCard(cell,0), std::exception);
        REQUIRE_THROWS_AS(game.getCard(cell,3), std::exception);
        REQUIRE_THROWS_AS(game.getCard(foundation,1), std::exception);
        REQUIRE_THROWS_AS(game.getCard(foundation,3), std::exception);
    }

    /* Current game state looks like this:

        Cell:                                       Foundation Pile:
        0       1       2        3                      0       1        2         3   
        empty  empty   empty   empty                empty     empty    empty     empty


        Tableau Piles:

        0                   1                 2                 3                 4                5               6                 7
    (two,spades)       (eight,hearts)   (seven,spades)    (five,clubs)      (ten,spades)    (three,spades)   (ten,hearts)      (queen,spades)
    (nine,diamonds)    (five,spades)    (jack,hearts)     (jack,diamonds)   (seven,hearts)  (six,diamonds)   (ten,diamonds)    (queen,clubs)
    (ace,clubs)        (three,clubs)    (four,spades)     (king,hearts)     (queen,hearts)  (two,diamonds)   (four,hearts)     (ten,clubs)
    (jack,clubs)       (eight,clubs)    (ace,spades)      (five,hearts)     (jack,spades)   (six,hearts)     (seven,diamonds)  (king,diamonds)
    (seven,clubs)      (nine,hearts)    (two,hearts)      (eight,diamonds)  (nine,clubs)    (five,diamonds)  (ace,diamonds)    (king,spades)
    (four,diamonds)    (eight,spades)   (king,clubs)      (six,clubs)       (four,clubs)    (ace,hearts)     (two,clubs)       (nine,spades)
    (three,diamonds)   (six,spades)     (queen,diamonds)  (three,hearts)
    */

    SECTION("Make invalid moves between tableau piles"){
        REQUIRE_THROWS_AS(game.moveCard(tableau,tableau, -1, 9), std::exception);
        REQUIRE_THROWS_AS(game.moveCard(tableau,tableau, 9, -1), std::exception);
        REQUIRE_THROWS_AS(game.moveCard(tableau,tableau, 0, 1), std::exception);
        REQUIRE_THROWS_AS(game.moveCard(tableau,tableau, 3, 0), std::exception);
        REQUIRE_THROWS_AS(game.moveCard(tableau,tableau, 4, 0), std::exception);
    }

    //Make valid moves between tableau piles, check that the state of the game has been updated by checking the top card of the modified piles
    game.moveCard(tableau,tableau, 6, 0);
    game.moveCard(tableau,tableau, 3, 4);
    /* Current game state looks like this:

        Cell:                                       Foundation Pile:
        0       1       2        3                      0       1        2         3   
        empty  empty   empty   empty                empty     empty    empty     empty


        Tableau Piles:

        0                   1                 2                 3                 4                5               6                 7
    (two,spades)       (eight,hearts)   (seven,spades)    (five,clubs)      (ten,spades)    (three,spades)   (ten,hearts)      (queen,spades)
    (nine,diamonds)    (five,spades)    (jack,hearts)     (jack,diamonds)   (seven,hearts)  (six,diamonds)   (ten,diamonds)    (queen,clubs)
    (ace,clubs)        (three,clubs)    (four,spades)     (king,hearts)     (queen,hearts)  (two,diamonds)   (four,hearts)     (ten,clubs)
    (jack,clubs)       (eight,clubs)    (ace,spades)      (five,hearts)     (jack,spades)   (six,hearts)     (seven,diamonds)  (king,diamonds)
    (seven,clubs)      (nine,hearts)    (two,hearts)      (eight,diamonds)  (nine,clubs)    (five,diamonds)  (ace,diamonds)    (king,spades)
    (four,diamonds)    (eight,spades)   (king,clubs)      (six,clubs)       (four,clubs)    (ace,hearts)                       (nine,spades)
    (three,diamonds)   (six,spades)     (queen,diamonds)                    (three,hearts)
    (two,clubs)
    */


    SECTION("check the correct cards were moved"){
        REQUIRE((game.getCard(tableau,0).S() == clubs && game.getCard(tableau,0).V() == two));
        REQUIRE((game.getCard(tableau,4).S() == hearts && game.getCard(tableau,4).V() == three));
        REQUIRE((game.getCard(tableau,6).S() == diamonds && game.getCard(tableau,6).V() == ace));
        REQUIRE((game.getCard(tableau,3).S() == clubs && game.getCard(tableau,3).V() == six));
    }

    //Make valid moves between tableau piles and cell piles, check that the state of the game has been updated by checking the top card of the modified piles
    game.moveCard(tableau,cell, 1, 0);
    game.moveCard(tableau,cell, 7, 1);
    game.moveCard(tableau,cell, 3, 3);
    game.moveCard(cell,cell, 3, 2);
    game.moveCard(tableau,cell, 2, 3);
    game.moveCard(cell,tableau, 3, 2);

    /* Current game state looks like this:

        Cell:                                                       Foundation Pile:
        0             1              2           3                    0          1        2         3   
   (six,spades)  (nine,spades)   (six,clubs)   empty                 empty     empty    empty     empty


        Tableau Piles:

        0                   1                 2                 3                 4                5               6                 7
    (two,spades)       (eight,hearts)   (seven,spades)    (five,clubs)      (ten,spades)    (three,spades)   (ten,hearts)      (queen,spades)
    (nine,diamonds)    (five,spades)    (jack,hearts)     (jack,diamonds)   (seven,hearts)  (six,diamonds)   (ten,diamonds)    (queen,clubs)
    (ace,clubs)        (three,clubs)    (four,spades)     (king,hearts)     (queen,hearts)  (two,diamonds)   (four,hearts)     (ten,clubs)
    (jack,clubs)       (eight,clubs)    (ace,spades)      (five,hearts)     (jack,spades)   (six,hearts)     (seven,diamonds)  (king,diamonds)
    (seven,clubs)      (nine,hearts)    (two,hearts)      (eight,diamonds)  (nine,clubs)    (five,diamonds)  (ace,diamonds)    (king,spades)
    (four,diamonds)    (eight,spades)   (king,clubs)                        (four,clubs)    (ace,hearts)                       
    (three,diamonds)                    (queen,diamonds)                    (three,hearts)
    (two,clubs)
    */

    SECTION("check the correct cards were moved"){
        REQUIRE((game.getCard(cell,0).S() == spades && game.getCard(cell,0).V() == six));
        REQUIRE((game.getCard(cell,1).S() == spades && game.getCard(cell,1).V() == nine));
        REQUIRE((game.getCard(cell,2).S() == clubs && game.getCard(cell,2).V() == six));
        REQUIRE((game.getCard(tableau,1).S() == spades && game.getCard(tableau,1).V() == eight));
        REQUIRE((game.getCard(tableau,7).S() == spades && game.getCard(tableau,7).V() == king));
        REQUIRE((game.getCard(tableau,3).S() == diamonds && game.getCard(tableau,3).V() == eight));
    }

    SECTION("make invalid moves between tableau piles and cell piles"){
        REQUIRE_THROWS_AS(game.moveCard(tableau,cell, -1, 9), std::exception);
        REQUIRE_THROWS_AS(game.moveCard(cell,tableau, 4, 3), std::exception);
        REQUIRE_THROWS_AS(game.moveCard(tableau,cell, 3, 4), std::exception);
        REQUIRE_THROWS_AS(game.moveCard(cell,tableau, 2, 8), std::exception);
        REQUIRE_THROWS_AS(game.moveCard(cell,tableau, 3, 2), std::exception);
        REQUIRE_THROWS_AS(game.moveCard(cell,tableau, 2, 2), std::exception);
        REQUIRE_THROWS_AS(game.moveCard(cell,cell, 1, 2), std::exception);
        REQUIRE_THROWS_AS(game.moveCard(tableau,cell, 4, 2), std::exception);
        REQUIRE_THROWS_AS(game.moveCard(tableau,cell, 7, 0), std::exception);
        REQUIRE_THROWS_AS(game.moveCard(cell,tableau, 1, 6), std::exception);
    }

    //Make valid moves between tableau piles and foundation piles
    game.moveCard(tableau,foundation, 5, 0);
    game.moveCard(tableau,foundation, 6, 1);
    game.moveCard(tableau,tableau, 2, 7);
    game.moveCard(tableau,cell, 2, 3);
    game.moveCard(tableau,foundation, 2, 0);
    game.moveCard(tableau,foundation, 2, 2);

    /* Current game state looks like this:

        Cell:                                                           Foundation Pile:
        0             1              2              3                         0             1                 2            3   
   (six,spades)  (nine,spades)   (six,clubs)   (king,clubs)             (ace,hearts)  (ace,diamonds)     (ace,spades)    empty
                                                                        (two,hearts)   

        Tableau Piles:

        0                   1                 2                 3                 4                5               6                 7
    (two,spades)       (eight,hearts)   (seven,spades)    (five,clubs)      (ten,spades)    (three,spades)   (ten,hearts)      (queen,spades)
    (nine,diamonds)    (five,spades)    (jack,hearts)     (jack,diamonds)   (seven,hearts)  (six,diamonds)   (ten,diamonds)    (queen,clubs)
    (ace,clubs)        (three,clubs)    (four,spades)     (king,hearts)     (queen,hearts)  (two,diamonds)   (four,hearts)     (ten,clubs)
    (jack,clubs)       (eight,clubs)                      (five,hearts)     (jack,spades)   (six,hearts)     (seven,diamonds)  (king,diamonds)
    (seven,clubs)      (nine,hearts)                      (eight,diamonds)  (nine,clubs)    (five,diamonds)                    (king,spades)
    (four,diamonds)    (eight,spades)                                       (four,clubs)                                       (queen,diamonds)     
    (three,diamonds)                                                        (three,hearts)
    (two,clubs)
    */
 
    SECTION("check the correct cards were moved"){ 
        REQUIRE((game.getCard(tableau,5).S() == diamonds && game.getCard(tableau,5).V() == five));
        REQUIRE((game.getCard(tableau,6).S() == diamonds && game.getCard(tableau,6).V() == seven));
        REQUIRE((game.getCard(tableau,2).S() == spades && game.getCard(tableau,2).V() == four));
        REQUIRE((game.getCard(foundation,0).S() == hearts && game.getCard(foundation,0).V() == two));
        REQUIRE((game.getCard(foundation,1).S() == diamonds && game.getCard(foundation,1).V() == ace));
    }

    SECTION("make invalid moves between tableau piles and foundation piles"){
        REQUIRE_THROWS_AS(game.moveCard(tableau,foundation, -1, 9), std::exception);
        REQUIRE_THROWS_AS(game.moveCard(tableau,foundation, 7, 4), std::exception);
        REQUIRE_THROWS_AS(game.moveCard(tableau,foundation, 5, 0), std::exception);
        REQUIRE_THROWS_AS(game.moveCard(tableau,foundation, 7, 3), std::exception);
        REQUIRE_THROWS_AS(game.moveCard(tableau,foundation, 0, 2), std::exception);
        REQUIRE_THROWS_AS(game.moveCard(tableau,foundation, 0, 3), std::exception);
        REQUIRE_THROWS_AS(game.moveCard(foundation, tableau, 2, 2), std::exception);
        REQUIRE_THROWS_AS(game.moveCard(foundation, tableau, 3, 0), std::exception);
        REQUIRE_THROWS_AS(game.moveCard(foundation, tableau, 0, 2), std::exception);
        REQUIRE_THROWS_AS(game.moveCard(foundation, tableau, 1, 6), std::exception);
    }

    //Make valid moves between cell piles and foundation piles
    game.moveCard(cell,tableau, 2, 6);
    game.moveCard(tableau,cell, 4, 2);
    game.moveCard(cell,foundation, 2, 0);
    game.moveCard(foundation,cell, 1, 2);
    game.moveCard(foundation,tableau, 0, 2);
    /* Current game state looks like this:

        Cell:                                                           Foundation Pile:
        0             1               2                   3                         0             1                 2            3   
   (six,spades)  (nine,spades)     (ace,diamonds)    (king,clubs)             (ace,hearts)      empty          (ace,spades)    empty
                                                                              (two,hearts)   
                                                                              
        Tableau Piles:

        0                   1                 2                 3                 4                5               6                 7
    (two,spades)       (eight,hearts)   (seven,spades)    (five,clubs)      (ten,spades)    (three,spades)   (ten,hearts)      (queen,spades)
    (nine,diamonds)    (five,spades)    (jack,hearts)     (jack,diamonds)   (seven,hearts)  (six,diamonds)   (ten,diamonds)    (queen,clubs)
    (ace,clubs)        (three,clubs)    (four,spades)     (king,hearts)     (queen,hearts)  (two,diamonds)   (four,hearts)     (ten,clubs)
    (jack,clubs)       (eight,clubs)    (three,hearts)    (five,hearts)     (jack,spades)   (six,hearts)     (seven,diamonds)  (king,diamonds)
    (seven,clubs)      (nine,hearts)                      (eight,diamonds)  (nine,clubs)    (five,diamonds)  (six,clubs)       (king,spades)
    (four,diamonds)    (eight,spades)                                       (four,clubs)                                       (queen,diamonds)     
    (three,diamonds)                                                        
    (two,clubs)
    */
    SECTION("check the correct cards were moved"){ 
        REQUIRE((game.getCard(tableau,4).S() == clubs && game.getCard(tableau,4).V() == four));
        REQUIRE((game.getCard(tableau,6).S() == clubs && game.getCard(tableau,6).V() == six));
        REQUIRE((game.getCard(foundation,0).S() == hearts && game.getCard(foundation,0).V() == two));
        REQUIRE((game.getCard(cell,2).S() == diamonds && game.getCard(cell,2).V() == ace));
        REQUIRE((game.getCard(tableau,2).S() == hearts && game.getCard(tableau,2).V() == three));
        REQUIRE((game.size(foundation,2) == 1));
    }
    SECTION("make invalid moves between tableau piles and foundation piles"){
        REQUIRE_THROWS_AS(game.moveCard(cell,foundation, -1, 9), std::exception);
        REQUIRE_THROWS_AS(game.moveCard(cell,foundation, 4, 4), std::exception);
        REQUIRE_THROWS_AS(game.moveCard(cell,foundation, 5, 0), std::exception);
        REQUIRE_THROWS_AS(game.moveCard(cell,foundation, 2, 0), std::exception);
        REQUIRE_THROWS_AS(game.moveCard(cell,foundation, 0, 3), std::exception);
        REQUIRE_THROWS_AS(game.moveCard(foundation,cell, 0, 3), std::exception);
        REQUIRE_THROWS_AS(game.moveCard(foundation,cell, 1, 5), std::exception);
        REQUIRE_THROWS_AS(game.moveCard(foundation,cell, 2, 0), std::exception);
        REQUIRE_THROWS_AS(game.moveCard(foundation,cell, 3, 1), std::exception);
    }
    SECTION("check sizes of random piles are correct"){
        REQUIRE((game.size(cell,0)==1));
        REQUIRE((game.size(cell,2)==1));
        REQUIRE((game.size(tableau,2)==4));
        REQUIRE((game.size(tableau,4)==6));
    }    
    
    SECTION("determine if game has been won"){
        REQUIRE((game.gameWon()==false));
    }

    SECTION("determine if there are no moves available"){
        REQUIRE((game.noValidMoves()==false));
    }

    //Make more valid moves and ensure no errors are raised
    game.moveCard(cell,foundation,2,1);
    game.moveCard(tableau,tableau,5,6);
    game.moveCard(tableau,cell,5,2);
    game.moveCard(tableau,foundation,5,1);


    /* Current game state looks like this:

        Cell:                                                              Foundation Pile:
        0             1               2                   3                         0                 1                  2            3   
   (six,spades)  (nine,spades)    (six,hearts)       (king,clubs)            (ace,hearts)      (ace,diamonds)       (ace,spades)    empty
                                                                             (two,hearts)      (two,diamonds) 
                                                                              
        Tableau Piles:

        0                   1                 2                 3                 4                5               6                 7
    (two,spades)       (eight,hearts)   (seven,spades)    (five,clubs)      (ten,spades)    (three,spades)   (ten,hearts)      (queen,spades)
    (nine,diamonds)    (five,spades)    (jack,hearts)     (jack,diamonds)   (seven,hearts)  (six,diamonds)   (ten,diamonds)    (queen,clubs)
    (ace,clubs)        (three,clubs)    (four,spades)     (king,hearts)     (queen,hearts)                   (four,hearts)     (ten,clubs)
    (jack,clubs)       (eight,clubs)    (three,hearts)    (five,hearts)     (jack,spades)                    (seven,diamonds)  (king,diamonds)
    (seven,clubs)      (nine,hearts)                      (eight,diamonds)  (nine,clubs)                     (six,clubs)       (king,spades)
    (four,diamonds)    (eight,spades)                                       (four,clubs)                     (five,diamonds)   (queen,diamonds)     
    (three,diamonds)                                                        
    (two,clubs)
    */


    SECTION("make more invalid moves between all piles"){
        REQUIRE_THROWS_AS(game.moveCard(cell,foundation, 0, 1), std::exception);
        REQUIRE_THROWS_AS(game.moveCard(tableau,foundation, 4, 1), std::exception);
        REQUIRE_THROWS_AS(game.moveCard(tableau,tableau, 2, 0), std::exception);
        REQUIRE_THROWS_AS(game.moveCard(tableau,tableau, 6, 5), std::exception);
        REQUIRE_THROWS_AS(game.moveCard(cell,foundation, 2, 3), std::exception);
    }

    //reset the game
    game.newGame(deck);

    SECTION("check that the sizes of the piles are reset"){
        for (int i=0; i < 4;i++){
            REQUIRE(game.size(foundation,i)==0);
            REQUIRE(game.size(foundation,i)==0);
        }
        for (int i=0; i < 4;i++){
            REQUIRE(game.size(tableau,i)==7);
        }

        for (int i=4; i < 8;i++){
            REQUIRE(game.size(tableau,i)==6);
        }
    }

    SECTION("check the correct cards are in the top of the piles from the deck"){
        REQUIRE((game.getCard(tableau,0).S() == diamonds && game.getCard(tableau,0).V() == three));
        REQUIRE((game.getCard(tableau,1).S() == spades && game.getCard(tableau,1).V() == six));
        REQUIRE((game.getCard(tableau,2).S() == diamonds && game.getCard(tableau,2).V() == queen));
        REQUIRE((game.getCard(tableau,3).S() == hearts && game.getCard(tableau,3).V() == three));
        REQUIRE((game.getCard(tableau,4).S() == clubs && game.getCard(tableau,4).V() == four));
        REQUIRE((game.getCard(tableau,5).S() == hearts && game.getCard(tableau,5).V() == ace));
        REQUIRE((game.getCard(tableau,6).S() == clubs && game.getCard(tableau,6).V() == two));
        REQUIRE((game.getCard(tableau,7).S() == spades && game.getCard(tableau,7).V() == nine));
    }
}
