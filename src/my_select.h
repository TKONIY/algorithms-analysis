#include "my_qsorts.h"

template <class T>
class Select {
 public:
  /* select kth min elements, k range from 0, which diff from textbook*/
  /* return index instead of value*/
  static int LinearSelect(T a[], int l, int r, int k) {
    if (r - l < 5) {
      QSort<T>::RandomizeQSort(a, l, r);
      return l + k;
    }

    for (int i = 0; i <= (r - l - 4) / 5; i++) { /*(r-l-4)/5 subarrs*/
      int li = l + 5 * i, ri = l + 5 * i + 4;
      QSort<T>::RandomizeQSort(a, li, ri);   /*sort each 5 arr*/
      Utils<T>::Swap(&a[l + i], &a[li + 2]); /*middle num moved to front*/
    }

    int midn_i = LinearSelect(a, l, l + (r - l - 4) / 5,
                              (r - l - 4) / 10); /*rank from 0*/
    midn_i = QSort<T>::Partition(a, l, r, midn_i);

    int midn_rank = midn_i - l;
    if (k == midn_rank)
      return midn_i;
    else if (k < midn_rank)
      return LinearSelect(a, l, midn_i - 1, k);
    else
      return LinearSelect(a, midn_i + 1, r, k - midn_rank - 1);
  }
};