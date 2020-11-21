#pragma once
#include "my_utils.h"

/**
 * S是步数, 第一步为0, 走到终点一共2n-2步
 * 当前x+y = S;
 */
template <int MAX_N>
class TwoCollectionRoute {
 private:
  int dp[MAX_N][MAX_N][MAX_N][MAX_N]{0};
  const int *const *a;
  int n;
  void DP() {
    dp[0][0][0][0] = a[0][0];
    for (int s = 0; s <= n + n - 2; ++s)
      for (int x1 = 0; x1 <= s; ++x1)
        for (int x2 = 0; x2 <= s; ++x2) {
          int y1 = s - x1;
          int y2 = s - x2;
          if (x1 >= n || y1 >= n || x2 >= n || y2 >= n) continue;
          int v = dp[x1][y1][x2][y2];
          //更新接下来四个点的值
          val(x1 + 1, x2 + 1, y1, y2, v);
          val(x1 + 1, x2, y1, y2 + 1, v);
          val(x1, x2 + 1, y1 + 1, y2, v);
          val(x1, x2, y1 + 1, y2 + 1, v);
        }
    max_value = dp[n - 1][n - 1][n - 1][n - 1];
  }
  void val(int x1, int x2, int y1, int y2, int v) {
    // 只要有一个点越界那么全都不用算了
    if (x1 >= n || y1 >= n || x2 >= n || y2 >= n) return;

    if (x1 == x2 && y1 == y2) {  //同一个点 只collect一次
      dp[x1][y1][x2][y2] = Utils<int>::Max(dp[x1][y1][x2][y2], v + a[x1][y1]);
    } else {
      dp[x1][y1][x2][y2] =
          Utils<int>::Max(dp[x1][y1][x2][y2], v + a[x1][y1] + a[x2][y2]);
    }
  }

 public:
  int max_value;
  TwoCollectionRoute(const int *const *array, int length)
      : a(array), n(length) {
    DP();
  }
};
