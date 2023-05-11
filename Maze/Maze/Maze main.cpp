#include <iostream>
#include "MyQueue.h"

using namespace std;

void ShowWelcome() {
  cout << "===========================================" << endl;
  cout << "|               Maze Game                 |" << endl;
  cout << "|        Powered by BFS algorithm         |" << endl;
  cout << "|-----------------------------------------|" << endl;
  cout << "|        [1] Search & Show Mode           |" << endl;
  cout << "|       [2] Step by Step Show Mode        |" << endl;
  cout << "===========================================" << endl;
}

MyQueue<int> q;

int main() {
  ShowWelcome();
  
  return 0;
}