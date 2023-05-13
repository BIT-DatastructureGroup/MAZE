#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "MyQueue.h"
#include<stack>
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
int min_len = INT_MAX;
vector<Point> min_path;
bool dfs() {
    stack<Point> s;
    stack<int> l;
    stack<vector<Point>> p;
    s.push(Point(sx, sy));
    l.push(0);
    p.push(vector<Point>(1,Point(sx, sy)));
    vis[sx][sy] = true;
    bool reached = false;
    while (!s.empty()) {
        Point now = s.top();
        int len = l.top();
        vector<Point> path = p.top();
        s.pop();
        l.pop();
        p.pop();
        if (now.x == ex && now.y == ey) {
            reached = true;
            if (len < min_len) {
                min_len = len;
                min_path = path;
            }
            vis[now.x][now.y] = false;
            continue;
        }
        for (int i = 0; i < 4; i++) {
            int tx, ty;
            tx = now.x + dir[i][0];
            ty = now.y + dir[i][1];
            if (tx > 0 && tx <= size_x && ty > 0 && ty <= size_y && !vis[tx][ty] && maze[tx][ty] != '#') {
                s.push(Point(tx, ty));
                l.push(len + 1);
                fa_x[tx][ty] = now.x;
                fa_y[tx][ty] = now.y;
                path.push_back(Point(tx, ty));
                p.push(path);
                path.pop_back();
                vis[tx][ty] = true;
            }
        }
    }
    return reached;
}


bool ReadMaze() {
  ClearScreen();
  cout << "===========================================" << endl;
  cout << "|               Maze Game                 |" << endl;
  cout << "|   Which way do you want to input?       |" << endl;
  cout << "|-----------------------------------------|" << endl;
  cout << "|           [1] Read From File            |" << endl;
  cout << "|           [2] Input Directly            |" << endl;
  cout << "===========================================" << endl;
READ_CHOICE:
  string choice;
  cout << "���ѡ����:";
  cin >> choice;
  if (choice != "1" && choice != "2") {
    cout << "������������������ " << endl;
    goto READ_CHOICE;
  }
  if (choice == "1") {
    cout << "�������Թ��ļ���(ͬһĿ¼�µ�): ";
    string filename;
    cin >> filename;
    ifstream inputfile(filename);
    if (!inputfile.is_open()) {
      cout << "��ȡ�ļ�ʧ��!" << endl;
      return false;
    }
    // �ȶ����Թ���С
    inputfile >> size_x >> size_y;
    // Ȼ���������յ�����
    inputfile >> sx >> sy >> ex >> ey;
    // �������Թ�ͼ
    for (int i = 1; i <= size_x; i++) {
      for (int j = 1; j <= size_y; j++) {
        inputfile >> maze[i][j];
      }
    }
    return true;
  }
  else {
    cout << "�����������Թ���С��������꣬�յ����꣬�Լ��Թ�����ͼ" << endl;
    // �ȶ����Թ���С
    cin >> size_x >> size_y;
    // Ȼ���������յ�����
    cin >> sx >> sy >> ex >> ey;
    // �������Թ�ͼ
    for (int i = 1; i <= size_x; i++) {
      for (int j = 1; j <= size_y; j++) {
        cin >> maze[i][j];
      }
    }
    return true;
  }
  
}
void SearchShowMode() {
  if (!ReadMaze()) return;
  //bool result = bfs();
  bool result = dfs();
  vector<Point> path;
  path = min_path;
  if (!result) {
    cout << "�Թ������޽⣡" << endl;
    return;
  }
  // ���·��
  /*int cur_x = ex, cur_y = ey;
  while (cur_x != sx || cur_y != sy) {
    int tmp_x = cur_x, tmp_y = cur_y;
    cur_x = fa_x[tmp_x][tmp_y];
    cur_y = fa_y[tmp_x][tmp_y];
    maze[cur_x][cur_y] = '!';
    // cout << "from " << cur_x << "," << cur_y << endl;
  }*/
  maze[sx][sy] = 'S';
  maze[ex][ey] = 'E';
  // ��ӡ��ͼ
  cout << "���������·����·����!��ǣ�" << endl;
  for (int i = 1; i < path.size(); i++) maze[path[i].x][path[i].y] = '!';  
  for (int i = 1; i <= size_x; i++) 
  {
       for (int j = 1; j <= size_y; j++) 
       {
              cout << maze[i][j];
       }
          cout << endl;
  }
 
}
void StepByStepMode() {
  if (!ReadMaze()) return;
  bool result = dfs();
  //bool result = bfs();
  if (!result) {
    cout << "�Թ������޽⣡" << endl;
    return;
  }
  vector<Point> path;
  path = min_path;
  // ���·��
  /*int cur_x = ex, cur_y = ey;
  while (cur_x != sx || cur_y != sy) {
    int tmp_x = cur_x, tmp_y = cur_y;
    cur_x = fa_x[tmp_x][tmp_y];
    cur_y = fa_y[tmp_x][tmp_y];
    path.push_back(Point(cur_x, cur_y));
  }
  reverse(path.begin(), path.end());*/
  maze[sx][sy] = 'S';
  maze[ex][ey] = 'E';
  getchar();
  for (int i = 1; i < path.size(); i++) {
    ClearScreen();
    cout << "չʾ�Թ�·�������س�������һ֡����ǰ֡ = " << i << endl;
    maze[path[i].x][path[i].y] = '!';
    for (int i = 1; i <= size_x; i++) {
      for (int j = 1; j <= size_y; j++) {
        cout << maze[i][j];
      }
      cout << endl;
    }
    getchar();
  }
  cout << "չʾ��ϣ�" << endl;
}


int main() {
  ShowWelcome();
  string choice;
INPUT:
  cout << "���ѡ����:";
  cin >> choice;
  if (choice != "1" && choice != "2") {
    cout << "������������������ " << endl;
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