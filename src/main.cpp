#include <fstream>
#include <iostream>

#include "my_robot_guard.h"
int main() {
  std::ifstream is("input.txt");
  if (!is.is_open()) {
    std::cout << "文件没开" << std::endl;
    exit(-1);
  }
  std::ofstream os("output.txt");

  int n, m;
  is >> n >> m;
  RobotGuard robot(n, m);

  os << robot.best_n_robot << std::endl;
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      os << robot.best_robots[i][j] << " ";
    }
    os << std::endl;
  }
  return 0;
}