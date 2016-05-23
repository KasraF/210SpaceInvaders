/*
  Name: Kasra Ferdowsifard
  ID: 1475361
  Date: 05/17/2016

  NOTE: Windows only.
  NOTE 2: Needs Common Language Runtime Support (/clr) for compilation.
          To compile without clr, the 2 Beep() function calls in GameLoop.cpp must
          be removed.
*/

#ifndef LEADERBOARD_HPP
#define LEADERBOARD_HPP

#include <vector>
#include <string>
#include <fstream>
using std::vector;
using std::string;
using std::pair;
using std::fstream;

struct Score {
  string name;
  int score;

  bool operator< (const Score& rVal) {
    return score > rVal.score;
  }
};

class Leaderboard
{
public:
  Leaderboard(const string& filename);
  ~Leaderboard();

  void add(const string& name, const int score);
  vector<pair<string, int>> topTen();
private:
  string filename;
  vector<Score> board;
};
#endif
