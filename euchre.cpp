#include <iostream>
#include "Player.hpp"
#include "Pack.hpp"
#include <fstream>
using namespace std;

class Game {
private:
  std::vector<Player*> players;
  Pack pack;
  int pointsToWin;
  bool defaultShuffle = true;

  void shuffle();
  void deal();
  void make_trump();
  void play_hand();
  void add_and_discard();

 public:

  Game(const string filename, int points_to_win, bool shuffle, const vector<Player*> playerList)
        : pointsToWin(points_to_win), defaultShuffle(shuffle), players(playerList) {
            //initialize pack
            ifstream inputFile(filename);
            Pack(inputFile);
        }

  void play() {


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