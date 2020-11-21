/**
 * 存取概率
 * x[1~n]
 * 输入:
 * a[0~n] 在第x[i]和x[i+1]之间找到的概率
 * b[1~n] 在第x[i]个元素找到的概率
 * 中间:
 * m[i,j]为子树x[i~j]的最小耗费
 * w[i,j]为子树x[i~j]的概率和
 *
 * w[i][j] = w[i][j-1] + a[j] + b[j]
 * implys: w[i][i] = w[i][i-1] + a[i] + b[i]
 *                 = a[i-1] + a[i] + b[i]
 *       ∴    w[i+1][i] = a[i]
 */
#pragma once
#include "my_utils.h"
class OptimalBST {
 private:
  int n;
  const int* a;
  const int* b;
  int** w;
  int** m;
  int** s;

  void DP() {
    // init
    for (int i = 0; i <= n; ++i) {
      w[i + 1][i] = a[i];
      m[i + 1][i] = 0;
    }
    // dp
    for (int r = 0; r < n; r++) {  //间距最大为n-1
      for (int i = 1; i <= n - r; ++i) {
        int j = i + r;
        w[i][j] = w[i][j - 1] + a[j] + b[j];
        m[i][j] = m[i + 1][j];  //最后才加w[i][j], 作比较的只是m
        s[i][j] = i;            //初值设置i为根节点
        for (int k = i + 1; k <= j; ++k) {  //从第i+1个根节点开始考虑
          int t = m[i][k - 1] + m[k + 1][j];
          if (t < m[i][j]) {
            m[i][j] = t;
            s[i][j] = k;
          }
          m[i][j] += w[i][j];
        }
      }
    }
  }

 public:
  OptimalBST(int len, const int* arra_a, const int* arr_b)
      : n(len), a(arra_a), b(arr_b) {
    w = Utils<int>::New2Darray(n);
    m = Utils<int>::New2Darray(n);
    s = Utils<int>::New2Darray(n);
    DP();
  }
  ~OptimalBST() {
    Utils<int>::Delete2Darray(w, n);
    Utils<int>::Delete2Darray(w, n);
    Utils<int>::Delete2Darray(w, n);
  }
  const int* const* get_s() const { return s; }
};