#include <bits/stdc++.h>
using namespace std;

const int N = 200005;

int n, m;
int a[N], b[N];

int main() {
  scanf("%d %d", &n, &m);
  for (int i = 0; i < n; ++i) {
    scanf("%d %d", a + i, b + i);
    --a[i], --b[i];
  }

  vector<vector<int>> tourists(m, vector<int>());
  for (int i = 0; i < n; ++i) {
    for (int j = a[i]; j <= b[i]; ++j) {
      tourists[j].push_back(i);
    }
  }

  for (int i = 0; i < n; ++i) {
    vector<bool> met(n, false);
    
    for (int j = a[i]; j <= b[i]; ++j) {
      for (int tourist: tourists[j]) {
        met[tourist] = true;
      }
    }
    
    printf("%d\n", (int) count(met.begin(), met.end(), true) - 1);
  }

  return 0;
}
