#include "Card.hpp"
#include "unit_test_framework.hpp"
#include <iostream>

using namespace std;

//need more test cases

TEST(test_card_ctor) {
    Card c(ACE, HEARTS);
    Card card;
    ASSERT_EQUAL(ACE, c.get_rank());
    ASSERT_EQUAL(HEARTS, c.get_suit());
    ASSERT_EQUAL(TWO, card.get_rank());
    ASSERT_EQUAL(SPADES, card.get_suit());

}

TEST(test_card_suit_and_rank) {
    Card four_clubs = Card(FOUR, CLUBS);
    ASSERT_EQUAL(four_clubs.get_rank(), FOUR);
    ASSERT_EQUAL(four_clubs.get_suit(), CLUBS);

    Card five_hearts = Card(FIVE, HEARTS);
    ASSERT_EQUAL(five_hearts.get_rank(), FIVE);
    ASSERT_EQUAL(five_hearts.get_suit(), HEARTS);
    ASSERT_FALSE(five_hearts.is_face_or_ace());
}

TEST(test_card_type) {
    Card five_diamonds = Card(FIVE, DIAMONDS);
    Card jack_diamonds = Card(JACK, DIAMONDS);
    Card jack_hearts = Card(JACK, HEARTS);
    ASSERT_FALSE(five_diamonds.is_face_or_ace());
    ASSERT_FALSE(five_diamonds.is_right_bower(CLUBS));
    ASSERT_FALSE(five_diamonds.is_left_bower(CLUBS));
    ASSERT_FALSE(five_diamonds.is_trump(CLUBS));
    ASSERT_TRUE(jack_diamonds.is_face_or_ace());
    ASSERT_TRUE(jack_diamonds.is_right_bower(DIAMONDS));
    ASSERT_TRUE(jack_hearts.is_left_bower(DIAMONDS));
    ASSERT_TRUE(jack_diamonds.is_trump(DIAMONDS));
}

TEST(test_is_trump){
    Card six_diamonds = Card(SIX, DIAMONDS);
    Card six_hearts = Card(SIX, HEARTS);
    Card six_spades = Card(SIX, SPADES);
    Card six_clubs = Card(SIX, CLUBS);
    Card jack_diamonds = Card(JACK, DIAMONDS);
    ASSERT_TRUE(six_diamonds.is_trump(DIAMONDS));
    ASSERT_TRUE(six_hearts.is_trump(HEARTS));
    ASSERT_TRUE(six_spades.is_trump(SPADES));
    ASSERT_TRUE(six_clubs.is_trump(CLUBS));
    //left bower
    ASSERT_TRUE(jack_diamonds.is_trump(HEARTS));
    ASSERT_FALSE(jack_diamonds.is_trump(CLUBS));
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

TEST(test_greater_and_less){
    Card six_diamonds = Card(SIX, DIAMONDS);
    Card six_spades = Card(SIX, SPADES);
    ASSERT_TRUE(six_spades < six_diamonds);
    ASSERT_TRUE(six_diamonds > six_spades);
}

TEST(test_card_greater_than) {
    Card card1(QUEEN, CLUBS); 
    Card card2(TEN, DIAMONDS);

    ASSERT_TRUE(card1 > card2);

    // Additional test with equal ranks
    Card card3(QUEEN, HEARTS);
    ASSERT_TRUE(card1 > card3);

    // Additional test with different suits
    Card card4(EIGHT, CLUBS); 
    ASSERT_TRUE(card1 > card4);
}

TEST(test_less_than_or_equal_to){
    Card card1(TEN, DIAMONDS);   
    Card card2(TEN, DIAMONDS);  
    Card card3(QUEEN, CLUBS);

    ASSERT_TRUE(card1 <= card3);
    ASSERT_TRUE(card1 <= card2);
}

TEST(test_card_equal) {
    Card card1(TEN, DIAMONDS);   
    Card card2(TEN, DIAMONDS);  
    Card card3(QUEEN, CLUBS);

    
    ASSERT_TRUE(card1 == card2);
    ASSERT_FALSE(card1 == card3);
}

TEST(test_card_not_equal) {
    Card card1(TEN, DIAMONDS);   
    Card card2(TEN, DIAMONDS);  
    Card card3(QUEEN, CLUBS);

    ASSERT_TRUE(card1 != card3);
    ASSERT_FALSE(card1 != card2);
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

TEST(test_get_suit_trump) {
    Card three_spades = Card(THREE, SPADES);
    Card five_hearts = Card(FIVE, HEARTS);
    Card seven_clubs = Card(SEVEN, CLUBS);
    Card two_hearts = Card(TWO, HEARTS);
    Card nine_spades = Card(NINE, SPADES);
    Card left_bower = Card(JACK, SPADES);
    ASSERT_EQUAL(three_spades.get_suit(CLUBS), SPADES);
    ASSERT_EQUAL(five_hearts.get_suit(DIAMONDS), HEARTS);
    ASSERT_EQUAL(seven_clubs.get_suit(SPADES), CLUBS);
    ASSERT_EQUAL(two_hearts.get_suit(HEARTS), HEARTS);
    ASSERT_EQUAL(nine_spades.get_suit(HEARTS), SPADES);
    ASSERT_EQUAL(left_bower.get_suit(CLUBS), CLUBS)
}

TEST(test_is_face_or_ace){
    Card jack_diamonds = Card(JACK, DIAMONDS);
    Card queen_diamonds = Card(QUEEN, DIAMONDS);
    Card king_diamonds = Card(KING, DIAMONDS);
    Card ace_diamonds = Card(ACE, DIAMONDS);
    Card five_diamonds = Card(FIVE, DIAMONDS);
    Card two_spades = Card(TWO, SPADES);

    ASSERT_TRUE(jack_diamonds.is_face_or_ace());
    ASSERT_TRUE(queen_diamonds.is_face_or_ace());
    ASSERT_TRUE(king_diamonds.is_face_or_ace());
    ASSERT_TRUE(ace_diamonds.is_face_or_ace());
    ASSERT_FALSE(five_diamonds.is_face_or_ace());
    ASSERT_FALSE(two_spades.is_face_or_ace());
}

TEST_MAIN()
