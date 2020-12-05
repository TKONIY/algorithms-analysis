#include <chrono>
#include <cmath>
#include <fstream>

#include "data.h"
#include "my_optimal_BST.h"
inline void ShowResult(const double* a, const double* b, int N) {
  auto start = std::chrono::high_resolution_clock::now();
  auto bst = OptimalBST(N, a, b, 2);
  auto end = std::chrono::high_resolution_clock::now();
  auto t = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

  printf("p(N=%d) = %lf  height = %d  %ldms\n", N, bst.get_m()[1][N],
         bst.get_height(), t.count());
  // Utils<int>::Cout2Darray(bst.get_s(), N + 2, N + 2);
  // Utils<double>::Cout2Darray(bst.get_m(), N + 2, N + 2);
  // Utils<double>::Cout2Darray(bst.get_w(), N + 2, N + 2);
}
int main() {
  // double a[5];
  // Data::RedPackages(5, 1, a, 0.200000);
  // Utils<double>::Cout1Darray(a, 5);
  // double sum = 0;
  // for (int i = 0; i < 5; ++i) sum += a[i];
  // std::cout << sum << std::endl;

  // const int N = 5000;
  // double a[N + 1];
  // double b[N + 1];
  // Data::NaturalRand(a, b, N, 0.8);
  // // Utils<double>::Cout1Darray(b, N + 1);
  // std::cout << Utils<double>::Sum1Darray(b, N + 1) << std::endl;
  // // Utils<double>::Cout1Darray(a, N + 1);
  // std::cout << Utils<double>::Sum1Darray(a, N + 1) << std::endl;
  //生成a b的数据
  // const int n = 5;
  // double a[n + 1]{0.05, 0.10, 0.05, 0.05, 0.05, 0.10};
  // double b[n + 1]{0, 0.15, 0.10, 0.05, 0.10, 0.20};
  // auto bst = OptimalBST(n, a, b, 1);
  // Utils<double>::Cout2Darray(bst.get_w(), n + 2, n + 2);
  // std::cout << std::endl;
  // Utils<double>::Cout2Darray(bst.get_m(), n + 2, n + 2);
  // std::cout << std::endl;
  // Utils<int>::Cout2Darray(bst.get_s(), n + 2, n + 2);
  // std::cout << std::endl;
  // std::cout << "height=" << bst.get_height() << std::endl;

  /*************************************************************/
  const int N1 = 100, N2 = 1000, N3 = 5000, N4 = 7, N5 = 15, N6 = 1023;

  // 平均, 全部成功
  double avg_suc_a1[N1 + 1], avg_suc_a2[N2 + 1], avg_suc_a3[N3 + 1],
      avg_suc_a4[N4 + 1], avg_suc_a5[N5 + 1], avg_suc_a6[N6 + 1];
  double avg_suc_b1[N1 + 1], avg_suc_b2[N2 + 1], avg_suc_b3[N3 + 1],
      avg_suc_b4[N4 + 1], avg_suc_b5[N5 + 1], avg_suc_b6[N6 + 1];
  Data::AvgSuccess(avg_suc_a1, avg_suc_b1, N1);
  Data::AvgSuccess(avg_suc_a2, avg_suc_b2, N2);
  Data::AvgSuccess(avg_suc_a3, avg_suc_b3, N3);
  Data::AvgSuccess(avg_suc_a4, avg_suc_b4, N4);
  Data::AvgSuccess(avg_suc_a5, avg_suc_b5, N5);
  Data::AvgSuccess(avg_suc_a6, avg_suc_b6, N6);

  // 平均, 成功概率和失败概率相同
  double avg_a1[N1 + 1], avg_a2[N2 + 1], avg_a3[N3 + 1], avg_a4[N4 + 1],
      avg_a5[N5 + 1], avg_a6[N6 + 1];
  double avg_b1[N1 + 1], avg_b2[N2 + 1], avg_b3[N3 + 1], avg_b4[N4 + 1],
      avg_b5[N5 + 1], avg_b6[N6 + 1];

  Data::Avg(avg_a1, avg_b1, N1);
  Data::Avg(avg_a2, avg_b2, N2);
  Data::Avg(avg_a3, avg_b3, N3);
  Data::Avg(avg_a4, avg_b4, N4);
  Data::Avg(avg_a5, avg_b5, N5);
  Data::Avg(avg_a6, avg_b6, N6);

  // 随机 8: 2
  double rand82_a1[N1 + 1], rand82_a2[N2 + 1], rand82_a3[N3 + 1];
  double rand82_b1[N1 + 1], rand82_b2[N2 + 1], rand82_b3[N3 + 1];
  Data::NaturalRand(rand82_a1, rand82_b1, N1, 0.8);
  Data::NaturalRand(rand82_a2, rand82_b2, N2, 0.8);
  Data::NaturalRand(rand82_a3, rand82_b3, N3, 0.8);

  // 随机 9: 1
  double rand91_a1[N1 + 1], rand91_a2[N2 + 1], rand91_a3[N3 + 1];
  double rand91_b1[N1 + 1], rand91_b2[N2 + 1], rand91_b3[N3 + 1];
  Data::NaturalRand(rand91_a1, rand91_b1, N1, 0.9);
  Data::NaturalRand(rand91_a2, rand91_b2, N2, 0.9);
  Data::NaturalRand(rand91_a3, rand91_b3, N3, 0.9);

  //随机1:9
  double rand19_a1[N1 + 1], rand19_a2[N2 + 1], rand19_a3[N3 + 1];
  double rand19_b1[N1 + 1], rand19_b2[N2 + 1], rand19_b3[N3 + 1];
  Data::NaturalRand(rand19_a1, rand19_b1, N1, 0.9);
  Data::NaturalRand(rand19_a2, rand19_b2, N2, 0.9);
  Data::NaturalRand(rand19_a3, rand19_b3, N3, 0.9);

  std::cout << "1. 全部查找成功, 关键字等概率" << std::endl;
  ShowResult(avg_suc_a1, avg_suc_b1, N1);
  ShowResult(avg_suc_a2, avg_suc_b2, N2);
  ShowResult(avg_suc_a3, avg_suc_b3, N3);
  ShowResult(avg_suc_a4, avg_suc_b4, N4);
  ShowResult(avg_suc_a5, avg_suc_b5, N5);
  ShowResult(avg_suc_a6, avg_suc_b6, N6);

  std::cout << "2. 包含查找成功和失败情况, 所有情况等概率" << std::endl;
  ShowResult(avg_a1, avg_b1, N1);
  ShowResult(avg_a2, avg_b2, N2);
  ShowResult(avg_a3, avg_b3, N3);
  ShowResult(avg_a4, avg_b4, N4);
  ShowResult(avg_a5, avg_b5, N5);
  ShowResult(avg_a6, avg_b6, N6);

  std::cout << "3. 查找成功概率为80%, 不成功为20% ..." << std::endl;
  ShowResult(rand82_a1, rand82_b1, N1);
  ShowResult(rand82_a2, rand82_b2, N2);
  ShowResult(rand82_a3, rand82_b3, N3);

  std::cout << "4. 查找成功概率为90%, 不成功为10% ..." << std::endl;
  ShowResult(rand91_a1, rand91_b1, N1);
  ShowResult(rand91_a2, rand91_b2, N2);
  ShowResult(rand91_a3, rand91_b3, N3);

  std::cout << "5. 查找成功概率为10%, 不成功为90% ..." << std::endl;
  ShowResult(rand19_a1, rand19_b1, N1);
  ShowResult(rand19_a2, rand19_b2, N2);
  ShowResult(rand19_a3, rand19_b3, N3);
}
