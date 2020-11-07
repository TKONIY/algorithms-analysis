#include "my_select.h"
template <class T>
class FindTheMode {
 public:
  /** todo 这些都应该设置成private, 但是由于为了让代码简洁,
   * 就直接暴露在外面好了吧
   */
  int largest;   /*最大出现次数*/
  int element_i; /*元素下标*/
  T* a;          /*数组*/

  FindTheMode(T a[], int l, int r) : a(a), largest(1), element_i(0) {
    RecurFind(l, r);
  }

  static int Split(T a[], int l, int r, int pivot_i, int* l_bound,
                   int* r_bound) {
    int p = QSort<T>::Partition(a, l, r, pivot_i);
    bool find_pivot = false;
    for (int i = l; i < r; ++i) {
      if (!find_pivot) {
        if (a[i] == a[p]) {
          find_pivot = true;
          *l_bound = i;
        }
      } else {
        if (a[i] != a[p]) {
          *r_bound = i - 1;
          return p;
        }
      }
    }
    *r_bound = r - 1;
    return p;
  }

 private:
  void RecurFind(int l, int r) {
    int mid_i = Select<T>::LinearSelect(a, l, r, (r - l) / 2);
    int l1, r1;
    mid_i = Split(a, l, r, mid_i, &l1, &r1);
    if (largest < r1 - l1 + 1) {
      largest = r1 - l1 + 1;
      element_i = mid_i;
    }
    if (l1 - l > largest) RecurFind(l, l1 - 1);
    if (r - r1 > largest) RecurFind(r1 + 1, r);
  }
};
