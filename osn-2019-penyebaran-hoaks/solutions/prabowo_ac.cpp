#include <bits/stdc++.h>
using namespace std;

int n, s, q;
vector<vector<pair<int, int>>> onlines;
vector<int> queries;

void ReadInputFromStdin() {
  scanf("%d %d %d", &n, &s, &q);
  
  onlines.clear();
  onlines.resize(n);
  
  for (int i = 0; i < n; ++i) {
    int o;
    scanf("%d", &o);
    
    for (int j = 0; j < o; ++j) {
      int a, b;
      scanf("%d %d", &a, &b);
      --a, --b;
      
      onlines[i].emplace_back(a, b);
    }
  }
  
  queries.resize(q);
  
  for (int i = 0; i < q; ++i) {
    scanf("%d", &queries[i]);
    --queries[i];
  }
}

namespace DSU {
  vector<int> par;
  vector<int> size;
  
  void init(int n) {
    par = size = vector<int>(n);
    
    for (int i = 0; i < n; ++i) {
      par[i] = i;
      size[i] = 1;
    }
  }
  
  int getRoot(int u) {
    if (u != par[u]) return par[u] = getRoot(par[u]);
    return u;
  }
  
  void merge(int u, int v) {
    if (getRoot(u) == getRoot(v)) return;
    size[getRoot(v)] += size[getRoot(u)];
    par[getRoot(u)] = getRoot(v);
  }
  
  int getSize(int u) {
    return size[getRoot(u)];
  }
};

void PrepareSolver() {  
  vector<pair<int, int>> timelineOfEvent;
  for (int user = 0; user < n; ++user) {
    for (pair<int, int> online: onlines[user]) {
      timelineOfEvent.emplace_back(online.first, -user - 1);
      timelineOfEvent.emplace_back(online.second, user + 1);
    }
  }
  
  sort(timelineOfEvent.begin(), timelineOfEvent.end());
  
  DSU::init(n);

  int onlineUserCount = 0;
  vector<int> connectedUsers;

  for (pair<int, int> event: timelineOfEvent) {
    int user = abs(event.second) - 1;

    // user become online
    if (event.second < 0) {
      ++onlineUserCount;
      connectedUsers.push_back(user);
    }

    // user become offline
    if (event.second > 0) {
      --onlineUserCount;

      if (onlineUserCount == 0) {
        for (int i = 1; i < connectedUsers.size(); ++i) {
          DSU::merge(connectedUsers[0], connectedUsers[i]);
        }
        connectedUsers.clear();
      }
    }
  }
}

int CountHoaxesWithInitialUser(int initialUser) {
  return DSU::getSize(initialUser);
}

vector<int> ans;
void Solve() {
  PrepareSolver();
  
  ans.resize(q);
  for (int i = 0; i < q; ++i) {
    ans[i] = CountHoaxesWithInitialUser(queries[i]);
  }
}

void PrintOutputToStdout() {
  for (int line: ans) {
    printf("%d\n", line);
  }
}

int main() {
  ReadInputFromStdin();
  Solve();
  PrintOutputToStdout();
  return 0;
}
