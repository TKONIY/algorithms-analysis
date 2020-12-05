#include <chrono>

#include "data.h"
#include "my_closest_pair.h"

inline void ShowResult(PointX* X, int n) {
  PointX a, b;
  float d = 0;
  auto start = std::chrono::high_resolution_clock::now();
  CPair2d(X, n, a, b, d);
  auto end = std::chrono::high_resolution_clock::now();
  auto t = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

  printf("N = %d \t最近点对: ", n);
  std::cout << a << b;
  printf("\t距离 %f\t用时 %ldus\n", d, t.count());
}

inline void ShowResultLogn(PointX* X, int n) {
  PointX a, b;
  float d = 0;
  std::queue<Pair> Q;

  auto start = std::chrono::high_resolution_clock::now();
  CPair2dlogn(X, n, a, b, d, &Q);
  auto end = std::chrono::high_resolution_clock::now();
  auto t = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

  printf("N = %d\t   最近点对个数%lu", n, Q.size());
  std::cout << a << b;
  printf("\t距离 %f\t用时 %ldus\n", d, t.count());
  while (!Q.empty()) {
    std::cout << Q.front().a << Q.front().b << std::endl;
    Q.pop();
  }
}

int main() {
  PointX a100[100], a1k[1000], a1w[10000], a10w[100000];
  Data::GenPoints2d(a100, 100, 0, 100000);
  Data::GenPoints2d(a1k, 1000, 0, 100000);
  Data::GenPoints2d(a1w, 10000, 0, 100000);
  Data::GenPoints2d(a10w, 100000, 0, 100000);
  ShowResult(a100, 100);
  ShowResult(a1k, 1000);
  ShowResult(a1w, 10000);
  ShowResult(a10w, 100000);
  // ShowResultLogn(a100, 100);
  // ShowResultLogn(a1k, 1000);
  // ShowResultLogn(a1w, 10000);
  // ShowResultLogn(a10w, 100000);
}