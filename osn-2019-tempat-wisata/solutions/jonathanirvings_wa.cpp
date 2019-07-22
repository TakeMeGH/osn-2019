#include <bits/stdc++.h>
using namespace std;

int main() {
  int N, M;
  scanf("%d %d", &N, &M);

  vector<int> A(N), B(N);
  for (int i = 0; i < N; ++i) {
    scanf("%d %d", &A[i], &B[i]);
  }

  vector<int> starts = A;
  vector<int> ends = B;

  sort(starts.begin(), starts.end());
  sort(ends.begin(), ends.end());

  starts.erase(unique(starts.begin(), starts.end()), starts.end());
  ends.erase(unique(ends.begin(), ends.end()), ends.end());

  for (int i = 0; i < N; ++i) {
    int toLeft = lower_bound(ends.begin(), ends.end(), A[i]) - ends.begin();
    int toRight =
        starts.end() - upper_bound(starts.begin(), starts.end(), B[i]);
    printf("%d\n", N - 1 - toLeft - toRight);
  }
}
