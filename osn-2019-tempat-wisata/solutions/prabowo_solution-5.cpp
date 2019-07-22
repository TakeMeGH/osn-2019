#include <bits/stdc++.h>
using namespace std;

const int N = 200005;

int n, m;
int a[N], b[N];

int main() {
  scanf("%d %d", &n, &m);

  vector<int> pre(m+2, 0), suf(m+2, 0);
  for (int i = 0; i < n; ++i) {
    scanf("%d %d", a + i, b + i);

    pre[b[i]] += 1;
    suf[a[i]] += 1;
  }

  for (int i = 1; i <= m; ++i) pre[i] += pre[i-1], suf[m-i+1] += suf[m-i+2];

  for (int i = 0; i < n; ++i) {
    printf("%d\n", n - pre[a[i]-1] - suf[b[i]+1] - 1);
  }

  return 0;
}
