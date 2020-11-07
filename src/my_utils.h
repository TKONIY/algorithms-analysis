template <class T>
class Utils {
 public:
  static void Swap(T* a, T* b) {
    T tmp = *a;
    *a = *b;
    *b = tmp;
  }
  static const T& Max(const T& a, const T& b) { return a > b ? a : b; }
  static const T& Min(const T& a, const T& b) { return a < b ? a : b; }
};
