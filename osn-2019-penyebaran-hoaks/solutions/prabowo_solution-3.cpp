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

vector<vector<int>> usersOnlineAtHour;
void PrepareSolver() {
  int totalHours = s * n;
  usersOnlineAtHour.clear();
  usersOnlineAtHour.resize(totalHours);
  
  for (int user = 0; user < n; ++user) {
    for (pair<int, int> online: onlines[user]) {
      for (int day = 0; day < n; ++day) {
        for (int hour = online.first; hour <= online.second; ++hour) {
          usersOnlineAtHour[day*s + hour].push_back(user);
        }
      }
    }
  }
}

int CountHoaxesWithInitialUser(int initialUser) {
  vector<bool> userHasHoax(n, false);
  userHasHoax[initialUser] = true;
  
  int totalHours = s * n;
  for (int hour; hour < totalHours; ++hour) {
    bool someoneHasHoaxAtThisHour = false;
    for (int user: usersOnlineAtHour[hour]) {
      if (userHasHoax[user]) {
        someoneHasHoaxAtThisHour = true;
        break;
      }
    }
    
    if (someoneHasHoaxAtThisHour) {
      // Spread hoaxes to everyone
      for (int user: usersOnlineAtHour[hour]) {
        userHasHoax[user] = true;
      }
    }
  }
  
  return count(userHasHoax.begin(), userHasHoax.end(), true);
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
