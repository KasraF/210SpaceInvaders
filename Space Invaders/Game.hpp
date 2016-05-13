/*
  Name: Kasra Ferdowsifard
  ID: 1475361
  Date: 05/07/2016
*/

#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <string>
#include <vector>
using std::ostream;
using std::string;
using std::vector;

#include "Leaderboard.hpp"
#include "GameLoop.hpp"

const int SCREEN_X = 60;
const int SCREEN_Y = 20;

const string SAVEFILE = "leaderboard.csv";
const string MENU = "menu.dat";
const string GAME_OVER = "gameover.dat";
const string CREDITS = "credits.dat";

class Game
{
public:
  Game();
  void start();
  ~Game();
private:
  ostream* out;
  Leaderboard scores;
  GameLoop loop;

  vector<string> buffer;

  int menu();
  void getScore(int score);
  void printScores();
  void credits();

  void clearBuffer();
  void print();

  int midPrint(int y, const string&); //Adds in middle of line
};
#endif

