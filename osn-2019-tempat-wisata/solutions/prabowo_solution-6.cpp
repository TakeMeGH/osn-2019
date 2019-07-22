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

  vector<int> starts; int endidx = -1;
  for (const pair<int, int> &p: ends) {
    int idx = abs(p.second) - 1;
    
    if (p.second < 0) {
      starts.push_back(p.first);
      
      if (endidx >= 0 && a[endidx] < p.first && b[endidx] >= p.first) {
        ++ans[idx];
      }

      if (endidx == -1 || b[idx] > b[endidx]) endidx = idx;
    } else {
      ans[idx] += (int) starts.size() - 1 -
          (lower_bound(starts.begin(), starts.end(), a[idx]) - starts.begin());
    }
  }

  for (int i = 0; i < n; ++i) {
    printf("%d\n", ans[i]);
  }

  return 0;
}
