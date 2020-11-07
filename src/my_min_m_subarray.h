// 最小子段和, 划分成m个子段, 找一个划分方法,
// 使得其中最大的子段的和在所有划分方法里面最小
// todo 类里面可以存分段策略
#include "my_utils.h"
class MinSubarraySplit {
 private:
  const int* a;
  const int n;
  const int m;
  int** dp;

  void DP() {
    dp[n - 1][1] = a[n - 1];
    for (int i = n - 2; i >= 0; --i) {
      dp[i][1] = a[i] + dp[i + 1][1];
    }

    for (int j = 2; j <= m; ++j) {
      for (int i = 0; i <= n - j; ++i) {
        int sum_ai = a[i];  //用来累计计算a[i]到a[p]的和
        int min_sum = Utils<int>::Max(sum_ai, dp[i + 1][j - 1]);  //初始化最优解
        for (int p = i + 1; p <= n - j; ++p) {
          sum_ai += a[p];
          min_sum = Utils<int>::Min(min_sum,
                                    Utils<int>::Max(sum_ai, dp[p + 1][j - 1]));
        }
        dp[i][j] = min_sum;
      }
      // i=0, j=m的时候其实只需要算dp[0][j]不需要算其他dp[i][j],
      // 其他算出来是给下一次用的, 下一次用不上
    }
    MinMaxSum = dp[0][m];
  }

 public:
  int MinMaxSum;  // 结果直接暴露在外面, 懒得写API了

  MinSubarraySplit(const int* array, int length, int m_segment)
      : a(array), n(length), m(m_segment) {
    // dp(n*(m+1)) m从1开始用, 0空掉
    dp = new int*[n];
    for (int i = 0; i < n; ++i) dp[i] = new int[m + 1];
    DP();  //计算
    // 结果保存在MinMaxSum中
  }

  virtual ~MinSubarraySplit() {
    for (int i = 0; i < n; ++i) delete[] dp[i];
    delete[] dp;
  }
};