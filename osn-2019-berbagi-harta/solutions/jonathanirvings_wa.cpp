#include <bits/stdc++.h>
using namespace std;

int main() {
  int N, P, Q;
  scanf("%d %d %d", &N, &P, &Q);

  vector<int> H(N);
  vector<bool> insideA(N), insideB(N);
  for (int i = 0; i < N; ++i) {
    scanf("%d", &H[i]);
  }

  for (int i = 0; i < P; ++i) {
    int A;
    scanf("%d", &A);
    insideA[i] = true;
  }

  for (int i = 0; i < Q; ++i) {
    int B;
    scanf("%d", &B);
    insideB[i] = true;
  }

  vector<int> insideAB;
  long long answer = 0;

  for (int i = 0; i < N; ++i) {
    if (insideA[i]) {
      if (insideB[i]) {
        insideAB.push_back(H[i]);
      } else {
        answer += H[i];
      }
    }
  }

  sort(insideAB.rbegin(), insideAB.rend());
  for (int i = 0; i < insideAB.size(); i += 2) {
    answer += insideAB[i];
  }

  printf("%lld\n", answer);
}
