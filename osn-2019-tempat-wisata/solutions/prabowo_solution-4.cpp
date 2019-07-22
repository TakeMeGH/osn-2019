#include <bits/stdc++.h>
using namespace std;

const int N = 200005;

int n, m;
int a[N], b[N];

int main() {
  scanf("%d %d", &n, &m);
  for (int i = 0; i < n; ++i) {
    scanf("%d %d", a + i, b + i);
  }

  auto inrange = [](int x, int l, int r) {
    return l <= x && x <= r;
  };

  for (int i = 0; i < n; ++i) {
    int cnt = 0;
    for (int j = 0; j < n; ++j) {
      if (inrange(a[j], a[i], b[i]) || inrange(b[j], a[i], b[i]) ||
          inrange(a[i], a[j], b[j]) || inrange(b[i], a[j], b[j])) {
        ++cnt;     
      }
    }
    printf("%d\n", cnt-1);
  }

  return 0;
}
