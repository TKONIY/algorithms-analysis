template <class T>
class MSort {
 public:
  static void Merge(const T c[], T d[], int l, int m, int r) {
    int i = l, j = m + 1, k = l;
    while (i <= m && j <= r) {
      if (c[i] <= c[j])
        d[k++] = c[i++];
      else
        d[k++] = c[j++];
    }
    while (i <= m) d[k++] = c[i++];
    while (j <= r) d[k++] = c[j++];
  }
};