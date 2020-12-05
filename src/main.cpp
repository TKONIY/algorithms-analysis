#include <fstream>
#include <iostream>

#include "my_subset_sum.h"
#include "my_utils.h"
int main() {
  std::ifstream is("input.txt");
  if (!is.is_open()) std::cout << "文件没开" << std::endl;
  std::ofstream os("output.txt");

  int n, c;
  is >> n >> c;
  int* S = new int[n + 1];
  for (int i = 1; i <= n; ++i) is >> S[i];

  SubsetSum s(S, n, c);
  if (!s.found) {
    os << "No Solution!";
    return 0;
  }
  for (int i = 1; i <= n; ++i) {
    if (s.x[i]) os << S[i] << " ";
  }
  os << std::endl;
  return 0;
}