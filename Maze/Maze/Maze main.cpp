#include <iostream>
#include <string>
#include <fstream>
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

void ClearScreen() {
  system("clean");
  system("cls"); 
}

const int maxsize = 1000;
char maze[maxsize][maxsize];
bool vis[maxsize][maxsize];
int fa_x[maxsize][maxsize], fa_y[maxsize][maxsize];

int size_x, size_y;
int sx, sy, ex, ey;

struct Point {
  int x, y;
  Point() : x(0), y(0) {}
  Point(int _x, int _y) : x(_x), y(_y) {}
};

int dir[4][2] = { {-1, 0}, {1, 0}, {0, 1}, {0, -1} };

bool bfs() {
  MyQueue<Point> q;
  q.Push(Point(sx, sy));
  vis[sx][sy] = true;
  bool reached = false;
  while (!q.Empty()) {
    Point now = q.Front();
    q.Pop();
    if (now.x == ex && now.y == ey) {
      reached = true;
      break;
    }
    for (int i = 0; i < 4; i++) {
      int tx, ty;
      tx = now.x + dir[i][0];
      ty = now.y + dir[i][1];
      if (tx > 0 && tx <= size_x && ty > 0 && ty <= size_y && !vis[tx][ty] && maze[tx][ty] != '#') {
        vis[tx][ty] = true;
        fa_x[tx][ty] = now.x;
        fa_y[tx][ty] = now.y;
        q.Push(Point(tx, ty));
      }
    }
  }
  return reached;
}

bool ReadMaze() {
  ClearScreen();
  cout << "请输入迷宫文件名(同一目录下的): ";
  string filename;
  cin >> filename;
  ifstream inputfile(filename);
  if (!inputfile.is_open()) {
    cout << "读取文件失败!" << endl;
    return false;
  }
  // 先读入迷宫大小
  inputfile >> size_x >> size_y;
  // 然后读入起点终点坐标
  inputfile >> sx >> sy >> ex >> ey;
  // 最后读入迷宫图
  for (int i = 1; i <= size_x; i++) {
    for (int j = 1; j <= size_y; j++) {
      inputfile >> maze[i][j];
    }
  }
  return true;
}



void SearchShowMode() {
  if (!ReadMaze()) return;
  bool result = bfs();
  if (!result) {
    cout << "迷宫问题无解！" << endl;
    return;
  }
  // 标记路径
  int cur_x = ex, cur_y = ey;
  while (cur_x != sx || cur_y != sy) {
    int tmp_x = cur_x, tmp_y = cur_y;
    cur_x = fa_x[tmp_x][tmp_y];
    cur_y = fa_y[tmp_x][tmp_y];
    maze[cur_x][cur_y] = '!';
    // cout << "from " << cur_x << "," << cur_y << endl;
  }
  maze[sx][sy] = 'S';
  maze[ex][ey] = 'E';
  // 打印地图
  cout << "搜索到最短路径，路径用!标记：" << endl;
  for (int i = 1; i <= size_x; i++) {
    for (int j = 1; j <= size_y; j++) {
      cout << maze[i][j];
    }
    cout << endl;
  }
}

void StepByStepMode() {
  if (!ReadMaze()) return;
  bool result = bfs();
  if (!result) {
    cout << "迷宫问题无解！" << endl;
    return;
  }
}


int main() {
  ShowWelcome();
  string choice;
INPUT:
  cout << "你的选择是:";
  cin >> choice;
  if (choice != "1" && choice != "2") {
    cout << "输入有误，请重新输入 " << endl;
    goto INPUT;
  }
  if (choice == "1") {
    SearchShowMode();
  }
  else if(choice == "2") {
    StepByStepMode();
  }
  return 0;
}