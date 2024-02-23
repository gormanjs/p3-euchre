#include "Player.hpp"
#include <vector>
#include <algorithm>

class SimplePlayer : public Player {
    public:

    //name constructor
    SimplePlayer(const std::string& name) : playerName(name){}

    //get_name 
    const std::string & get_name() const override{
        return playerName;
    }

    //add_card
    void add_card(const Card &c) override {
        hand.push_back(c);
    }

    //make trump
    bool make_trump(const Card &upcard, bool is_dealer,
                          int round, Suit &order_up_suit) const override {
        int round_one_count = 0;
        if (round == 1){
            for (size_t i = 0; i < hand.size(); i++){
                if (hand[i].is_face_or_ace() && hand[i].get_suit() == upcard.get_suit()){
                    round_one_count++;
                }
            }
            if (round_one_count >= 2){
                order_up_suit = upcard.get_suit();
                return true;
            }
            return false;
        }
        int round_two_count = 0;
        if (round == 2){
            if (is_dealer){
                order_up_suit = upcard.get_suit();
                return true;
            }
            for (size_t i = 0; i < hand.size(); i++){
                if (hand[i].is_face_or_ace() && 
                    hand[i].get_suit() == Suit_next(upcard.get_suit())){
                        round_two_count++;
                    }
            }
            if (round_two_count >= 1){
                order_up_suit = upcard.get_suit();
                return true;
            }
            return false;
        }
        return false;
    }

    void add_and_discard(const Card &upcard) override {
        hand.push_back(upcard);
        auto card = upcard;
        for(int i = 1; i < hand.size(); i++){
            if(hand[i].get_rank() < card.get_rank()){
                card = hand[i];
            }
            if(hand[i].get_rank() == card.get_rank() && hand[i].get_suit() != card.get_suit()){
                card = hand[i];
            }
        }
        hand.erase(remove(hand.begin(), hand.end(), card),hand.end());
        
    }   

    Card lead_card(Suit trump) override{
         Card lead = hand[0];
         int spot;
    bool has_non_trump = false;

    // Check if there are non-trump cards in the hand
    for (size_t i = 0; i < hand.size(); i++) {
        if (!hand[i].is_trump(trump)) {
            has_non_trump = true;
            
        }
    }

    // If there are non-trump cards, play the highest one
    if (has_non_trump) {
        for (size_t i = 1; i < hand.size(); i++) {
            if (!hand[i].is_trump(trump) && hand[i].get_rank() > lead.get_rank()) {
                lead = hand[i];
                spot = i;
            }
        }
    } else { // If all cards are trump, play the highest trump card
        for (size_t i = 1; i < hand.size(); i++) {
            if (hand[i].get_rank() > lead.get_rank()) {
                lead = hand[i];
                spot = i;
            }
        }
    }

    // Remove the played card from the hand
    hand.erase(hand.begin() + spot);

    return lead;
    }

    Card play_card(const Card &led_card, Suit trump) override {
        Suit ledSuit = led_card.get_suit();

        bool has_suit = false;
        Rank highest = hand[0].get_rank();

        //check if player has card of led suit
        for (auto i = 0; i < hand.size(); i++){
            if (hand[i].get_suit() == ledSuit){
                has_suit = true;
                if (Card_less(hand[i], Card(highest, ledSuit), led_card, trump)){
                    highest = hand[i].get_rank();
                }
            }
        }

        //play highest of led suit if has
        if (has_suit){
            for (auto i = 0; i < hand.size(); i++){
                if (hand[i].get_suit() == ledSuit && hand[i].get_rank() == highest){
                    //create temporary card because need to delete it
                    Card played = hand[i];
                    hand.erase(hand.begin() + i);
                    return played;
                }
            }
        }

        //find lowest card if not
        auto lowest_index = 0;
        for (auto i = 0; i < hand.size(); i++){
            if (Card_less(hand[i], hand[lowest_index], led_card, trump)){
                lowest_index = i;
            }
        }

        //play lowest card
        Card played = hand[lowest_index];
        hand.erase(hand.begin() + lowest_index);
        return played;
    }

    private:
    std::string playerName;
    std::vector<Card> hand;
};



class HumanPlayer : public Player {
    std::string HumanName;
    std::vector<Card> hand;
    void print_hand() const {
    for (size_t i=0; i < hand.size(); ++i)
    std::cout << "Human player " << HumanName << "'s hand: "
         << "[" << i << "] " << hand[i] << "\n";
}
    public:

    HumanPlayer(const std::string& name) : HumanName(name){}

    const std::string & get_name() const override {
        return HumanName;
    }

    void add_card(const Card &c) override {
        hand.push_back(c);
        std::sort(hand.begin(), hand.end());
    }
    
    bool make_trump(const Card &upcard, bool is_dealer,
    int round, Suit &order_up_suit) const override {
        print_hand();
        std::cout << "Human player " << HumanName << ", please enter a suit, or \"pass\":\n";
        std::string decision;
        std::cin >> decision;
        if(decision != "pass") {
            order_up_suit = string_to_suit(decision);
            return true;
        }
        else {
            return false;
        }


    }

    void add_and_discard(const Card &upcard) override {
        add_card(upcard);
        auto card = upcard;
        int choice;
        print_hand();
        std::cout << "Discard upcard: [-1]\n";
        std::cout << "Human player " << HumanName << ", please select a card to discard:\n";
        std::cin >> choice;
        if(choice == -1) {
            hand.erase(remove(hand.begin(), hand.end(), card),hand.end());
        }
        else {
            hand.erase(hand.begin() + choice);
        }
        
    }

    Card lead_card(Suit trump) override{
        print_hand();
        int choice;
        Card lead;
        std::cout << "Human player " << HumanName << ", please select a card:\n";
        std::cin >> choice;
        lead = hand[choice];
        return lead;
    }

    Card play_card(const Card &led_card, Suit trump) override {
        print_hand();
        int choice;
        Card lead;
        std::cout << "Human player " << HumanName << ", please select a card:\n";
        std::cin >> choice;
        lead = hand[choice];
        return lead;
    }

    friend std::ostream & operator<<(std::ostream &os, const Player &p);
};

std::ostream & operator<<(std::ostream &os, const Player &p) {
   os << p.get_name();
   return os;

}

Player * Player_factory(const std::string &name, 
                        const std::string &strategy) {
                            
  // We need to check the value of strategy and return 
  // the corresponding player type.
  if (strategy == "Simple") {
    // The "new" keyword dynamically allocates an object.
    return new SimplePlayer(name);
  }
  else if(strategy == "Human"){
    return new HumanPlayer(name);
  }
  else {
    return nullptr;
  }
}
