/*
  Name: Kasra Ferdowsifard
  ID: 1475361
  Date: 05/17/2016

  NOTE: Windows only. 
  NOTE 2: Needs Common Language Runtime Support (/clr) for compilation.
          To compile without clr, the 2 Beep() function calls in GameLoop.cpp must
          be removed.
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

