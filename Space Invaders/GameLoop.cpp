/*
  Name: Kasra Ferdowsifard
  ID: 1475361
  Date: 05/07/2016
*/

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <stdlib.h>
#include "windows.h"
using namespace std;

#include "GameLoop.hpp"
#include "Game.hpp"

//Used for changing the cursor position
//in the console
BOOL gotoxy(const WORD x, const WORD y);

GameLoop::GameLoop(ostream& out_str)
  :out(&out_str)
{
  reset();
}

void GameLoop::run()
{
  running = true;
  int wait = 0;
  while (running) {
    
    print();
    wait++;
    Sleep(20); //Faster process would make every button press count several times

    //Actual GameObject process is done every 3rd frame
    //This makes player control smoother.
    if (wait == 2) {

      if (GetAsyncKeyState(VK_SPACE) && missiles.size() < MAX_MISSILES) {
        GameObject missile(player.x, player.y - 1);
        missiles.push_back(missile);
      }

      wait = 0;

      //The order of these processes should not be changed
      processMissiles();
      processBullets();
      processInvaders();
      collisionCheck();
    }

    //Controlls (Uses Windows.h. not portable.)
    if (GetAsyncKeyState(VK_LEFT) && buffer.at(player.y).at(player.x - 1) != BORDER) {
      buffer.at(player.y).at(player.x) = ' ';
      player.x--;
      buffer.at(player.y).at(player.x) = PLAYER;
    }
    if (GetAsyncKeyState(VK_RIGHT) && buffer.at(player.y).at(player.x + 1) != BORDER) {
      buffer.at(player.y).at(player.x) = ' ';
      player.x++;
      buffer.at(player.y).at(player.x) = PLAYER;
    }
    
    if (GetAsyncKeyState(VK_ESCAPE)) {
      running = false;
    }
  }
}

int GameLoop::getScore()
{
  return (score < 0) ? 0 : score;
}

void GameLoop::reset()
{
  //Emptying vectors
  invaders.clear();
  missiles.clear();
  bullets.clear();

  //Setting player
  player.x = SCREEN_X / 2;
  player.y = SCREEN_Y - 2;

  //Create Invaders
  int x = 1;
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 4; j++) {
      GameObject invader(x, 2);
      invaders.push_back(invader);
      x++;
    }
    x += 2;
  }

  //Draw Borders
  string border(SCREEN_X, BORDER);
  string walls(SCREEN_X, ' ');
  walls.at(0) = walls.at(SCREEN_X - 1) = BORDER;

  buffer.clear();
  buffer.resize(SCREEN_Y);
  buffer.at(0) = buffer.at(SCREEN_Y - 1) = border;
  for (int i = 1; i < buffer.size() - 1; i++) {
    buffer.at(i) = walls;
  }
  buffer.at(player.y).at(player.x) = PLAYER;

  //Single Variables
  score = 0;
  multiplier = 0;
  dx = -1;
  fireRate = 11;
}

void GameLoop::processInvaders()
{
  //Clear Buffer
  for (GameObject& inv : invaders) {
    buffer.at(inv.y).at(inv.x) = ' ';
  }

  //Border Collision check
  if (!(invaders.at(0).x - 1) || SCREEN_X == invaders.at(invaders.size() - 1).x + 2) {
    multiplier++;
    dx = -dx;
  }

  //Vertical movement
  if (!(multiplier % 8)) {
    multiplier++;
    for (GameObject& inv : invaders) {
      inv.y++;
    }
  }

  //Horizontal movement + Fire Bullet + buffer draw
  for (GameObject& inv : invaders) {
    inv.x += dx;
    buffer.at(inv.y).at(inv.x) = INVADER;
    int check = random();
    if (check < fireRate) {
      GameObject bullet(inv.x, inv.y);
      bullets.push_back(bullet);
    }
  }

  return;
}

void GameLoop::processMissiles()
{

  //Clear buffer
  for (GameObject &miss : missiles) {
    buffer.at(miss.y).at(miss.x) = ' ';
    miss.y--;
  }

  //Buffer draw + front collision check
  for (int i = 0; i < missiles.size(); i++) {
    if (missiles.at(i).y == 0) {
      missiles.erase(missiles.begin() + i);
      i--;
    }
    //Round one collision check for front collision
    else if (buffer.at(missiles.at(i).y).at(missiles.at(i).x) == INVADER) {
      killInvader(missiles.at(i).x);
      fireRate+=2;
      System::Console::Beep(); // Uses windows.h (not portable)
      score += static_cast<double>(multiplier) / MAX_MULTIPLIER * SCORE_UNIT;
      buffer.at(missiles.at(i).y).at(missiles.at(i).x) = ' ';
      running = !invaders.empty();
      missiles.erase(missiles.begin() + i);
      i--;
    }
    else {
      buffer.at(missiles.at(i).y).at(missiles.at(i).x) = MISSILE;
    }
  }
}

void GameLoop::processBullets()
{
  for (int i = 0; i < bullets.size(); i++) {
    buffer.at(bullets.at(i).y++).at(bullets.at(i).x) = ' ';
    if (bullets.at(i).y == SCREEN_Y - 1) {
      bullets.erase(bullets.begin() + i);
      i--;
    }
    else {
      buffer.at(bullets.at(i).y).at(bullets.at(i).x) = BULLET;
    }
  }
}

void GameLoop::collisionCheck()
{  
  //Missile Collision check Round two! For side collision.)
  for (int i = 0; i < missiles.size(); i++) {
    if (buffer.at(missiles.at(i).y).at(missiles.at(i).x) == INVADER) {
      killInvader(missiles.at(i).x);
      fireRate += 2;
      System::Console::Beep();
      score += static_cast<double>(multiplier) / MAX_MULTIPLIER * SCORE_UNIT;
      buffer.at(missiles.at(i).y).at(missiles.at(i).x) = ' ';
      running = !invaders.empty();
      missiles.erase(missiles.begin() + i);
      i--;
    }
  }

  //Game Over check for player
  if (buffer.at(player.y).at(player.x) != PLAYER) {
    running = false;
    score -= static_cast<double>(multiplier) / MAX_MULTIPLIER * SCORE_UNIT;
  }

  return;
}

inline int GameLoop::random()
{
  return rand()%100;
}

void GameLoop::print()
{
  gotoxy(0, 0);
  for (string line : buffer) {
    *out << line << endl;
  }
  return;
}

//Uses a binary search algorithm to find
//and erase the invader with the coordinate x
bool GameLoop::killInvader(int x) {
  int begin = 0, end = invaders.size() - 1;
  int i = 0;
  bool done = false;

  while (begin <= end && !done) {
    i = (begin + end) >> 1;
    if (invaders.at(i).x == x) {
      invaders.erase(invaders.begin() + i);
      done = true;
    }
    else if (invaders.at(i).x > x) {
      end = i - 1;
    }
    else {
      begin = i + 1;
    }
  }

  return done;
}