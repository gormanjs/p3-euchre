#include "Player.hpp"
#include "unit_test_framework.hpp"

#include <iostream>

using namespace std;

Card ace_spades(ACE, SPADES);
    Card two_spades(TWO, SPADES);
    Card two_clubs(TWO, CLUBS);
    Card king_diamonds(KING, DIAMONDS);
    Card king_clubs(KING, CLUBS);
    Card ten_spades(TEN, SPADES);
    Card king_spades(KING, SPADES);
    Card upcard1_jack_spades(JACK, SPADES);
    Card upcard2_jack_clubs(JACK, CLUBS);

TEST(test_player_get_name) {
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());

    delete alice;
}

// Add more tests here


TEST(test_play_card) {
    Player *player = Player_factory("TestPlayer", "Simple");
    player->add_card(ace_spades);
    player->add_card(two_spades);
    player->add_card(king_diamonds);
    player->add_card(ten_spades);
    player->add_card(king_spades);
    player->add_and_discard(two_clubs);
    Card led = Card(JACK, DIAMONDS);
    Card led2 = Card(QUEEN, CLUBS);
    Card led3 = Card(JACK,SPADES);

    //a simple player ignore the suit parameter and follows suit of lead card
    //has lead suit, plays highest of suit
    ASSERT_EQUAL(player->play_card(led, SPADES), king_diamonds);
    //does not have lead suit, plays lowest
    ASSERT_EQUAL(player->play_card(led2, DIAMONDS), two_spades);

    delete player;
}

TEST(test_make_trump){
    Player *player = Player_factory("TestPlayer", "Simple");
    player->add_card(ace_spades);
    player->add_card(two_spades);
    player->add_card(king_diamonds);
    player->add_card(ten_spades);
    player->add_card(king_spades);
    Card upcard = Card(QUEEN, SPADES);
    Suit order_up_suit = SPADES;
    //round 1 and will make trump
    ASSERT_TRUE(player->make_trump(upcard, false, 1, order_up_suit));
    delete player;

    Player *player1 = Player_factory("TestPlayer", "Simple");
    player1->add_card(ace_spades);
    player1->add_card(two_spades);
    player1->add_card(king_diamonds);
    player1->add_card(ten_spades);
    player1->add_card(king_spades);
    Card upcard1 = Card(QUEEN, HEARTS);
    Suit order_up_suit1 = SPADES;
    //round 2 and will make trump
    ASSERT_TRUE(player->make_trump(upcard1, false, 2, order_up_suit1));
    delete player1;

    //make tests for if the player WONT make trump
    Player *player2 = Player_factory("TestPlayer", "Simple");
    player2->add_card(ace_spades);
    player2->add_card(two_spades);
    player2->add_card(king_diamonds);
    player2->add_card(ten_spades);
    player2->add_card(king_spades);
    Card upcard2 = Card(QUEEN, HEARTS);
    Suit order_up_suit2 = SPADES;
    //round 1 and wont make trump
    ASSERT_FALSE(player2->make_trump(upcard2, false, 1,order_up_suit2));
    delete player2;

    Player *player3 = Player_factory("TestPlayer", "Simple");
    player3->add_card(ace_spades);
    player3->add_card(two_spades);
    player3->add_card(king_clubs);
    player3->add_card(ten_spades);
    player3->add_card(king_spades);
    Card upcard3 = Card(QUEEN, HEARTS);
    Suit order_up_suit3 = HEARTS;
    //round 2 and wont make trump
    ASSERT_FALSE(player3->make_trump(upcard3, false, 2, order_up_suit3));
    delete player3;

    //test screw the dealer
    Player *player4 = Player_factory("TestPlayer", "Simple");
    player4->add_card(ace_spades);
    player4->add_card(two_spades);
    player4->add_card(king_diamonds);
    player4->add_card(ten_spades);
    player4->add_card(king_spades);
    Card upcard4 = Card(QUEEN, SPADES);
    Suit order_up_suit4 = SPADES;
    //screw the dealer happens in round 2
    ASSERT_TRUE(player4->make_trump(upcard4, true, 2, order_up_suit4));
    delete player4;
}

TEST_MAIN()
