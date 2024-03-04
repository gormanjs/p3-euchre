#include <iostream>
#include "Player.hpp"
#include "Pack.hpp"
#include <fstream>
using namespace std;

class Game {
private:
  std::vector<Player*> players;
  Pack pack;
  int score = 0;
  int pointsToWin = 0;
  bool defaultShuffle = false;
  int dealerIndex = 0;
  Suit trump = SPADES;
  int leadingPlayer = (dealerIndex + 1) % players.size();

  void shuffle() {
    pack.shuffle();
  }

  void deal(int dealerIndex) {
    int currentPlayer = (dealerIndex + 1) % players.size();
    for (int deal1 = 0; deal1 < 2; deal1++) {
        for (int i = 0; i < 4; i++) { // Deal 3-2-3-2 cards
            players[currentPlayer]->add_card(pack.deal_one());
            if (i % 2 == 1) // After dealing 2 cards, move to the next player
                currentPlayer = (currentPlayer + 1) % players.size();
        }
    }
    for (int deal2 = 0; deal2 < 2; deal2++) {
        for (int i = 0; i < 4; i++) { // Deal 2-3-2-3 cards
            if (i % 2 == 0) // Before dealing 3 cards, move to the next player
                currentPlayer = (currentPlayer + 1) % players.size();
            players[currentPlayer]->add_card(pack.deal_one());
        }
    }
  }

  void make_trump(int dealerIndex) {
    Card upcard = pack.deal_one();
    bool is_dealer = false;
    for(int round = 1; round <= 2; round++) {
    int currentPlayer = (dealerIndex + 1) % players.size();
    for(int i = 0; i < 4; i++) {
        if(currentPlayer == dealerIndex) {
            is_dealer = true;
        }
        if(players[currentPlayer]->make_trump(upcard, is_dealer, round, trump)) {
            return;
        }
        else {
            currentPlayer = (currentPlayer + 1) % players.size();
        }
    }
  }
  }
  //double check to make sure dealer picks up upcard if ordered up
  
  void play_hand(Suit trump, int leadingPlayer, Player* players) {
    //figure out who is winning
    Card played = players[leadingPlayer].lead_card(trump);
    int nextPlayer = (leadingPlayer + 1) % 4;
    //if()
    //compare cards to see who has the lead
  }
  void add_and_discard();

 public:
 
//create an array of player pointers to initialize
  Player *players;

  Game(const string filename, int points_to_win, bool shuffle)
        : pointsToWin(points_to_win), defaultShuffle(shuffle) {
            //initialize pack
            ifstream inputFile(filename);
            Pack(inputFile);
        }

  void play() {

    // shuffle deck is specified
    if (defaultShuffle){
        pack.shuffle();
    }
    else {
        pack.reset();
    }

    // keep track of dealer index
    for (int i = dealerIndex; i < players.size(); i++){
        // deal in order: 1, 2, 3, 0

    }
    


    //delete players
    for (size_t i = 0; i < players.size(); ++i) {
        delete players[i];
    }
  }

};


int main(int argc, char **argv) {

    // Game game(/* game details */);
    // game.play();
  
    if (argc != 12 || argv[2] != "shuffle" || argv[2] != "noshuffle" 
        || stoi(argv[3]) < 1 || stoi(argv[3]) > 100 
        || argv[5] != "Simple"|| argv[5] != "Human" 
        || argv[7] != "Simple"|| argv[7] != "Human"
        || argv[9] != "Simple"|| argv[9] != "Human"
        || argv[11] != "Simple"|| argv[11] != "Human"){
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
             << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
             << "NAME4 TYPE4" << endl;
        return 1;
    }

    string filename = argv[1];
    ifstream packFile(filename);

    if (!packFile.is_open()){
        cout << "Error opening filename: " << filename << endl;
        return 2;
    }



}