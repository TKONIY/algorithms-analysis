#include <cmath>
#include <fstream>

#include "my_optimal_BST.h"
int main() {
  //生成a b的数据
  const int n = 5;
  int a[n + 1]{5, 10, 5, 5, 5, 10};
  int b[n + 1]{0, 15, 10, 5, 10, 20}; 
  auto bst = OptimalBST(n, a, b);
  Utils<int>::Cout2Darray(bst.get_w(), n + 2, n + 2);
  std::cout << std::endl;
  Utils<int>::Cout2Darray(bst.get_m(), n + 2, n + 2);
  std::cout << std::endl;
  Utils<int>::Cout2Darray(bst.get_s(), n + 2, n + 2);
  std::cout << std::endl;
}