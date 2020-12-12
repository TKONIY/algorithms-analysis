#include <fstream>
#include <iostream>

// #include "my_best_merge.h"
#include "my_service_sequence.h"
int main() {
  std::ifstream is("input.txt");
  if (!is.is_open()) {
    std::cout << "文件没开" << std::endl;
    exit(-1);
  }
  std::ofstream os("output.txt");
  // int k;
  // is >> k;
  // int *lens = new int[k];
  // for (int i = 0; i < k; ++i) is >> lens[i];
  // BestMerge bm(lens, k);
  // os << bm.worst_n_merge << " " << bm.best_n_merge << std::endl;

  int n;
  is >> n;
  int* time = new int[n];
  for (int i = 0; i < n; ++i) is >> time[i];
  os << Service(n, time).avg_wait_time << std::endl;
  return 0;
}