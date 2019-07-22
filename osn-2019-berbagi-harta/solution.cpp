#include <bits/stdc++.h>
using namespace std;

const int N = 200005;

int n, p, q;
int h[N], a[N], b[N];

int main() {
  scanf("%d %d %d", &n, &p, &q);
  for (int i = 0; i < n; ++i) scanf("%d", h + i);
  for (int i = 0; i < p; ++i) scanf("%d", a + i), --a[i];
  for (int i = 0; i < q; ++i) scanf("%d", b + i), --b[i];
  
  vector<int> intersects;
  
  long long ans = 0;
  for (int i = 0, j = 0; i < p; ++i) {
    while (j < q && b[j] < a[i]) ++j;
    if (j < q && b[j] == a[i]) {
      intersects.push_back(h[a[i]]);
    } else ans += h[a[i]];
  }
  
  sort(intersects.begin(), intersects.end(), greater<int>());
  
  for (int i = 0; i < intersects.size(); i += 2) {
    ans += intersects[i];
  }
  
  printf("%lld\n", ans);
  return 0;
}
