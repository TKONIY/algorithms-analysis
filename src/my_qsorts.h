/**
 * Author: TKONIY
 * Date: 2020/10/18
 * Discription:
 *  simple implemention for
 *
 */
#include "my_utils.h"

template <class T>
class QSort {
 public:
  static int Partition(T a[], int l, int r, int pivot_i) {
    Utils<T>::Swap(&a[l], &a[pivot_i]);
    T pivot = a[l];
    while (l < r) {
      while (l < r && a[r] >= pivot) --r;
      a[l] = a[r];
      while (l < r && a[l] <= pivot) ++l;
      a[r] = a[l];
    } /* stop at l==r */
    a[l] = pivot;
    return l;
  }

  static void RandomizeQSort(T a[], int l, int r) {
    if (l < r) {
      int pivot_i = l + rand() % (r - l + 1); /*randomize pivot*/
      pivot_i = Partition(a, l, r, pivot_i);
      RandomizeQSort(a, l, pivot_i - 1);
      RandomizeQSort(a, pivot_i + 1, r);
    }
  }
};
