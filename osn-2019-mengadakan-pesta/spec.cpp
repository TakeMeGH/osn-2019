#include <tcframe/spec.hpp>
using namespace tcframe;

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 50;

class ProblemSpec : public BaseProblemSpec {
 protected:
  int N, M, Q;
  vector<vector<char>> G;

  int Z;
  vector<int> ANS;

  void InputFormat() {
    LINE(N, M, Q);
    GRID(G) % SIZE(N+M, N+M);
  }

  void StyleConfig() {
    InteractiveEvaluator();
  }

  void Constraints() {
    CONS(1 <= N && N <= MAXN);
    CONS(1 <= M && M <= MAXN);
    CONS(N != M);
    CONS(Q == 7);
    CONS(bipartiteGraph(N, M, G));
  }

  void Subtask1() {
    CONS(N == 1);
  }

  void Subtask2() {
    CONS(N <= 4);
    CONS(M <= 4);
  }

  void Subtask3() {
    CONS(N <= 8);
    CONS(M <= 8);
  }

  void Subtask4() {
  }

 private:
  bool bipartiteGraph(int N, int M, const vector<vector<char>> &G) {
    for (int i = 0; i < N; ++i) for (int j = i; j < N; ++j) {
      if (G[i][j] != '0') return false;
    }
    for (int i = N; i < N+M; ++i) for (int j = i; j < N+M; ++j) {
      if (G[i][j] != '0') return false;
    }
    
    for (int i = 0; i < N+M; ++i) for (int j = i+1; j < N+M; ++j) {
      if (G[i][j] != '0' && G[i][j] != '1') return false;
      if (G[i][j] != G[j][i]) return false;
    }

    return true;
  }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
 protected:
  vector<int> adj[MAXN];
 
  void SampleTestCase1() {
    Subtasks({3, 4});
    Input({
      "3 5 7",
      "00010000",
      "00001101",
      "00000100",
      "10000000",
      "01000000",
      "01100000",
      "00000000",
      "01000000",
    });
  }
  
  void BeforeTestCase() {
    for (int i = 0; i < MAXN; ++i) adj[i].clear();
  }

  void AfterTestCase() {
    G = vector<vector<char>>(N+M, vector<char>(N+M, '0'));
    for (int u = 0; u < N; ++u) {
      for (int v: adj[u]) {
        G[u][v+N] = G[v+N][u] = '1';
      }
    }
  }

  // N = 1, M <= 4
  void TestGroup1() {
    Subtasks({1, 2, 3, 4});
    
    for (int m = 2; m <= 4; ++m) {
      for (int mask = 0; mask < 1 << m; ++mask) {
        vector<int> v;
        for (int i = 0; i < m; ++i) {
          if (mask >> i & 1) v.push_back(i);
        }
        CASE(N = 1; M = m; adj[0] = v);
      }
    }
  }
  
  // N = 1, M <= 8
  void TestGroup2() {
    Subtasks({1, 3, 4});

    CASE(N = 1; M = 8; randomBipartiteGraph(N, M));
    CASE(N = 1; M = 8; completeBipartiteGraph(N, M));
    CASE(N = 1; M = 8; oneDegreedBipartiteGraph(N, M));
    CASE(N = 1; M = 8; adj[0] = iotaExceptX(M, 0));
    CASE(N = 1; M = 8; adj[0] = iotaExceptX(M, 0));
    CASE(N = 1; M = 8; adj[0] = iotaExceptX(M, M/2));
  }
  
  // N = 1, M <= 50
  void TestGroup3() {
    Subtasks({1, 4});

    CASE(N = 1; M = 50; randomBipartiteGraph(N, M));
    CASE(N = 1; M = 50; completeBipartiteGraph(N, M));
    CASE(N = 1; M = 50; oneDegreedBipartiteGraph(N, M));
    CASE(N = 1; M = 50; adj[0] = iotaExceptX(M, 0));
    CASE(N = 1; M = 50; adj[0] = iotaExceptX(M, 0));
    CASE(N = 1; M = 50; adj[0] = iotaExceptX(M, M/2));
  }

  // N <= 4, M <= 4
  void TestGroup4() {
    Subtasks({2, 3, 4});

    generateCommonCases(4);
  }

  // N <= 8, M <= 8
  void TestGroup5() {
    Subtasks({3, 4});

    generateCommonCases(8);
  }

