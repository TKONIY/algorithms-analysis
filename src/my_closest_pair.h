#pragma once
#include <algorithm>
#include <cfloat>
#include <cmath>
#include <iostream>
#include <queue>
#include <unordered_map>

#include "my_merge_sorts.h"
#include "my_qsorts.h"

/**
 * N = 总个数
 * m = S中各点x坐标的中位数
 * 所有点按x和y排序存放在两个数组X和Y中
 * 先存放到X，再复制到Y，分别排序
 */

/**
 * 存储在以横坐标排序的数组中的点。
 */

struct Point2d {
  Point2d(float x, float y) : x(x), y(y) {}
  float x, y;
  friend std::ostream& operator<<(std::ostream& os, const Point2d& p) {
    os << "(" << p.x << ", " << p.y << ")";
    return os;
  }
};
struct PointX : public Point2d {
  PointX(float x = 0, float y = 0) : Point2d(x, y) {}
  bool operator<=(const PointX& a) const { return x <= a.x; }
  bool operator>=(const PointX& a) const { return x >= a.x; }
  bool operator<(const PointX& a) const { return x < a.x; }
  friend std::ostream& operator<<(std::ostream& os, const PointX& p) {
    os << "(" << p.x << ", " << p.y << ")";
    return os;
  }
};

struct PointY : public Point2d {
  PointY(float x = 0, float y = 0) : Point2d(x, y) {}
  int p;  //同一个点在数组X中的坐标
  bool operator<=(const PointY& a) const { return y <= a.y; }
  bool operator>=(const PointY& a) const { return y >= a.y; }
  bool operator<(const PointY& a) const { return x < a.x; }
  friend std::ostream& operator<<(std::ostream& os, const PointY& p) {
    os << "(" << p.x << ", " << p.y << ")";
    return os;
  }
};

inline float distance(const Point2d* u, const Point2d* v) {
  float dx = u->x - v->x;
  float dy = u->y - v->y;
  //   std::cout << *u << *v << std::sqrt(dx * dx + dy * dy) << std::endl;
  return std::sqrt(dx * dx + dy * dy);
}

// class CPair2d {
// public:
void BruteForce(PointX X[], int l, int r, PointX* a, PointX* b, float* d) {
  if (l == r) throw "至少要两个点";
  // 只有比当前的d要小的时候才存放
  *d = FLT_MAX;
  for (int i = l; i < r; ++i) {
    for (int j = i + 1; j <= r; ++j) {
      float dij = distance(&X[i], &X[j]);
      if (dij < *d) {
        *d = dij;
        *a = X[i];
        *b = X[j];
      }
    }
  }
}

void closest(PointX X[], PointY Y[], PointY Z[], int l, int r, PointX& a,
             PointX& b,
             float& d) {  //计算X[l-r]中的最近点对
  if (r - l == 1) {
    a = X[l];
    b = X[r];
    d = distance(&X[l], &X[r]);
    return;
  }
  if (r - l == 2) {
    float d1 = distance(&X[l], &X[l + 1]);
    float d2 = distance(&X[l + 1], &X[r]);
    float d3 = distance(&X[l], &X[r]);
    if (d1 <= d2 && d1 <= d3) {
      a = X[l];
      b = X[l + 1];
      d = d1;
      return;
    }
    if (d2 <= d3) {
      a = X[l + 1];
      b = X[r];
      d = d2;
      return;
    } else {
      a = X[l];
      b = X[r];
      d = d3;
      return;
    }
  }

  //多于3个点 分治法
  int m = (l + r) / 2;
  int li = l, ri = m + 1;  // 用r来
  for (int i = l; i <= r; ++i) {
    // 根据这个点在X中轴线左侧还是右侧，将他分配到Y2中
    if (Y[i].p > m)
      Z[ri++] = Y[i];
    else
      Z[li++] = Y[i];
  }

  //分治法计算两边的最接近点对结果， 将Y2临时和Y1交换，作为子问题的
  // printf(" 11\n");
  closest(X, Z, Y, l, m, a, b, d);
  // printf(" 12\n");
  float dr;
  PointX ar, br;
  closest(X, Z, Y, m + 1, r, ar, br, dr);
  // printf(" 13\n");
  if (dr < d) {
    a = ar;
    b = br;
    d = dr;
  }
  // printf("3\n");

  //恢复Y1, 否则很可能被破坏了, 先将Y1Y2换回来，恢复我当前问题的Y1
  MSort<PointY>::Merge(Z, Y, l, m, r);

  //从Y2[k]开始存放d矩形条内的点, 按Y排序
  int k = l;
  for (int i = l; i <= r; ++i) {
    if (fabs(Y[m].x - Y[i].x) < d) Z[k++] = Y[i];
  }

  // printf("4\n");
  //一共有k个点有可能成为最接近点对, 搜他们
  for (int i = l; i < k; ++i) {
    for (int j = i + 1; j < k && Z[j].y - Z[i].y < d; ++j) {
      float dp = distance(&Z[i], &Z[j]);
      if (dp < d) {
        d = dp;
        a = X[Z[i].p];
        b = X[Z[j].p];
      }
    }
  }
  // printf("NBF l=%d r=%d", l, r);
  // std::cout << *a << *b << *d << std::endl;
  // std::cout << "NBFF" << std::endl;
}
// PointX* X;   //输入的点, 可修改
// PointY* Y1;  //按Y排序的点
// PointY* Y2;  // Y2是将Y1按照X中轴线分成的点
// int n;       //个数

