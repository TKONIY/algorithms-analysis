#include <cstdio>

#include "my_min_m_subarray.h"
int main() {
  int a[] = {5, 4, 3, 2, 1}, n = 5, m = 3;
  printf("%d\n", MinSubarraySplit(a, n, m).MinMaxSum);
}