/*
  Name: Kasra Ferdowsifard
  ID: 1475361
  Date: 05/07/2016
*/
#include <iostream>
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