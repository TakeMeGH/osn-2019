#include <bits/stdc++.h>
using namespace std;

int main() {
  int N, M, S;
  scanf("%d %d %d", &N, &M, &S);

  vector<vector<int>> enter(N), exit(N);

  vector<int> A(M), B(M), P(M);
  for (int i = 0; i < M; ++i) {
    scanf("%d %d %d", &A[i], &B[i], &P[i]);
    --A[i];
    --B[i];

    enter[B[i]].push_back(i);
    exit[A[i]].push_back(i);
  }

  set<pair<long long, int>> dp;
  vector<long long> dp_packet(M), dp_medicine(N);

  for (int i = N - 1; i >= 0; --i) {
    dp_medicine[i] = S + (i == N - 1 ? 0 : dp_medicine[i + 1]);

    for (int ix : enter[i]) {
      dp_packet[ix] = P[ix] + (i == N - 1 ? 0 : dp_medicine[i + 1]);
      dp.insert(make_pair(dp_packet[ix], ix));
    }

    if (dp.size() > 0) {
      dp_medicine[i] = min(dp_medicine[i], (dp.begin())->first);
    }

    for (int ix : exit[i]) {
      dp.erase(make_pair(dp_packet[ix], ix));
    }
  }

  printf("%lld\n", dp_medicine[0]);
}
