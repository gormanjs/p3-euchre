#include "Player.hpp"
#include <vector>

class SimplePlayer : public Player {
    public:

    //name constructor
    SimplePlayer(const std::string& name) : playerName(name){}

    //get_name implementation
    const std::string & get_name() const override{
        return playerName;
    }

    //add_card
    void add_card(const Card &c) override {
        hand.push_back(c);
    }

    //make_trump
    // bool make_trump(const Card &upcard, bool is_dealer,
    //                       int round, Suit &order_up_suit) const override {
        
    // }


    private:
    std::string playerName;
    std::vector<Card> hand;
}

// std::ostream & operator<<(std::ostream &os, const Player &p) {
//   assert(false);
// }

// Player * Player_factory(const std::string &name, 
//                         const std::string &strategy) {
//   // We need to check the value of strategy and return 
//   // the corresponding player type.
//   if (strategy == "Simple") {
//     // The "new" keyword dynamically allocates an object.
//     return new SimplePlayer(name);
//   }
//   // Repeat for each other type of Player
//   ...
//   // Invalid strategy if we get here
//   assert(false);
//   return nullptr;
//}
;