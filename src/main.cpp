#include <cmath>
#include <fstream>

#include "my_min_m_subarray.h"

int main() {
  std::fstream input("input.txt", std::ios_base::in);
  std::fstream output("output.txt", std::ios_base::out);
  int n, m;
  input >> n >> m;
  int* a = new int[n];
  for (int i = 0; i < n; ++i) {
    input >> a[i];
    a[i] = a[i] * a[i];
  }
  output << std::sqrt(MinSubarraySplit(a, n, m).MinMaxSum);
  input.close();
  output.close();
  delete[] a;
  return 0;
}