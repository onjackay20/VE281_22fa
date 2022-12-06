#include<iostream>
#include<list>
#include<vector>
#include<climits>
// You are not allowed to include additional libraries, either in shortestP2P.hpp or shortestP2P.cc

#define INF INT_MAX
typedef unsigned int ui;

using namespace std;



class ShortestP2P {
  public:
      ShortestP2P() {}
      ~ShortestP2P() {
          for (ui i = 0; i < n; i++) delete [] dis[i];
          delete [] dis;
      }

      /* Read the graph from stdin
       * The input has the following format:
       *
       * Firstline: 1 unsigned int, the total number of verticies, X.
       * Secondline: 1 unsigned int, the total number of edges between vertices, Y.
       * A set of Y lines, each line contains tuple of 2 unsigned int and 1 int (not unsigned int!), in the format of: A(point 1, unsigned) B(point 2, unsigned) dist(distance, int)
       *
       * Example:
       * 4
       * 4
       * 0 1 5
       * 1 2 -1
       * 2 3 4
       * 3 1 6
       * 
       * 
       * 
       *
       * Vertices that are not connected have a infinitly large distance. You may use INF (previously defined at the top of this cope snippet) for infinitly large distance.
       * 
       * Special: when the graph is not proper, where there exist any pair of vertices whose minimum distance does not exist, terminate immediately by printing:
       * cout << "Invalid graph. Exiting." << endl;
       *
       * Note: vertex pairs that are not connected, which have infinitely large distances are not considered cases where "minimum distances do not exist".
       */
      void readGraph();

      /* Input: 2 vertices A and B
       * Output: distance between them.
       * cout << dist << endl;
       *
       * When the A and B are not connected print INF:
       * cout << "INF" << endl;
       */
      void distance(unsigned int A, unsigned int B);


  private:
    // internal data and functions.

      ui n;
    //   std::vector<std::vector<std::pair<ui, int> > > e;
    //   std::vector<std::vector<long long> > dis;
      long long **dis;
      bool valid;

      long long spfa(ui S, ui T);


};

void ShortestP2P::readGraph() {
    ui m;
    std::cin >> n >> m;
    // e.resize(n);
    dis = new long long*[n]();
    for (ui i = 0; i < n; i++) dis[i] = new long long[n]();
    // dis.resize(n);
    for (ui i = 0; i < n; i++) {
        // dis[i].resize(n);
        for (ui j = 0; j < n; j++) dis[i][j] = INF;
    }
    for (ui i = 0; i < m; i++) {
        ui u, v;
        int w;
        std::cin >> u >> v >> w;
        if (w < dis[u][v]) dis[u][v] = w;
    }
    if (spfa(0, 1) == -INF) {
        std::cout << "Invalid graph. Exiting." << std::endl;
        valid = 0;
        std::exit(0);
    }
    for (ui k = 0; k < n; k++) {
        for (ui i = 0; i < n; i++) {
            for (ui j = 0; j < n; j++) {
                if (dis[i][k] + dis[k][j] < dis[i][j]) {
                    dis[i][j] = dis[i][k] + dis[k][j];
                }
            }
        }
    }
    valid = 1;
}

void ShortestP2P::distance(ui A, ui B) {
    if (!valid) return;
    if (dis[A][B] == INF)
        std::cout << "INF" << std::endl;
    else
        std::cout << dis[A][B] << std::endl;
}

long long ShortestP2P::spfa(ui S, ui T) {
    auto dis_ = new long long[n]();
    auto flag = new bool[n]();
    auto cnt = new ui[n]();
    for (ui i = 0; i < n; i++) {
        dis_[i] = INF;
        flag[i] = 0;
        cnt[i] = 0;
    }
    dis_[S] = 0;
    flag[S] = 1;
    cnt[S] = 1;
    std::list<ui> l;
    l.push_back(S);
    while (!l.empty()) {
        auto u = l.front();
        l.pop_front();
        flag[u] = 0;
        for (ui v = 0; v < n; v++) {
            if (v == u) continue;
            if (dis_[u] + dis[u][v] < dis_[v]) {
                if (++cnt[v] >= n) return -INF;
                dis_[v] = dis_[u] + dis[u][v];
                if (!flag[v]) {
                    l.push_back(v);
                    flag[v] = 1;
                }
            }
        }
    }
    auto ans = dis_[T];
    delete [] dis_;
    delete [] flag;
    delete [] cnt;
    return ans;
}