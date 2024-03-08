#include <iostream>
#include "Player.hpp"
#include "Pack.hpp"
#include <fstream>
using namespace std;

class Game {
private:
  std::vector<Player*> players;
  vector<int> track;
  Pack pack;
  int teamdecided;
  int points1;
  int points2;
  int score1;
  int score2;
  string condition;
  int pointsToWin;
  bool defaultShuffle;
  int dealerIndex;
  Suit trump;
  int leadingPlayer;
  string playerType;
  Card start;

  void shuffle() {
    pack.shuffle();
  }


  void deal(int dealerIndex) {
    int currentPlayer = (dealerIndex + 1) % players.size();
    
       // Deal 3-2-3-2 cards
    for(int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; ++j) {
            players[currentPlayer]->add_card(pack.deal_one());
        }
        currentPlayer = (currentPlayer + 1) % players.size();
        for (int j = 0; j < 2; ++j) {
            players[currentPlayer]->add_card(pack.deal_one());
        }
        currentPlayer = (currentPlayer + 1) % players.size();
    }
    
    
    // Deal 2-3-2-3 cards
    for(int p = 0; p < 2; p++) {
        for (int j = 0; j < 2; ++j) {
            players[currentPlayer]->add_card(pack.deal_one());
        }
        currentPlayer = (currentPlayer + 1) % players.size();
        for (int j = 0; j < 3; ++j) {
            players[currentPlayer]->add_card(pack.deal_one());
        }
        currentPlayer = (currentPlayer + 1) % players.size();
    }

    start = pack.deal_one();

    
  }
    //change
  void make_trump() {
    bool is_dealer = false;
    for(int round = 1; round <= 2; round++) {
    int currentPlayer = (dealerIndex + 1) % players.size();
    for(int i = 0; i < 4; i++) {
        if(currentPlayer == dealerIndex) {
            is_dealer = true;
        }
        if(players[currentPlayer]->make_trump(start, is_dealer, round, trump)) {
            if(round == 1) {
                add_and_discard(start, dealerIndex);
            }
            cout << players[currentPlayer]->get_name() << " orders up " << trump << endl;
            if(currentPlayer == 1 || currentPlayer == 3) {
                teamdecided = 1;
            }
            else {
                teamdecided = 2;
            }
            return;
        }
        else {
            cout << players[currentPlayer]->get_name() << " passes" << endl;
            currentPlayer = (currentPlayer + 1) % players.size();
        }
    }
  
    }
  }
  //determines game winner
  void winner() {
    if(condition == "w1") {
        cout << players[1]->get_name() << " and " 
        << players[3]->get_name() << " win!" << endl;
    }
    else if(condition == "w2") {
        cout << players[0]->get_name() << " and " 
        << players[2]->get_name() << " win!" << endl;
    }
    else if(condition == "1") {
        cout << players[1]->get_name() << " and " 
        << players[3]->get_name() << " win the hand" << endl;
        points1 = points1++;
    }
    else if(condition == "2") {
        cout << players[0]->get_name() << " and "
        << players[2]->get_name() << " win the hand" << endl;
        points2 = points2++;
    }
    else if(condition == "e1") {
        cout << "euchred!" << endl;
        points1 = points1 + 2;
    }
    else if(condition == "e2") {
        cout << "euchred" << endl;
        points2 = points2 + 2;
    }
    else if(condition == "m1") {
        cout << "march!" << endl;
        points1 = points1 + 2;
    }
    else if(condition == "m2") {
        cout << "march!" << endl;
        points2 = points2 + 2;
    }
    else {
        cout << "error" << endl;
    }
  }
//determines trick winner based on scoring funtion
  void trick_winner(bool team1) {
    cout << players[track[track.size() - 1]]->get_name() << " takes the trick" << endl;
    if(team1) {
        score1++;
    }
    else {
        score2++;
    }
    track.clear(); // reset track so size doesnt stay
  }
