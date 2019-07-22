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

bool isIntersect(pair<int, int> range1, pair<int, int> range2) {
  function<bool(int, pair<int, int>)> pointInRange = [](int x, pair<int, int> range) {
    return range.first <= x && x <= range.second;
  };
  
  return pointInRange(range1.first, range2) || pointInRange(range1.second, range2) ||
      pointInRange(range2.first, range1) || pointInRange(range2.second, range1);
}

vector<vector<int>> intersect;
void PrepareSolver() {
  intersect = vector<vector<int>>(n);
  for (int user1 = 0; user1 < n; ++user1) {
    for (pair<int, int> online1: onlines[user1]) {
      for (int user2 = user1; user2 < n; ++user2) {
        bool hasIntersect = false;
        for (pair<int, int> online2: onlines[user2]) {
          if (isIntersect(online1, online2)) {
            hasIntersect = true;
            break;
          }
        }
        
        if (hasIntersect) {
          intersect[user1].push_back(user2);
          intersect[user2].push_back(user1);
        }
      }
    }
  }
}

int CountHoaxesWithInitialUser(int initialUser) {
  queue<int> bfsQueue;
  vector<bool> hasHoax(n, false);
  
  bfsQueue.push(initialUser);
  hasHoax[initialUser] = true;
  
  int hoaxCount = 0;
  
  while (!bfsQueue.empty()) {
    int user = bfsQueue.front();
    bfsQueue.pop();
    
    ++hoaxCount;
    
    for (int intersectingUser: intersect[user]) {
      if (hasHoax[intersectingUser]) continue;
      hasHoax[intersectingUser] = true;
      
      bfsQueue.push(intersectingUser);
    }
  }
  
  return hoaxCount;
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
