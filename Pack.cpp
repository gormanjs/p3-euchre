#include "Pack.hpp"

Pack::Pack() : next(0) {
    int index = 0;
    for (int suit = 0; suit < 4; suit++) {
        for (int rank = NINE; rank < 13; rank++) {
            cards[index] = Card(static_cast<Rank>(rank), static_cast<Suit>(suit));
            index++;
        }
    }
}

Pack::Pack(std::istream& pack_input){
    
    std::string rank;
    std::string suit;

    for (int i = 0; i < PACK_SIZE; i++){
        pack_input >> rank >> suit;
        Rank r = string_to_rank(rank);
        Suit s = string_to_suit(suit);
        cards[i] = Card(r, s);
    }
    

}

Card Pack::deal_one() {
    return cards[next++];
}

void Pack::reset() {
    
    next = 0;

}

void Pack::shuffle() {
    std::array<Card, PACK_SIZE> temp;
    for(int deck = 0; deck < 7; deck++){
        int trackodd = 0;
        int trackeven = 0;
        for(int i = 0; i < PACK_SIZE; i++){
            if( i % 2 == 0){
            temp[i] = cards[(PACK_SIZE / 2) -  1 - trackeven];
            trackeven++;
            }
            if( i % 2 != 0){
            temp[i] = cards[(PACK_SIZE / 2) + trackodd];
            trackodd++;
            }
        }
        cards = temp;
    }
    reset();
}

bool Pack::empty() const {
    
    return next >= PACK_SIZE;

}