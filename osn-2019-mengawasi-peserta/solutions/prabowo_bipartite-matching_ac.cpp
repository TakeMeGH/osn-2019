#include <bits/stdc++.h>
using namespace std;

namespace BipartiteMatching {

const int MAXN1 = 1000000;
const int MAXN2 = 1000000;
const int MAXM = 4000000;

int n1, n2, edges, last[MAXN1], prv[MAXM], head[MAXM];
int matching[MAXN2], dist[MAXN1], Q[MAXN1];
bool used[MAXN1], vis[MAXN1];

// https://sites.google.com/site/indy256/algo_cpp/hopcroft_karp
void init(int _n1, int _n2) {
  n1 = _n1;
  n2 = _n2;
  edges = 0;
  fill(last, last + n1, -1);
}

void addEdge(int u, int v) {
  head[edges] = v;
  prv[edges] = last[u];
  last[u] = edges++;
}

void bfs() {
  fill(dist, dist + n1, -1);
  int sizeQ = 0;
  for (int u = 0; u < n1; ++u) {
    if (!used[u]) {
      Q[sizeQ++] = u;
      dist[u] = 0;
    }
  }
  for (int i = 0; i < sizeQ; i++) {
    int u1 = Q[i];
    for (int e = last[u1]; e >= 0; e = prv[e]) {
      int u2 = matching[head[e]];
      if (u2 >= 0 && dist[u2] < 0) {
        dist[u2] = dist[u1] + 1;
        Q[sizeQ++] = u2;
      }
    }
  }
}

bool dfs(int u1) {
  vis[u1] = true;
  for (int e = last[u1]; e >= 0; e = prv[e]) {
    int v = head[e];
    int u2 = matching[v];
    if (u2 < 0 || !vis[u2] && dist[u2] == dist[u1] + 1 && dfs(u2)) {
      matching[v] = u1;
      used[u1] = true;
      return true;
    }
  }
  return false;
}

int maxMatching() {
  fill(used, used + n1, false);
  fill(matching, matching + n2, -1);
  for (int res = 0;;) {
    bfs();
    fill(vis, vis + n1, false);
    int f = 0;
    for (int u = 0; u < n1; ++u)
      if (!used[u] && dfs(u))
        ++f;
    if (!f)
      return res;
    res += f;
  }
}

}

const int N = 1005;

int R, C;
char S[N][N];

int lftSz, rgtSz;
int nodeLft[N][N], nodeRgt[N][N];
pair<int, int> cellLft[N*N], cellRgt[N*N];

int main() {
  scanf("%d %d", &R, &C);
  
  lftSz = rgtSz = 0;
  for (int i = 0; i < R; ++i) {
    scanf("%s", S[i]);
    for (int j = 0; j < C; ++j) {
      if (S[i][j] == '.') {
        nodeLft[i][j] = lftSz;
        cellLft[lftSz] = {i, j};
        ++lftSz;
      } else if (S[i][j] == 'x') {
        nodeRgt[i][j] = rgtSz;
        cellRgt[rgtSz] = {i, j};
        ++rgtSz;
      }
    }
  }
  
  BipartiteMatching::init(lftSz, rgtSz);
  
  int dx[4] = {0, -1, 0, 1}, dy[4] = {1, 0, -1, 0};
  char arrow[4] = {'>', '^', '<', 'v'};
  for (int i = 0; i < R; ++i) {
    for (int j = 0; j < C; ++j) {
      if (S[i][j] == 'x') {
        for (int k = 0; k < 4; ++k) {
          int ni = i + dx[k], nj = j + dy[k];
          if (ni < 0 || ni >= R || nj < 0 || nj >= C) continue;
          
          if (S[ni][nj] == '.') {
            BipartiteMatching::addEdge(nodeLft[ni][nj], nodeRgt[i][j]);          
          }
        }
      }
    }
  }
  
  BipartiteMatching::maxMatching();
  
  for (int i = 0; i < R; ++i) {
    for (int j = 0; j < C; ++j) {
      if (S[i][j] == 'x') {
        int x, y;
        tie(x, y) = cellLft[BipartiteMatching::matching[nodeRgt[i][j]]];
        
        for (int k = 0; k < 4; ++k) {
          if (make_pair(x + dx[k], y + dy[k]) == make_pair(i, j)) {
            S[x][y] = arrow[k];
          }
        }
      }
    }  
  }
  
  for (int i = 0; i < R; ++i) printf("%s\n", S[i]);
  return 0;
}
