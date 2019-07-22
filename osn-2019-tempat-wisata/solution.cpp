#include <bits/stdc++.h>
using namespace std;

const int N = 200005;

int n, m;
int a[N], b[N];

int main() {
  scanf("%d %d", &n, &m);
  
  vector<int> st(n), en(n);
  for (int i = 0; i < n; ++i) {
    scanf("%d %d", a + i, b + i);
    st[i] = a[i];
    en[i] = b[i];
  }
  
  sort(st.begin(), st.end(), greater<int>());
  sort(en.begin(), en.end());
  
  for (int i = 0; i < n; ++i) {
    int ans = n-1;
    ans -= lower_bound(en.begin(), en.end(), a[i]) - en.begin();
    ans -= lower_bound(st.begin(), st.end(), b[i], greater<int>()) - st.begin();
    
    printf("%d\n", ans);
  }
  return 0;
}
