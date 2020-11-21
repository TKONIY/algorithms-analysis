#pragma once
#include <iostream>

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

  static T** New2Darray(int n) {
    return New2Darray(n, n);
  }  //同一个模板类里面调用其他函数不用加模板

  static T** New2Darray(int n, int m) {
    T** a = new T*[n];
    for (int i = 0; i < n; ++i) a[i] = new T[m];
    return a;
  }

  static void Delete2Darray(T** a, int row) {
    for (int i = 0; i < row; ++i) delete[] a[i];
    delete[] a;
  }

  static void Cout2Darray(const T* const* a, int n, int m) {
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        std::cout << a[i][j] << " ";
      }
      std::cout <<std::endl;
    }
  }
};
