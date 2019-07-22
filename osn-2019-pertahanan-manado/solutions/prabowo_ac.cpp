#include <bits/stdc++.h>
using namespace std;

int main() {
  int N, M, S;
  scanf("%d %d %d", &N, &M, &S);

  vector<int> A(M), B(M), P(M);
  for (int i = 0; i < M; ++i) {
    scanf("%d %d %d", &A[i], &B[i], &P[i]);
  }

  vector<vector<int>> ends(N), starts(N);
  for (int i = 0; i < M; ++i) {
    ends[B[i] - 1].push_back(i);
    starts[A[i] - 1].push_back(i);
  }

  vector<long long> DP(N+1, 0LL);

  function<long long(int)> getMedicine = [&](int u) {
    return P[u] + DP[B[u]];
  };

  auto compareGreaterMedicine = [&](int u, int v) {
    return getMedicine(u) > getMedicine(v);
  };

  priority_queue<int, vector<int>, decltype(compareGreaterMedicine)>
    pq(compareGreaterMedicine);

  vector<bool> erased(M, false);

  for (int i = N-1; i >= 0; --i) {
    DP[i] = DP[i+1] + S;

    for (int en: ends[i]) pq.push(en);
    if (!pq.empty()) DP[i] = min(DP[i], getMedicine(pq.top()));

    for (int st: starts[i]) erased[st] = true;
    while (!pq.empty() && erased[pq.top()]) pq.pop();
  }
  
  printf("%lld\n", DP[0]);
  return 0;
}
