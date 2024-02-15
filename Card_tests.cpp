#include "Card.hpp"
#include "unit_test_framework.hpp"
#include <iostream>

using namespace std;


TEST(test_card_ctor) {
    Card c(ACE, HEARTS);
    ASSERT_EQUAL(ACE, c.get_rank());
    ASSERT_EQUAL(HEARTS, c.get_suit());
}

TEST(test_card_suit_and_rank) {
    Card four_clubs = Card(FOUR, CLUBS);
    ASSERT_EQUAL(four_clubs.get_rank(), FOUR);
    ASSERT_EQUAL(four_clubs.get_suit(), CLUBS);

    Card five_hearts = Card(FIVE, HEARTS);
    ASSERT_EQUAL(five_hearts.get_rank(), FIVE);
    ASSERT_EQUAL(five_hearts.get_suit(), HEARTS);
}

TEST(test_card_type) {
    Card five_diamonds = Card(FIVE, DIAMONDS);
    Card jack_diamonds = Card(JACK, DIAMONDS);
    Card jack_hearts = Card(JACK, HEARTS);
    ASSERT_FALSE(five_diamonds.is_face_or_ace());
    ASSERT_FALSE(five_diamonds.is_right_bower(CLUBS));
    ASSERT_FALSE(five_diamonds.is_left_bower(CLUBS));
    ASSERT_FALSE(five_diamonds.is_trump(CLUBS));
    ASSERT_TRUE(jack_diamonds.is_right_bower(DIAMONDS));
    ASSERT_TRUE(jack_hearts.is_left_bower(DIAMONDS));
}

TEST(test_card_self_comparison) {
    Card six_spades = Card(SIX, SPADES);
    ASSERT_FALSE(six_spades < six_spades);
    ASSERT_TRUE(six_spades <= six_spades);
    ASSERT_FALSE(six_spades > six_spades);
    ASSERT_TRUE(six_spades >= six_spades);
    ASSERT_TRUE(six_spades == six_spades);
    ASSERT_FALSE(six_spades != six_spades);
}

TEST(test_Suit_next) {
    ASSERT_EQUAL(Suit_next(DIAMONDS), HEARTS);
    ASSERT_EQUAL(Suit_next(HEARTS), DIAMONDS);
    ASSERT_EQUAL(Suit_next(SPADES), CLUBS);
    ASSERT_EQUAL(Suit_next(CLUBS), SPADES);
}

TEST(test_Card_less_self) {
    Card seven_hearts = Card(SEVEN, HEARTS);
    ASSERT_FALSE(Card_less(seven_hearts, seven_hearts, CLUBS));
    ASSERT_FALSE(Card_less(seven_hearts, seven_hearts, seven_hearts, CLUBS));
}

TEST(test_Card_less){
    Card jack_spades = Card(JACK, SPADES);
    Card two_spades = Card(TWO, SPADES);
    Card jack_clubs = Card(JACK, CLUBS);
    Card king = Card(KING, HEARTS);
    Card ace = Card(ACE, DIAMONDS);
    Card queen = Card(QUEEN, DIAMONDS);
    ASSERT_TRUE(Card_less(jack_clubs, jack_spades, SPADES));
    ASSERT_TRUE(Card_less(jack_spades, jack_clubs, CLUBS));
    ASSERT_TRUE(Card_less(king, ace, DIAMONDS));
    //Card_less with led_card
    ASSERT_FALSE(Card_less(jack_spades, jack_clubs, two_spades, SPADES));
    ASSERT_TRUE(Card_less(king, ace, queen, SPADES));
}

TEST(test_card_insertion) {
    Card eight_clubs = Card(EIGHT, CLUBS);
    ostringstream oss;
    oss << eight_clubs;
    ASSERT_EQUAL(oss.str(), "Eight of Clubs");
}

TEST(test_card_extraction) {
    istringstream iss("Eight of Clubs");
    Card c;
    iss >> c;
    ASSERT_EQUAL(c, Card(EIGHT, CLUBS));
}

TEST_MAIN()
