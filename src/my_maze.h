#include "my_utils.h"
class Maze {
 private:
  int n, m, k;     // n*m的网格, k个封闭房间
  int x1, y1;      //罗密欧的位置
  int x2, y2;      //朱丽叶的位置
  int n_turn = 0;  //转弯次数

  int** board;  // 地图, -1为封闭房间
  //表示各个方向上的加减,direction为1-8的数字对应这些方向
  const int dx[9]{0, -1, -1, -1, 0, 1, 1, 1, 0};
  const int dy[9]{0, -1, 0, 1, 1, 1, 0, -1, -1};

  void Search(int depth, int x, int y, int direction) {
    std::cout << "search" << std::endl;
    if (depth == m * n - k && x == x2 && y == y2 && n_turn <= best_n_turn) {
      if (n_turn < best_n_turn) {  //有更好的解
        best_n_turn = n_turn;
        n_best = 1;
        Save();
      } else {  //有与最优解相同的解
        n_best++;
      }
      return;
    }
    if (depth == m * n - k || (x == x2 && y == y2) || n_turn > best_n_turn) {
      //如果已经走完了但是终点不对, 或 提前走到终点 或不是最优解
      return;
    }
    for (int i = 1; i <= 8; ++i) {  //遍历八个方向
      if (Stepok(x + dx[i], y + dy[i])) {
        board[x + dx[i]][y + dy[i]] = depth + 1;  //记录步数
        //计算转弯次数的时候第一次不算
        if (direction != i && depth != 1) n_turn++;
        Search(depth + 1, x + dx[i], y + dy[i], i);
        if (direction != i && depth != 1) n_turn--;
        board[x + dx[i]][y + dy[i]] = 0;  //回复步数
      }
    }
  }

  void Save() {
    for (int i = 1; i <= n; ++i) {
      for (int j = 1; j <= m; ++j) {
        best_board[i][j] = board[i][j];
      }
    }
  }
  bool Stepok(int x, int y) {
    //判断是否越界或到了封闭房间或已经走过
    return (x > 0 && x <= n && y > 0 && y <= m && board[x][y] == 0);
  }

 public:
  int best_n_turn = INT32_MAX;  //最少的转弯次数
  int n_best = 0;       // 最优解的个数
  int** best_board;     //最优解

  Maze(int n_, int m_, int k_, int** board_, int x1_, int y1_, int x2_, int y2_)
      : n(n_), m(m_), k(k_), board(board_), x1(x1_), y1(y1_), x2(x2_), y2(y2_) {
    best_board = Utils<int>::New2Darray(n + 1, m + 1);
    board[x1][y1] = 1;
    Search(1, x1, y1, 0);
  }
  ~Maze() { Utils<int>::Delete2Darray(best_board, n + 1); }
};