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
#include <Windows.h>
using namespace std;

#include"Game.hpp"

int main()
{
  cout << "Developer Name: Kasra Ferdowsifard" << endl
    << "Developer ID: 1475361" << endl
    << "Date: 05/07/2016" << endl;
  cin.ignore();
  Game spaceInvaders;
  spaceInvaders.start();
  return 0;
}