template <class T>
class Utils {
 public:
  static void Swap(T* a, T* b) {
    T tmp = *a;
    *a = *b;
    *b = tmp;
  }
};  
