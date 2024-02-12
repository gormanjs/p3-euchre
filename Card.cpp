#include <cassert>
#include <iostream>
#include <array>
#include "Card.hpp"

using namespace std;

/////////////// Rank operator implementations - DO NOT CHANGE ///////////////

constexpr const char *const RANK_NAMES[] = {
  "Two",   // TWO
  "Three", // THREE
  "Four",  // FOUR
  "Five",  // FIVE
  "Six",   // SIX
  "Seven", // SEVEN
  "Eight", // EIGHT
  "Nine",  // NINE
  "Ten",   // TEN
  "Jack",  // JACK
  "Queen", // QUEEN
  "King",  // KING
  "Ace"    // ACE
};

//REQUIRES str represents a valid rank ("Two", "Three", ..., "Ace")
//EFFECTS returns the Rank correspoinding to str, for example "Two" -> TWO
Rank string_to_rank(const std::string &str) {
  for(int r = TWO; r <= ACE; ++r) {
    if (str == RANK_NAMES[r]) {
      return static_cast<Rank>(r);
    }
  }
  assert(false); // Input string didn't match any rank
  return {};
}

//EFFECTS Prints Rank to stream, for example "Two"
std::ostream & operator<<(std::ostream &os, Rank rank) {
  os << RANK_NAMES[rank];
  return os;
}

//REQUIRES If any input is read, it must be a valid rank
//EFFECTS Reads a Rank from a stream, for example "Two" -> TWO
std::istream & operator>>(std::istream &is, Rank &rank) {
  string str;
  if(is >> str) {
    rank = string_to_rank(str);
  }
  return is;
}



/////////////// Suit operator implementations - DO NOT CHANGE ///////////////

constexpr const char *const SUIT_NAMES[] = {
  "Spades",   // SPADES
  "Hearts",   // HEARTS
  "Clubs",    // CLUBS
  "Diamonds", // DIAMONDS
};

//REQUIRES str represents a valid suit ("Spades", "Hearts", "Clubs", or "Diamonds")
//EFFECTS returns the Suit correspoinding to str, for example "Clubs" -> CLUBS
Suit string_to_suit(const std::string &str) {
  for(int s = SPADES; s <= DIAMONDS; ++s) {
    if (str == SUIT_NAMES[s]) {
      return static_cast<Suit>(s);
    }
  }
  assert(false); // Input string didn't match any suit
  return {};
}

//EFFECTS Prints Suit to stream, for example "Spades"
std::ostream & operator<<(std::ostream &os, Suit suit) {
  os << SUIT_NAMES[suit];
  return os;
}

//REQUIRES If any input is read, it must be a valid suit
//EFFECTS Reads a Suit from a stream, for example "Spades" -> SPADES
std::istream & operator>>(std::istream &is, Suit &suit) {
  string str;
  if (is >> str) {
    suit = string_to_suit(str);
  }
  return is;
}


/////////////// Write your implementation for Card below ///////////////


// NOTE: We HIGHLY recommend you check out the operator overloading
// tutorial in the project spec before implementing
// the following operator overload functions:
//   operator<<
//   operator>>
//   operator<
//   operator<=
//   operator>
//   operator>=
//   operator==
//   operator!=

Rank string_to_rank(const std::string &str){
  string uppercaseStr = str;

  for(int i = 0; i < str.length(); i++){
    uppercaseStr[i] =toupper(uppercaseStr[i]);
  }
 if (uppercaseStr == "TWO") {
        return TWO;
    } else if (uppercaseStr == "THREE") {
        return THREE;
    } else if (uppercaseStr == "FOUR") {
        return FOUR;
    } else if (uppercaseStr == "FIVE") {
        return FIVE;
    } else if (uppercaseStr == "SIX") {
        return SIX;
    } else if (uppercaseStr == "SEVEN") {
        return SEVEN;
    } else if (uppercaseStr == "EIGHT") {
        return EIGHT;
    } else if (uppercaseStr == "NINE") {
        return NINE;
    } else if (uppercaseStr == "TEN") {
        return TEN;
    } else if (uppercaseStr == "JACK") {
        return JACK;
    } else if (uppercaseStr == "QUEEN") {
        return QUEEN;
    } else if (uppercaseStr == "KING") {
        return KING;
    } 
    else (uppercaseStr == "ACE");
    {
        return ACE;
    }
}

std::ostream & operator<<(std::ostream &os, Rank rank){
  os << rank;
}

std::istream & operator>>(std::istream &is, Rank &rank){
  is >> rank;
}

Suit string_to_suit(const std::string &str){
  string uppercaseStr = str;

  for(int i = 0; i < str.length(); i++){
    uppercaseStr[i] =toupper(uppercaseStr[i]);
  }
  if(uppercaseStr == "SPADES"){
    return SPADES;
  }else if(uppercaseStr == "HEARTS"){
    return HEARTS;
  } else if(uppercaseStr == "CLUBS"){
    return CLUBS;
  } else (uppercaseStr == "DIAMONDS");
  {
    return DIAMONDS;
  }
}

Card::Card(){
  Rank(0), Suit(0);
};

Card::Card(Rank rank_in, Suit suit_in){
  rank = rank_in;
  suit = suit_in;
}

Rank Card::get_rank() const{
  return rank;
}

Suit Card::get_suit() const{
  return suit;
}

Suit Card::get_suit(Suit trump) const{
  return trump;
}

bool Card::is_face_or_ace() const{
  return rank == 9 || rank == 10 || rank == 11 || rank == 12;
}

bool Card::is_right_bower(Suit trump) const{
  return rank == 9 && suit == trump;
}

bool Card::is_left_bower(Suit trump) const{
  int next = 4;
  if(trump == 0){
    next = 2;
  }
  else if(trump == 1){
    next = 3;
  }
  else if(trump == 2){
    next = 0;
  }
  else if(trump == 3){
    next = 1;
  }
  return rank == 9 && suit == next;
}

bool Card::is_trump(Suit trump) const{
  return suit == trump || is_left_bower(trump);
}

std::ostream & operator<<(std::ostream &os, const Card &card){
  os << card.get_rank() << " of " << card.get_suit();
}

std::istream & operator>>(std::istream &is, Card &card){
  string filler;
  is >> card.rank >> filler >> card.suit;
}

bool operator<(const Card &lhs, const Card &rhs){
  return lhs.get_rank() < rhs.get_rank();
}

bool operator<=(const Card &lhs, const Card &rhs){
  return lhs.get_rank() <= rhs.get_rank();
}

bool operator>(const Card &lhs, const Card &rhs){

}

bool operator>=(const Card &lhs, const Card &rhs){

}

bool operator==(const Card &lhs, const Card &rhs){

}

bool operator!=(const Card &lhs, const Card &rhs){

}

Suit Suit_next(Suit suit){
  int next = 4;
  if(suit == 0){
    return CLUBS;
  }
  else if(suit== 1){
   return DIAMONDS;
  }
  else if(suit == 2){
    return SPADES;
  }
  else if(suit== 3){
    return HEARTS;
  }
}

bool Card_less(const Card &a, const Card &b, Suit trump){
  
}