#include "Player.hpp"
#include "unit_test_framework.hpp"

#include <iostream>

using namespace std;


    Card ace_spades(ACE, SPADES);
    Card two_spades(TWO, SPADES);
    Card two_clubs(TWO, CLUBS);
    Card king_diamonds(KING, DIAMONDS);
    Card ten_spades(TEN, SPADES);
    Card king_spades(KING, SPADES);
    Card upcard1_jack_spades(JACK, SPADES);
    Card upcard2_jack_clubs(JACK, CLUBS);

TEST(test_player_get_name) {
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());

    delete alice;
}


TEST(test_lead_card) {
   


    
    

    
}
TEST(test_Player_simple) {
Player *player = Player_factory("TestPlayer", "Simple");
    //all trump cards
    player->add_card(ace_spades);
    player->add_card(two_spades);
    player->add_card(upcard1_jack_spades);
    player->add_card(ten_spades);
    player->add_card(king_spades);
    player->add_and_discard(upcard2_jack_clubs);
    ASSERT_EQUAL(player->lead_card(SPADES), upcard1_jack_spades)
    //not all trumps
    player->add_card(ace_spades);
    player->add_card(two_spades);
    player->add_card(king_diamonds);
    player->add_card(ten_spades);
    player->add_card(king_spades);
    player->add_and_discard(two_clubs);
    ASSERT_EQUAL(player->lead_card(SPADES), king_diamonds);


}
TEST_MAIN()