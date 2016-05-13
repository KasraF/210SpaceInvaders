/*
  Name: Kasra Ferdowsifard
  ID: 1475361
  Date: 05/07/2016
*/

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <sstream>
using namespace std;

#include "Leaderboard.hpp"

Leaderboard::Leaderboard(const string& file)
  :filename(file)
{
  ifstream loader(filename);

  if (loader) {
    string line, name;
    int score;
    Score element;

    //Inserting elements
    while (getline(loader, line)) {
      for (char &c : line)
        c = (c == ',') ? ' ' : c;
      stringstream(line) >> name >> score;
      element.name = name;
      element.score = score;
      board.push_back(element);
    }

    //Heapifying (just in case)
    make_heap(board.begin(), board.end());

    loader.close();
  }
  else {
    throw;
  }

}

Leaderboard::~Leaderboard()
{
  ofstream writer(filename);

  if (writer) {
    for (const Score& s : board) {
      string data(s.name);
      data += ',' + to_string(s.score);
      writer << data << endl;
    }
    writer.close();
  }
  else {
    throw;
  }
}

void Leaderboard::add(const string& name, const int score)
{
  Score newScore;
  newScore.name = name;
  newScore.score = score;
  board.push_back(newScore);
  push_heap(board.begin(), board.end());
  return;
}

vector<pair<string,int>> Leaderboard::topTen()
{
  vector<pair<string, int>> retVal;
  int max = (board.size() > 9) ? 10 : board.size();

  sort_heap(board.begin(), board.end());

  for (int i = 0; i < max; ++i) {
    pair<string, int> item = { board.at(i).name, board.at(i).score };
    retVal.push_back(item);
  }
  
  make_heap(board.begin(), board.end());

  return retVal;
}

