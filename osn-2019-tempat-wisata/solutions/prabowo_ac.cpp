#include <bits/stdc++.h>
using namespace std;

const int N = 200005;

int n, m;
int a[N], b[N];

int ans[N];

int main() {
  scanf("%d %d", &n, &m);
  
  vector<pair<int, int>> ends(n*2);
  for (int i = 0; i < n; ++i) {
    scanf("%d %d", a + i, b + i);
    
    ends[i*2 + 0] = {a[i], -i-1};
    ends[i*2 + 1] = {b[i], +i+1};
  }
  
  sort(ends.begin(), ends.end());

  int touristCount = 0;
  vector<int> startTime(n, -1);
  int t = 0;

  for (const pair<int, int> &p: ends) {
    int idx = abs(p.second) - 1;
    if (p.second < 0) {
      ans[idx] += touristCount++;
      startTime[idx] = ++t;
    } else {
      ans[idx] += t - startTime[idx];
      --touristCount;
    }
  }

  for (int i = 0; i < n; ++i) {
    printf("%d\n", ans[i]);
  }
  return 0;
}
