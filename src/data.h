#include <algorithm>
#include <cfloat>
#include <cstring>
#include <ctime>
#include <random>

#include "my_closest_pair.h"
#include "my_utils.h"
class Data {
 public:
  // 红包算法 生成n个和为sum的整数值叠加到红包上, up_bound限制每个红包的最大值，
  // a[0]可能会超出限制
  static void RedPackages(int n, double sum, double* arr,
                          double up_bound = DBL_MAX) {
    std::random_device rd;
    arr[0] = sum;  // a[0]直接存剩下的值
    do {
      for (int i = n - 1; i > 0; --i) {  // i+1 为剩余红包数
        double upper =
            Utils<double>::Min(arr[0] * 2 / (i + 1), up_bound - arr[i]);
        std::uniform_real_distribution<> dist(0.0, upper);  //均匀分布
        double p = dist(rd);
        arr[i] += p;
        arr[0] -= p;
      }
    } while (arr[0] > up_bound);
  }

 public:
  //全部查找成功, 并且关键字等概率, n为节点个数
  static void AvgSuccess(double* a, double* b, int n) {
    std::fill(a, a + n + 1, 0);
    b[0] = 0;
    double avg = 1.0 / n;
    for (int i = 1; i <= n; ++i) b[i] = avg;
  }
  static void Avg(double* a, double* b, int n) {
    int count = 2 * n + 1;
    b[0] = 0;
    a[0] = 1.0 / count;
    for (int i = 1; i <= n; ++i) a[i] = b[i] = a[0];
  }

  /**
   * suc_rate 查找成功的总概率
   * 成功的情况下10%的概率为成功的60%
   * 最高查找成功概率小于10/n
   */
  static void NaturalRand(double* a, double* b, int n, double suc_rate) {
    if (n < 10) {
      std::cerr << "n should at least be 10" << std::endl;
      return;
    }
    std::fill(a, a + n + 1, 0);
    std::fill(b, b + n + 1, 0);
    double upper = 10.0 / n;
    // b中10%的元素概率和为suc_rate * 0.6
    // 其余90%元素的概率和为suc_rate * 0.4
    // 先按序分配再shuffle
    double sum1 = suc_rate * 0.6;
    double sum2 = suc_rate * 0.4;
    int i = n / 10;  //前10%元素的结尾元素为b+i
    RedPackages(i, sum1, b + 1, upper);
    RedPackages(n - i, sum2, b + i + 1, upper);
    // shuffle
    std::random_shuffle(b + 1, b + n + 1);
    // fill a;
    for (int i = 1; i <= n; ++i) {
      a[i - 1] += b[i];
      a[i] += b[i];
    }
    double suma = Utils<double>::Sum1Darray(a, n + 1);
    double ratio = (1 - suc_rate) / suma;
    for (int i = 0; i <= n; ++i) a[i] *= ratio;
  }

  static void GenPoints2d(Point2d* a, int n, float min, float max) {
    std::random_device rd;
    std::uniform_real_distribution<> dist(min, max);
    for (int i = 0; i < n; ++i) {
      a[i].x = dist(rd);
      a[i].y = dist(rd);
    }
  }
};