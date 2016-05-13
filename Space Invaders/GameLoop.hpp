/*
  Name: Kasra Ferdowsifard
  ID: 1475361
  Date: 05/07/2016
*/
#ifndef GAMELOOP_HPP
#define GAMELOOP_HPP

#include <iostream>
#include <vector>
#include <string>
using std::ostream;
using std::vector;

const char PLAYER = '^';
const char INVADER = '@';
const char MISSILE = '!';
const char BULLET = '*';
const char BORDER = '#';

const int MAX_MISSILES = 3;
const int SCORE_UNIT = 1000;
const int MAX_MULTIPLIER = 127;

struct GameObject {
  int x, y;

  GameObject() {};
  GameObject(int x, int y) {
    this->x = x;
    this->y = y;
  }
};

class GameLoop
{
public:
  GameLoop(ostream&);
  void run();
  int getScore();
  void reset();
private:
  ostream* out;
  vector<string> buffer;
  bool running;

  int score;
  int multiplier; //used to calculate score and check invader y position
  int dx;
  int fireRate;

  GameObject player;
  vector<GameObject> invaders;
  vector<GameObject> missiles;
  vector<GameObject> bullets;

  void processInvaders();
  void processMissiles();
  void processBullets();
  void collisionCheck(); //Also handles object placement in buffer and score

  int random();
  void print();
  bool killInvader(int x);
};
#endif
