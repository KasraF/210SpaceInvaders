/*
  Name: Kasra Ferdowsifard
  ID: 1475361
  Date: 05/17/2016

  NOTE: Windows only.
  NOTE 2: Needs Common Language Runtime Support (/clr) for compilation.
          To compile without clr, the 2 Beep() function calls in GameLoop.cpp must
          be removed.
*/

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "windows.h"
using namespace std;

#include "Game.hpp"

//Changes cursor position in console
BOOL gotoxy(const WORD x, const WORD y) {
  COORD xy;
  xy.X = x;
  xy.Y = y;
  return SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), xy);
}

Game::Game()
  : scores(SAVEFILE), out(&cout), loop(*out)
{
  clearBuffer();
}

Game::~Game() {};

void Game::start()
{
  bool running = true;
  while (running) {
    switch (menu()) {
    case 1:
      loop.run();
      getScore(loop.getScore());
      loop.reset();
    case 2:
      printScores();
      break;
    case 3:
      credits();
      break;
    case 4:
      running = false;
    }
  }
}

//Algorithms for menu(), getScore(),
//printScores() and credits() should 
//still work after minor resolution changes.
int Game::menu()
{
  ifstream file(MENU);
  string temp;
  vector<string> reader;
  int x, y, input;

  //Fill buffer
  clearBuffer();

  while (getline(file, temp)) {
    reader.push_back(temp);
  }

  y = ((SCREEN_Y - reader.size()) >> 1) - 1;
  
  for (string& s : reader) {
    x = midPrint(y, s);
    y++;
  }
  file.close();

  buffer.at(y += 2).at(x) = '>';
  x++;  

  //Get option
  do {
    print();
    gotoxy(x, y);
    getline(cin, temp);
  } while (!(stringstream(temp) >> input) || input > 4 || input < 0);

  return input;
}

void Game::getScore(int score)
{
  ifstream file(GAME_OVER);
  string temp;
  int x, y;

  //clear screen. add borders.
  clearBuffer();

  //print score
  y = (SCREEN_Y >> 1 ) - 4;
  getline(file, temp);
  midPrint(y, temp);
  y+=2;

  getline(file, temp);
  midPrint(y, temp);
  midPrint(++y, to_string(score));
  y += 2;

  //get name
  getline(file, temp);
  x = midPrint(y, temp);
  buffer.at(++y).at(x++) = '>';

  print();
  gotoxy(x, y);
  getline(cin, temp);

  //add score
  scores.add(temp, score);

  return;
}

void Game::printScores()
{
  int y = 2;
  vector<pair<string, int>> list = scores.topTen();

  clearBuffer();
  midPrint(y++, "Leaderboard");

  if (!list.empty()) {
    //Print top name
    y++;
    midPrint(y++, "The Best of the Best:");
    while (list.front().first.size() < 8)
      list.front().first += " ";
    midPrint(y++, list.front().first + "  " + to_string(list.front().second));

    //Print remaining top 9;
    y++;
    midPrint(y++, "The Rest of the Best:");
    for (int i = 1; i < list.size(); ++i) {
      while (list.at(i).first.size() < 15)
        list.at(i).first += " ";
      list.at(i).first += to_string(list.at(i).second);
      while (list.at(i).first.size() < 20)
        list.at(i).first += " ";
      midPrint(y++, list.at(i).first);
    }
  }
  else {
    midPrint(++y, "No Scores yet!");
  }

  print();
  cin.ignore();

  return;
}

void Game::credits()
{
  ifstream file(CREDITS);
  clearBuffer();

  if (file) {
    int y = 3;
    string reader;

    while (getline(file, reader)) {
      midPrint(y++, reader);
    }

    print();
    file.close();
  }
  else {
    cout << CREDITS << " MISSING!" << endl;
  }

  cin.ignore();
  return;
}

void Game::clearBuffer()
{
  string border(SCREEN_X, '#');
  string walls(SCREEN_X, ' ');
  walls.at(0) = walls.at(SCREEN_X - 1) = '#';

  buffer.clear();
  buffer.resize(SCREEN_Y);
  buffer.at(0) = buffer.at(SCREEN_Y - 1) = border;
  for (int i = 1; i < buffer.size() - 1; i++) {
    buffer.at(i) = walls;
  }

  return;
}

void Game::print() //Print buffer
{
  gotoxy(0, 0);
  for (const string& line : buffer) {
    cout << line << endl;
  }
  return;
}

//add string to middle of line in buffer
int  Game::midPrint(int y, const string &s) 
{
  int x = (SCREEN_X - s.size()) >> 1;
  buffer.at(y).replace(x, s.size(), s);
  return x;
}
