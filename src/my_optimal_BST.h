/**
 * 存取概率
 * x[1~n]
 * 输入:
 * a[0~n] 在第x[i]和x[i+1]之间找到的概率
 * b[1~n] 在第x[i]个元素找到的概率
 * 中间:
 * m[i,j]为子树x[i~j]的最小耗费
 * w[i,j]为子树x[i~j]的概率和
 * 長度都是N+2
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
  const double* a;
  const double* b;
  double** w;
  double** m;
  int** s;

  void DP1() {
    // init
    for (int i = 0; i <= n; ++i) {
      w[i + 1][i] = a[i];
      m[i + 1][i] = 0;
    }
    // dp
    for (int r = 0; r < n; ++r) {  //间距最大为n-1
      for (int i = 1; i <= n - r; ++i) {
        int j = i + r;
        w[i][j] = w[i][j - 1] + a[j] + b[j];
        m[i][j] = m[i + 1][j];  //最后才加w[i][j], 作比较的只是m
        s[i][j] = i;            //初值设置i为根节点
        for (int k = i + 1; k <= j; ++k) {  //从第i+1个根节点开始考虑
          double t = m[i][k - 1] + m[k + 1][j];
          if (t < m[i][j]) {
            m[i][j] = t;
            s[i][j] = k;
          }
        }
        m[i][j] += w[i][j];
      }
    }
  }

  void DP2() {
    for (int i = 0; i <= n; ++i) {
      w[i + 1][i] = a[i];
      m[i + 1][i] = 0;
      s[i + 1][i] = 0;  // 初始化为0, 缩小ij范围时使用, 约束,防止出错
    }

    for (int r = 0; r < n; ++r) {  //间距最大为n-1
      for (int i = 1; i <= n - r; ++i) {
        int j = i + r;
        // 使用Knuth的改进缩小(i,j)范围到(i1, j1),
        int i1 = s[i][j - 1] > i ? s[i][j - 1] : i;
        int j1 = s[i][j - 1] > i ? s[i + 1][j] : j;

        w[i][j] = w[i][j - 1] + a[j] + b[j];
        m[i][j] = m[i][i1 - 1] + m[i1 + 1][j];  //初始从i1开始
        s[i][j] = i;
        for (int k = i1 + 1; k <= j1; ++k) {  //到j1结束
          double t = m[i][k - 1] + m[k + 1][j];
          if (t < m[i][j]) {
            m[i][j] = t;
            s[i][j] = k;
          }
        }
        m[i][j] += w[i][j];
      }
    }
  }

  int dfs_height(int i, int j) const {
    if (i > j) return 0;
    return 1 + Utils<int>::Max(dfs_height(i, s[i][j] - 1),
                               dfs_height(s[i][j] + 1, j));
  }

 public:
  OptimalBST(int len, const double* arra_a, const double* arr_b,
             int algorithm = 1)
      : n(len), a(arra_a), b(arr_b) {
    w = Utils<double>::New2Darray(n + 2);
    m = Utils<double>::New2Darray(n + 2);
    s = Utils<int>::New2Darray(n + 2);

    switch (algorithm) {
      case 1:
        DP1();
        break;
      case 2:
        DP2();
        break;
      default:
        std::cout << "please choose algorithm in [1, 2]" << std::endl;
        break;
    }
  }
  ~OptimalBST() {
    Utils<double>::Delete2Darray(w, n + 2);
    Utils<double>::Delete2Darray(m, n + 2);
    Utils<int>::Delete2Darray(s, n + 2);
  }
  const int* const* get_s() const { return s; }
  const double* const* get_w() const { return w; }
  const double* const* get_m() const { return m; }

  //计算树高
  int get_height() const {
    int i = 1, j = n;
    return dfs_height(i, j);
  }
};