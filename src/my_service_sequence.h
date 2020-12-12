#pragma once
#include "my_qsorts.h"
class Service {
 private:
 public:
  float avg_wait_time = 0;  //最小服务时间
  Service(int n, int* service_times) {
    QSort<int>::RandomizeQSort(service_times, 0, n - 1);
    int pre = 0;
    for (int i = 0; i < n ; ++i) {
      pre += service_times[i];
      avg_wait_time += pre;
    }
    avg_wait_time /= n;
  }
  ~Service() = default;
};