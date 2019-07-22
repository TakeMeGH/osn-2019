#include <bits/stdc++.h>
using namespace std;

const int N = 1005;
const int NN = N * N * 2;
const int INF = 1000000000;

int r, c;
char m[NN];
char p[N][N];

bool isRoute[N][N];

struct Dinic {
  int s, t;
  vector<int> edges[NN], cap[NN], rev[NN];
  int dist[NN], it[NN];
  
  void addEdge(int u, int v, int c=INF) {
    if (u == v) return;
    
    rev[u].push_back(edges[v].size());
    cap[u].push_back(c);
    edges[u].push_back(v);
    
    rev[v].push_back((int) edges[u].size() - 1);
    cap[v].push_back(0);
    edges[v].push_back(u);
  }
  
  bool bfs() {
    queue<int> q;
    q.push(s);
    
    for (int i=0; i<=t; i++) dist[i] = -1;
    dist[s] = 0;
    
    while (q.size()) {
      int u = q.front();
      q.pop();
      
      for (int i=0; i<edges[u].size(); i++) {
        int v = edges[u][i];
        int c = cap[u][i];
        if (dist[v] >= 0 || c == 0) continue;
        dist[v] = dist[u] + 1;
        q.push(v);
      }
    }
    
    return dist[t] >= 0;
  }
  
  int dfs(int u, int f) {
    if (u == t) return f;
    for (; it[u]<edges[u].size(); ++it[u]) {
      int i = it[u];
      int v = edges[u][i];
      int c = cap[u][i];
      if (dist[v] == dist[u] + 1 && c > 0) {
        int flow = dfs(v, min(f, c));
        if (flow > 0) {
          cap[u][i] -= flow;
          cap[v][rev[u][i]] += flow;
          return flow;
        }
      }
    }
    
    return 0;
  }
  
  int maxflow() {
    int ret = 0;
    while (bfs()) {
      for (int i=0; i<=t; i++) it[i] = 0;
      while (int flow = dfs(s, INF)) {
        ret += flow;
      }
    }
    
    return ret;
  }
} dinic;

int getOutNode(int x, int y) {
  return x*c + y + 1;
}

int getInNode(int x, int y) {
  return r*c + x*c + y + 1;
}

void read() {
  scanf("%d %d", &r, &c);
  scanf("%s", m);
  for (int i = 0; i < r; ++i) {
    scanf("%s", p[i]);
  }
}

void initialize() {
  int x = 0, y = 0;
  isRoute[x][y] = true;
  
  for (int i = 0; i < r+c-2; ++i) {
    if (m[i] == '>') y += 1;
    else x += 1;
    
    isRoute[x][y] = true;
  }
}

void constructGraph() {
  dinic.s = 0;
  dinic.t = r*c*2 + 1;
  
  for (int i = 0; i < r; ++i) {
    for (int j = 0; j < c; ++j) {
      if (p[i][j] == '#') continue;
      
      if (i+1 < r && p[i+1][j] != '#') {
        if (!isRoute[i][j] || !isRoute[i+1][j]) {
          dinic.addEdge(getOutNode(i, j), getInNode(i+1, j));
        }
      }
      
      if (j+1 < c && p[i][j+1] != '#') {
        if (!isRoute[i][j] || !isRoute[i][j+1]) {
          dinic.addEdge(getOutNode(i, j), getInNode(i, j+1));
        }
      }
      
      if (isRoute[i][j]) {
        dinic.addEdge(dinic.s, getOutNode(i, j));
        dinic.addEdge(getInNode(i, j), dinic.t);
      } else {
        dinic.addEdge(getInNode(i, j), getOutNode(i, j), 1);
      }
    }
  }
}

void output() {
  for (int i = 0; i < r; ++i) {
    for (int j = 0; j < c; ++j) {
      if (p[i][j] == '#') {
        printf("#");
        continue;
      }
      
      if (isRoute[i][j]) {
        printf(".");
        continue;
      }
      
      if (dinic.dist[getInNode(i, j)] >= 0 &&
          dinic.dist[getOutNode(i, j)] < 0) {
        printf("x");
      } else {
        printf(".");
      }
    }
    
    printf("\n");
  }
}

int main() {
  read();
  initialize();
  constructGraph();
  
  int ans = dinic.maxflow();
  
  output();
  return 0;
}

