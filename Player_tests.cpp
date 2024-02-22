#include "Player.hpp"
#include "unit_test_framework.hpp"

#include <iostream>

using namespace std;

TEST(test_player_get_name) {
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());

    delete alice;
}

// Add more tests here

// TEST(test_lead_card) {
//     Player * bob = Player_factory("Bob", "Simple");

//     Card card1 = Card(ACE, SPADES);
//     Card card2 = Card(TWO, HEARTS);
//     Card card3 = Card(KING, DIAMONDS);
//     Card card4 = Card(TEN, SPADES);
//     Card card5 = Card(KING, SPADES);
    

    
// }

TEST_MAIN()
