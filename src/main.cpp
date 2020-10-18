#include "my_mode.h"
#include <cstdio>
int main() {
  int a[] = {1, 2, 3, 4, 4, 5, 6, 5, 1, 2, 4, 4, 4, 4, 4, 5, 1, 2, 3, 5};
  FindTheMode<int> res(a, 0, sizeof(a) / sizeof(int) - 1);
  printf("val:%d, n:%d\n", a[res.element_i], res.largest);
}