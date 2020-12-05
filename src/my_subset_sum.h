#pragma once
class SubsetSum {
 private:
  const int* S;  // S[0..n]
  int n;
  int c;   // c
  int cw;  // current sum
  int r;   // remain

  void Backtrack(int i) {
    if (found) return;
    if (cw == c) {  //刚好找到了相等的, 不再递归
      found = true;
      return;
    }
    if (i > n) return;

    r -= S[i];
    if (cw + S[i] <= c) {  //左子树
      x[i] = true;
      cw += S[i];
      Backtrack(i + 1);
      cw -= S[i];
    }
    if (found) return;  //左子树找到了就返回
    if (cw + r >= c) {  //右子树
      x[i] = false;
      Backtrack(i + 1);
    }
    r += S[i];
    return;
  }

 public:
  bool* x;  // solution
  bool found;

  // S从1开始
  SubsetSum(const int* S_, int n_, int c_)
      : x(new bool[n + 1]), S(S_), n(n_), c(c_) {
    r = 0;
    for (int i = 1; i <= n; ++i) r += S_[i];
    cw = 0;
    found = false;
    Backtrack(1);
  }
  ~SubsetSum() { delete[] x; }
};
