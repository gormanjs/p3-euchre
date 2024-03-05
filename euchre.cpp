#include <iostream>
#include "Player.hpp"
#include "Pack.hpp"
#include <fstream>
using namespace std;

class Game {
private:
  std::vector<Player*> players;
  Pack pack;
  int teamdecided = 2;
  int score1 = 0;
  int score2 = 0;
  int pointsToWin = 0;
  bool defaultShuffle = false;
  int dealerIndex = 0;
  Suit trump = SPADES;
  int leadingPlayer = (dealerIndex + 1) % players.size();
  string playerType = "";

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

  void make_trump() {
    Card upcard = pack.deal_one();
    bool is_dealer = false;
    for(int round = 1; round <= 2; round++) {
    int currentPlayer = (dealerIndex + 1) % players.size();
    for(int i = 0; i < 4; i++) {
        if(currentPlayer == dealerIndex) {
            is_dealer = true;
        }
        if(players[currentPlayer]->make_trump(upcard, is_dealer, round, trump)) {
            if(currentPlayer == 1 || currentPlayer == 3) {
                teamdecided = 1;
            }
            else {
                teamdecided = 2;
            }
            return;
        }
        else {
            currentPlayer = (currentPlayer + 1) % players.size();
        }
    }
  }
  }
  //determines game winner
  void winner(string condition) {
    
    if(condition == "win1") {
        //cout team 1 wins
    }
    else if(condition == "win2") {

    }
  }
//determines trick winner based on scoring funtion
  void trick_winner(bool team1) {
    if(team1) {
        score1++;
    }
    else {
        score2++;
    }
  }
//use to keep track of each teams score during the game
  void scoring() {}
  
  
  //team 1 is player 1 and 3 and team 2 is player 0 and 2
  void play_hand(int leadingPlayer) {
    vector<int> track;
    bool team1 = false;
    Card highest;
    Card led;
    //figure out who is winning
    Card played = players[leadingPlayer]->lead_card(trump);
    track.push_back(leadingPlayer);
    led = played;
    highest = played;
    for(int i = 0; i < 3; i++) {
    int nextPlayer = (leadingPlayer + 1) % 4;
    played = players[nextPlayer]->play_card(highest, trump);
    if(Card_less(highest, played, led, trump)) {
        highest = played;
        track.push_back(nextPlayer);
    }
    }
    if(track[track.size() - 1] == 1 || track[track.size() - 1] == 3) {
        team1 = true;
    }
    else {
        team1 =false;
    }

    trick_winner(team1);
    
  }
  void add_and_discard(Card upcard, int currentPlayer) {
    players[currentPlayer]->add_and_discard(upcard);
  }


  

 public:

 Game(int argc, char* argv[]) { //player constructor

    for (int i = 4; i < argc; i += 2) {
            std::string playerName = argv[i];
            std::string playerStrategy = argv[i + 1];
            players.push_back(Player_factory(playerName, playerStrategy));
    }
 }

 

  Game(const string filename, string in, int points_to_win, const vector<pair<string, string>>& playerData) {
        ifstream inputFile(filename);
        pack = Pack(inputFile);
        pointsToWin = points_to_win;
        if (in != "noshuffle") {
            defaultShuffle = true;
        }

        for (const auto& data : playerData) {
            string playerName = data.first;
            string playerStrategy = data.second;
            players.push_back(Player_factory(playerName, playerStrategy));
        }
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
        deal(dealerIndex);
        if(make_trump)
        
        



    }
    


    //delete players
    for (size_t i = 0; i < players.size(); ++i) {
        delete players[i];
    }
  }

};


int main(int argc, char **argv) {
    //./euchre.exe pack.in noshuffle 1 Adi Simple Barbara Simple Chi-Chih Simple Dabbala Simple 
    // Game game(/* game details */);
    // game.play();
    std::vector<Player*> players;
    string filename = argv[1];
    string shuffle = argv[2];
    int points_to_win = stoi(argv[3]);
  
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


    
    ifstream packFile(filename);

    if (!packFile.is_open()){
        cout << "Error opening filename: " << filename << endl;
        return 2;
    }

    vector<pair<string, string>> playerData; 

    for (int i = 4; i < argc; i += 2) {
        string playerName = argv[i];
        string playerType = argv[i + 1];
        playerData.push_back({playerName, playerType});
    }


    Game game(filename, shuffle, points_to_win, playerData);
    game.play();



    



}