//use to keep track of each teams score during the game
  void scoring() {
    if(score1 == 5 && teamdecided == 0) {
        condition = "m1";
    }
    else if(score2 == 5 && teamdecided == 1) {
        condition = "m2";
    }
    else if(score1 > score2 && teamdecided == 1) {
        condition = "e1";
    }
    else if(score1 < score2 && teamdecided == 0) {
        condition = "e2";
    }
    else if(score1 < score2) {
        condition = "2";
    }
    else if(score1 > score2) {
        condition = "1";
    }
    else {
        condition = "error";
    }
    cout << players[1]->get_name() << " and " 
        << players[3]->get_name() << " have " << points1 << " points" << endl;
    cout << players[0]->get_name() << " and " 
        << players[2]->get_name() << " have " << points2 << " points" << endl;
  }

  bool check_win() {
    if(points1 == pointsToWin) {
        condition = "w1";
        return true;
    }
    else if(points2 == pointsToWin) {
        condition = "w2";
        return true;
    }
    else {
        return false;
    }
  }
  
  
  //team 1 is player 1 and 3 and team 2 is player 0 and 2
  void play_hand() {
    leadingPlayer = 1;
    bool team1 = false;
    Card highest;
    Card led;
    for(int i = 0; i < 5; i ++) 
    {
        Card played = players[leadingPlayer]->lead_card(trump);
        cout << played << " led by " << players[leadingPlayer]->get_name() << endl;
        track.push_back(leadingPlayer);
        led = played;
        highest = played;
        int nextPlayer = leadingPlayer + 1;
        for(int i = 0; i < 3; i++) 
        {
            played = players[nextPlayer]->play_card(highest, trump);
            cout << played << " played by " << players[nextPlayer]->get_name() << endl;
            if(Card_less(highest, played, led, trump)) 
            {
                highest = played;
                track.push_back(nextPlayer);
            }
            nextPlayer = (nextPlayer + 1) % players.size();
        }
            if(track[track.size() - 1] == 1 || track[track.size() - 1] == 3) 
            {
                team1 = true;
                leadingPlayer = track[track.size() - 1];
                trick_winner(team1);
            } 
            else if(track[track.size() - 1] == 0 || track[track.size() - 1] == 2) {
                leadingPlayer = track[track.size() - 1];
                trick_winner(team1);
            }
        }
        scoring();
        winner();
}

  void add_and_discard(Card upcard, int currentPlayer) {
    players[currentPlayer]->add_and_discard(upcard);
  }

  void announce(int hand) {
    std::cout << "Hand " << hand << endl;
    std::cout << players[dealerIndex]->get_name() << " deals" << endl;
    std::cout << start << " turned up" << endl;
  }

  //Human player Judea, please enter a suit, or "pass":


  

 public:

 Game(const string filename, string in, int points_to_win, int argc, char **argv) 
    : players(), track(), teamdecided(0), condition(""), pointsToWin(points_to_win)
    , playerType("") {
    points1 = 0;
    points2 = 0;
    score1 = 0;
    score2 = 0;
    dealerIndex = 0;
    ifstream inputFile(filename);
    pack = Pack(inputFile);
    if (in != "noshuffle") {
        defaultShuffle = true;
    }
    
    // Create players based on command-line arguments
    for (int i = 4; i < argc; i += 2) {
        Player* player = Player_factory(argv[i], argv[i + 1]);
        if (player) {
            players.push_back(player);
        } else {
            cout << "Failed to create player: " << argv[i] << std::endl;
            return;
        }
    }
    
    // Assign leadingPlayer outside the loop after adding players
    leadingPlayer = 1;
}





  void play() {
    int hand = 0;
    // shuffle deck if specified
    if (defaultShuffle){
        pack.shuffle();
    }
    else {
        pack.reset();
    }
    while(!check_win()) {
        deal(dealerIndex);
        announce(hand);
        make_trump();
        play_hand();
        hand++;
        
    }

  }

  ~Game() {
    // Delete players to avoid memory leaks
    for (size_t i = 0; i < players.size(); ++i) {
        delete players[i];
    }
  }

};


int main(int argc, char **argv) {
    string filename = argv[1];
    string shuffle = argv[2];
    int points_to_win = stoi(argv[3]);


  
if (argc != 12 || (std::string(argv[2]) != "shuffle" && std::string(argv[2]) != "noshuffle")
    || std::stoi(argv[3]) < 1 || std::stoi(argv[3]) > 100 
    || (std::string(argv[5]) != "Simple" && std::string(argv[5]) != "Human")
    || (std::string(argv[7]) != "Simple" && std::string(argv[7]) != "Human")
    || (std::string(argv[9]) != "Simple" && std::string(argv[9]) != "Human")
    || (std::string(argv[11]) != "Simple" && std::string(argv[11]) != "Human")) {
    std::cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
              << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
              << "NAME4 TYPE4" << std::endl;
    return 1;
}


    ifstream packFile(filename);

    if (!packFile.is_open()){
        cout << "Error opening filename: " << filename << endl;
        return 1;
    }


    Game game(filename, shuffle, points_to_win, argc, argv);
    game.play();

    return 0;

}