  // N <= 50, M <= 50
  void TestGroup6() {
    Subtasks({4});
    
    CASE(N = 40; M = 50; randomBipartiteGraph(N, M));
    CASE(N = 50; M = 40; randomBipartiteGraph(N, M));
    CASE(N = 40; M = 50; oneDegreedBipartiteGraph(N, M));
    CASE(N = 50; M = 40; oneDegreedBipartiteGraph(N, M));
    CASE(N = 40; M = 50; oneDegreedBipartiteGraph2(N, M));
    CASE(N = 50; M = 40; oneDegreedBipartiteGraph2(N, M));
    CASE(N = 40; M = 50);
    CASE(N = 50; M = 40);

    CASE(N = 49; M = 50; oneDegreedBipartiteGraph(N, M));
    CASE(N = 50; M = 49; oneDegreedBipartiteGraph(N, M));
    CASE(N = 49; M = 50; oneDegreedBipartiteGraph2(N, M));
    CASE(N = 50; M = 49; oneDegreedBipartiteGraph2(N, M));

    CASE(N = 49; M = 50; oneDegreedBipartiteGraph(N, M));
    CASE(N = 50; M = 49; oneDegreedBipartiteGraph(N, M));
    CASE(N = 49; M = 50; oneDegreedBipartiteGraph2(N, M));
    CASE(N = 50; M = 49; oneDegreedBipartiteGraph2(N, M));

    CASE(N = 49; M = 50; oneDegreedBipartiteGraph(N, M));
    CASE(N = 50; M = 49; oneDegreedBipartiteGraph(N, M));
    CASE(N = 49; M = 50; oneDegreedBipartiteGraph2(N, M));
    CASE(N = 50; M = 49; oneDegreedBipartiteGraph2(N, M));

    CASE(N = 49; M = 50; oneDegreedBipartiteGraph(N, M));
    CASE(N = 50; M = 49; oneDegreedBipartiteGraph(N, M));
    CASE(N = 49; M = 50; oneDegreedBipartiteGraph2(N, M));
    CASE(N = 50; M = 49; oneDegreedBipartiteGraph2(N, M));

    generateCommonCases(50);
  }

 private:
  void generateCommonCases(int n) {
    CASE(N = n-1; M = n; randomBipartiteGraph(N, M));
    CASE(N = n; M = n-1; randomBipartiteGraph(N, M));
    CASE(N = n-1; M = n; completeBipartiteGraph(N, M));
    CASE(N = n; M = n-1; completeBipartiteGraph(N, M));
    CASE(N = n-1; M = n; oneDegreedBipartiteGraph(N, M));
    CASE(N = n; M = n-1; oneDegreedBipartiteGraph(N, M));
    CASE(N = n-1; M = n; oneDegreedBipartiteGraph2(N, M));
    CASE(N = n; M = n-1; oneDegreedBipartiteGraph2(N, M));
    CASE(N = n-1; M = n; randomOneDegreedBipartiteGraph(N, M));
    CASE(N = n; M = n-1; randomOneDegreedBipartiteGraph(N, M));
    CASE(N = n-1; M = n; randomOneDegreedBipartiteGraph(N, M, true));
    CASE(N = n; M = n-1; randomOneDegreedBipartiteGraph(N, M, true));
    CASE(N = n-1; M = n);
    CASE(N = n; M = n-1);
  }
 
  void randomBipartiteGraph(int N, int M) {
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < M; ++j) {
        if (rnd.nextInt(2)) adj[i].push_back(j);
      }
    }
  }
  
  void completeBipartiteGraph(int N, int M) {
    for (int i = 0; i < N; ++i) {
      adj[i] = vector<int>(M);
      iota(adj[i].begin(), adj[i].end(), 0);
    }
  }
  
  void oneDegreedBipartiteGraph(int N, int M) {
    vector<int> nodes(max(N, M));
    iota(nodes.begin(), nodes.end(), 0);
    rnd.shuffle(nodes.begin(), nodes.end());

    if (N < M) {
      for (int i = 0; i < N; ++i) {
        adj[i].push_back(nodes[i]);      
      }
    } else {
      for (int i = 0; i < M; ++i) {
        adj[nodes[i]].push_back(i);
      }
    }
  }
  
  void oneDegreedBipartiteGraph2(int N, int M) {
    vector<int> nodes(max(N, M));
    iota(nodes.begin(), nodes.end(), 0);
    rnd.shuffle(nodes.begin(), nodes.end());

    if (N < M) {
      for (int i = 0; i < N; ++i) {
        adj[i].push_back(nodes[i]);      
      }
      
      for (int i = N; i < M; ++i) {
        adj[rnd.nextInt(N)].push_back(nodes[i]);
      }
    } else {
      for (int i = 0; i < M; ++i) {
        adj[nodes[i]].push_back(i);
      }
      
      for (int i = M; i < N; ++i) {
        adj[nodes[i]].push_back(rnd.nextInt(M));
      }
    }
  }
  
  void randomOneDegreedBipartiteGraph(int N, int M, bool right=false) {
    if (right) {
      for (int i = 0; i < N; ++i) {
        adj[i].push_back(rnd.nextInt(M));
      }
    } else {
      for (int i = 0; i < M; ++i) {
        adj[rnd.nextInt(N)].push_back(i);
      }
    }
  }
  
  vector<int> iotaExceptX(int N, int X) {
    vector<int> ret;
    ret = vector<int>(N-1);
    iota(ret.begin(), ret.begin() + X, 0);
    iota(ret.begin() + X, ret.end(), X+1);
    return ret;
  }
};
