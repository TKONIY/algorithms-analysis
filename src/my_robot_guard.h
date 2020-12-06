#include <queue>

#include "my_utils.h"
class RobotGuard {
 private:
  struct HeapNode {
    HeapNode(int n, int m) {
      robots = Utils<int>::New2Darray(n + 2, m + 2);
      monitors = Utils<int>::New2Darray(n + 2, m + 2);
      //将地图四周的边框设置为已监视
      for (int i = 0; i <= n + 1; ++i)
        for (int j = 0; j <= m + 1; ++j) robots[i][j] = monitors[i][j] = 0;
      for (int i = 0; i <= m + 1; ++i) monitors[0][i] = monitors[n + 1][i] = 1;
      for (int i = 0; i <= n + 1; ++i) monitors[i][0] = monitors[i][m + 1] = 1;

      x = y = 1;                //初始化坐标为(1,1)
      n_robot = n_monitor = 0;  //机器人和监视个数为0
    }
    operator int() const { return n_robot; }
    int x, y;        // 扩展结点坐标
    int n_robot;     // 该活结点的状态中一共有多少个机器人
    int n_monitor;   // 该活结点中一共有多少个坐标被监视
    int** robots;    // 地图, 是否放置机器人
    int** monitors;  // 地图, 是否被监视
  };

  int dx[6] = {0, -1, 0, 1, 0, 0};
  int dy[6] = {0, 0, 1, 0, -1, 0};

  int n, m;

  typedef std::priority_queue<HeapNode, std::vector<HeapNode>,
                              std::greater<HeapNode>>
      MinHeap;  //最小堆类型

  void AddLiveNode(MinHeap* H, HeapNode E, int x, int y) {
    HeapNode N(n, m);

    //复制结点信息
    N.x = E.x;
    N.y = E.y;
    N.n_robot = E.n_robot + 1;  //多放一个robot
    N.n_monitor = E.n_monitor;  //待会再统计被监视的节点数

    //复制
    for (int i = 0; i <= n + 1; ++i) {
      for (int j = 0; j <= m + 1; ++j) {
        N.robots[i][j] = E.robots[i][j];
        N.monitors[i][j] = E.monitors[i][j];
      }
    }
    N.robots[x][y] = 1;  //放一个robot
    //各个方向上添加monitor
    for (int i = 1; i <= 5; ++i) {
      int mx = x + dx[i], my = y + dy[i];
      N.monitors[mx][my]++;

      if (N.monitors[mx][my] == 1) {
        N.n_monitor++;  //新的点被监视了
      }
    }

    // 寻找下一个没有被监视的点并加入堆中
    while (!(N.monitors[N.x][N.y] == 0 || N.x > n)) {
      N.y++;
      if (N.y > m) {  //新行
        N.x++;
        N.y = 1;
      }
    }

    H->push(N);
  }

  void Save(int** robots) {  //保存最优解
    for (int i = 0; i <= n; ++i)
      for (int j = 0; j <= m; ++j) best_robots[i][j] = robots[i][j];
  }

 public:
  int best_n_robot;
  int** best_robots;  //最优解

  RobotGuard(int n_, int m_)
      : n(n_), m(m_), best_robots(Utils<int>::New2Darray(n + 2, m + 2)) {
    MinHeap minHeap;   //最小堆
    HeapNode E(n, m);  // E是一个没有机器人没有被监视的点,
                       // 它有三个儿子节点可以扩展(自己, 下, 右)
    while (true) {
      int x = E.x, y = E.y, n_robot = E.n_robot, n_monitor = E.n_monitor;
      if (n_monitor == n * m) {  //叶结点
        best_n_robot = n_robot;  //优先队列法第一个叶子节点就是最优解
        Save(E.robots);          //保存最优解, 退出
        break;
      }
      if (x < n) AddLiveNode(&minHeap, E, x + 1, y);  //(在下方结点设置机器人)
      if (y < m && (E.monitors[x][y + 1] == 0 || E.monitors[x][y + 2] == 0))
        AddLiveNode(&minHeap, E, x, y + 1);  //加上了剪枝条件(在右边设置机器人)
      if ((E.monitors[x + 1][y] == 0) && E.monitors[x][y + 1] == 0)
        AddLiveNode(&minHeap, E, x, y);  //加上了剪枝条件(在本点设置机器人)
      if (minHeap.empty()) break;
      E = minHeap.top();
      minHeap.pop();  //下一个结点
    }
  }
  ~RobotGuard() = default;
};
