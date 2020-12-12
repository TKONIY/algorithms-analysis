#pragma once
#include "my_qsorts.h"
class BestMerge {
 public:
  int best_n_merge = 0;
  int worst_n_merge = 0;
  BestMerge(int* lens_, int k) {
    if (!k) return;
    QSort<int>::RandomizeQSort(lens_, 0, k - 1);
    //从小到大merge就是bestMerge
    int pre = lens_[0];
    for (int i = 1; i < k; ++i) {
      pre += lens_[i];
      best_n_merge += pre - 1;
    }
    pre = lens_[k - 1];
    for (int i = k - 2; i >= 0; --i) {
      pre += lens_[i];
      worst_n_merge += pre - 1;
    }
  }
  ~BestMerge() = default;
};