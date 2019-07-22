#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> adj;
vector<int> inside;
vector<int> answer;

const int UNVISITED = 0;
const int VISITED = 1;

void dfs(int u) {
  if (answer[u] == VISITED) {
    return;
  }
  answer[u] = VISITED;
  inside.push_back(u);
  for (int v : adj[u]) {
    dfs(v);
  }
}

int main() {
  int N, S, Q;
  scanf("%d %d %d", &N, &S, &Q);
  adj.resize(N);
  answer.resize(N, UNVISITED);

  vector<int> hours;
  unordered_map<int, vector<int>> in, out;

  for (int i = 0; i < N; ++i) {
    int O;
    scanf("%d", &O);
    for (int j = 0; j < O; ++j) {
      int A, B;
      scanf("%d %d", &A, &B);
      hours.push_back(A);
      hours.push_back(B);
      in[A].push_back(i);
      out[B].push_back(i);
    }
  }

  sort(hours.begin(), hours.end());
  hours.erase(unique(hours.begin(), hours.end()), hours.end());

  vector<bool> isOnline(N, false);
  stack<int> onlineUsers;

  for (int h : hours) {
    for (int user : in[h]) {
      while (!onlineUsers.empty()) {
        if (!isOnline[onlineUsers.top()]) {
          onlineUsers.pop();
        } else {
          break;
        }
      }
      if (!onlineUsers.empty()) {
        adj[onlineUsers.top()].push_back(user);
        adj[user].push_back(onlineUsers.top());
      }
      isOnline[user] = true;
      onlineUsers.push(user);
    }
    for (int user : out[h]) {
      isOnline[user] = false;
    }
  }

  for (int i = 0; i < N; ++i) {
    if (answer[i] == UNVISITED) {
      inside.clear();
      dfs(i);
      for (int user : inside) {
        answer[user] = inside.size();
      }
    }
  }

  for (int i = 0; i < Q; ++i) {
    int P;
    scanf("%d", &P);
    printf("%d\n", answer[P - 1]);
  }
}