// public:
//	const int BF = 0;
//	const int C2 = 1;
//	// 存放中间结果与最后结果,全局变量, 不传参了
//	PointX fa;
//	PointX fb;
//	float fd;

static void CPair2d(PointX X[], int n, PointX& a, PointX& b, float& d) {
  if (n < 2) return;
  // 预排序 X Y数组
  std::sort(X, X + n);
  auto Y = new PointY[n];
  for (int i = 0; i < n; ++i) {
    Y[i].p = i;
    Y[i].x = X[i].x;
    Y[i].y = X[i].y;
  }
  std::sort(Y, Y + n);
  auto Z = new PointY[n];

  closest(X, Y, Z, 0, n - 1, a, b, d);
  delete[] Y;
  delete[] Z;
}

struct Pair {
  PointX a;
  PointX b;
};

//添加到Q队列中
static void UpdateQ(std::queue<Pair>* Q, const Pair& p, int size) {
  if (Q->empty())
    Q->push(p);
  else if (distance(&Q->back().a, &Q->back().b) >= distance(&p.a, &p.b)) {
    Q->push(p);
    if (Q->size() > size) Q->pop();
  }
  return;
}

void closest_logn(PointX X[], PointY Y[], PointY Z[], int l, int r, PointX& a,
                  PointX& b, float& d, std::queue<Pair>* Q,
                  int size) {  //计算X[l-r]中的size个最近点对

  printf("l = %d r = %d\n", l, r);
  if (r - l == 1) {
    UpdateQ(Q, Pair({X[l], X[l + 1]}), size);
    a = X[l];
    b = X[r];
    d = distance(&X[l], &X[r]);
    return;
  }
  if (r - l == 2) {
    UpdateQ(Q, Pair({X[l], X[l + 1]}), size);
    UpdateQ(Q, Pair({X[l + 1], X[r]}), size);
    UpdateQ(Q, Pair({X[l], X[r]}), size);

    float d1 = distance(&X[l], &X[l + 1]);
    float d2 = distance(&X[l + 1], &X[r]);
    float d3 = distance(&X[l], &X[r]);

    if (d1 <= d2 && d1 <= d3) {
      a = X[l];
      b = X[l + 1];
      d = d1;
    } else if (d2 <= d3) {
      a = X[l + 1];
      b = X[r];
      d = d2;
    } else {
      a = X[l];
      b = X[r];
      d = d3;
    }
    return;
  }

  int m = (l + r) / 2;
  int li = l, ri = m + 1;  // 用r来
  for (int i = l; i <= r; ++i) {
    if (Y[i].p > m)
      Z[ri++] = Y[i];
    else
      Z[li++] = Y[i];
  }

  //分治法计算两边的最接近点对结果， 将Y2临时和Y1交换，作为子问题的
  closest_logn(X, Z, Y, l, m, a, b, d, Q, size);
  float dr;
  PointX ar, br;
  closest_logn(X, Z, Y, m + 1, r, ar, br, dr, Q, size);
  if (dr < d) {
    a = ar;
    b = br;
    d = dr;
  }

  // Z 分成两部分, 都按照y排序, 左半部分的x小于右半部分的x
  MSort<PointY>::Merge(Z, Y, l, m, r);

  //不能将左右混合成一个数组来进行判断，可以左右交分别查找
  //对左边的所有元素进行查找

  // 从Z[l]开始存放d矩形条内的点, 按Y排序, 并且用m分开
  // 先存中轴线左边距离d内的点(从l开始), 再存右半部分的点(从m开始)
  // 对于每个左边的点, 需要记录它在右边的起始搜索位置,
  // 方法是每次添加一个右边的点时候,
  // 它的左边为左边未包含记录的点(从prel开始)的起始搜索位置
  int le = l, re = m,  //标记结束
      prel = l;  // prel标记[没有记录起始搜索位置的点]的坐标

  std::unordered_map<int, int> begin;
  for (int i = l; i <= r; ++i) {
    if ((Y[m].x - Y[i].x < d) && (Y[m].x - Y[i].x > 0))
      Z[le++] = Y[i];
    else if ((Y[i].x - Y[m].x < d) && (Y[i].x - Y[m].x >= 0)) {
      while (prel < le) {
        begin[prel++] = re;
      }
      Z[re++] = Y[i];
    }
  }
  while (prel < le) begin[prel++] = re - 1;

  // int k = l;
  // for (int i = l; i <= r; ++i) {
  //   if (fabs(Y[m].x - Y[i].x) < d) Z[k++] = Y[i];
  // }

  //对每个左半部分的点, 在右半部分搜一下它的最近点对,
  //记录左边元素的下一元素在右边的位置往上搜和往下搜
  for (int i = l; i < le; ++i) {
    int j = begin[i];  //右边对应的起始元素
    // printf("i = %d j = %d\n", i, j);
    //先确定一下右边的点要不要搜, 如果点j偏上了就考虑j-1,如果偏下了就直接跳过
    if (Z[j].y - Z[i].y >= d) j = j - 1;           // j-1一定小于i
    if (j <= m || Z[i].y - Z[j].y >= d) continue;  //跳过

    //往上找
    if (Z[j].y < Z[i].y) j = j + 1;  // j是恰好>=i的那个
    for (int k = j; k < re && Z[k].y - Z[i].y < d; ++k) {
      UpdateQ(Q, Pair({X[Z[i].p], X[Z[k].p]}), size);
      float dp = distance(&Z[i], &Z[k]);
      if (dp < d) {
        d = dp;
        a = X[Z[i].p];
        b = X[Z[k].p];
      }
    }

    j = j - 1;  // 改成小于i的那个
    //往下找
    for (int k = j; k >= le && Z[i].y - Z[k].y < d; --k) {
      UpdateQ(Q, Pair({X[Z[i].p], X[Z[k].p]}), size);
      float dp = distance(&Z[i], &Z[k]);
      if (dp < d) {
        d = dp;
        a = X[Z[i].p];
        b = X[Z[k].p];
      }
    }
  }

  //不能使用混合数组的方法搜
  // for (int i = l; i < k; ++i) {
  //   for (int j = i + 1; j < k && Z[j].y - Z[i].y < d; ++j) {
  //     float dp = distance(&Z[i], &Z[j]);
  //     if (dp < d) {
  //       d = dp;
  //       a = X[Z[i].p];
  //       b = X[Z[j].p];
  //     }
  //   }
  // }
}

static void CPair2dlogn(PointX X[], int n, PointX& a, PointX& b, float& d,
                        std::queue<Pair>* Q) {
  if (n < 2) return;
  // 预排序 X Y数组
  std::sort(X, X + n);
  auto Y = new PointY[n];
  for (int i = 0; i < n; ++i) {
    Y[i].p = i;
    Y[i].x = X[i].x;
    Y[i].y = X[i].y;
  }
  std::sort(Y, Y + n);
  auto Z = new PointY[n];

  closest_logn(X, Y, Z, 0, n - 1, a, b, d, Q, std::log2(n));
  delete[] Y;
  delete[] Z;
}