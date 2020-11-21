// 矩阵连乘
// 1. 备忘录LookupChain
// 2. dp
// 3. dfs
// 想了很久, dp的题还是写成C++风格吧, 相比C来说更好用代码也更简洁, 隐藏实现细节

#pragma once
#include <vector>
class MatrixChain {
 private:
  const int *p;
  const int n;
  int **m;

 public:
  int **s;

  MatrixChain(const int *dims, int n_matrix) : p(dims), n(n_matrix) {
    m = new int *[n + 1];  // n+1是为了让m[i]能表示p[i], p的长度是n+1
    s = new int *[n + 1];  // m 和s 的第一行和第一列都是用不上的
    for (int i = 0; i < n; ++i) {
      m[i] = new int[n];
      s[i] = new int[n];
    }
  }

  void DFS();
  void DP() {
    for (int i = 1; i <= n; ++i) m[i][i] = 0;
    for (int r = 2; r <= n; ++r) {  // r表示子结构[i...j]的长度
      for (int i = 1; i <= n - r + 1; i++) {
        int j = i + r - 1;

        //初始化为k=i的情况, m[i][i]可替换成0
        m[i][j] = m[i][i] + m[i + 1][j] + p[i - 1] * p[i] * p[j];
        s[i][j] = i;

        for (int k = i + 1; k < j; ++k) {  // i <= k < j
          int t = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
          if (t < m[i][j]) {
            m[i][j] = t;
            s[i][j] = k;
          }
        }
      }
    }
  }
  void Memorize(

  );
};
