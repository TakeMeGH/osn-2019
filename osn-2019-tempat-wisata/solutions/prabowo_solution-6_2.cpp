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

  vector<int> intersecting;
  for (const pair<int, int> &p: ends) {
    int idx = abs(p.second) - 1;
    if (p.second < 0) {
      for (int i: intersecting) ans[i] += 1;
      ans[idx] += intersecting.size();
      intersecting.push_back(idx);
    } else {
      for (int i = 0; i < intersecting.size(); ++i) {
        if (intersecting[i] == idx) {
          intersecting.erase(intersecting.begin() + i);
          break;
        }
      }
    }
  }

  for (int i = 0; i < n; ++i) {
    printf("%d\n", ans[i]);
  }

  return 0;
}
