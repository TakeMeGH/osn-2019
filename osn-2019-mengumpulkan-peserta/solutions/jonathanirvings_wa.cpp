#include <bits/stdc++.h>
using namespace std;

int main() {
  int R, C;
  scanf("%d %d", &R, &C);
  vector<string> S(R, string(C, 0));

  for (int i = 0; i < R; ++i) {
    scanf("\n");
    for (int j = 0; j < C; ++j) {
      scanf("%c", &S[i][j]);
    }
  }

  --C;
  int contestantsCount = 0;
  for (int i = 0; i < R; ++i) {
    for (int j = 0; j < C; ++j) {
      contestantsCount += S[i][j] - '0';
    }
  }

  int answer = INT_MAX;

  for (int i1 = 0; i1 < R; ++i1) {
    vector<int> rowAggregate(C, 0);
    for (int i2 = i1; i2 < R; ++i2) {
      for (int j = 0; j < C; ++j) {
        rowAggregate[j] += S[i2][j] - '0';
      }
      for (int j1 = 0; j1 < C; ++j1) {
        int currentTotalContestants = 0;
        for (int j2 = j1; j2 < C; ++j2) {
          currentTotalContestants += rowAggregate[j2];
          if ((i2 - i1 + 1) * (j2 - j1 + 1) == contestantsCount) {
            answer = min(answer, contestantsCount - currentTotalContestants);
          }
        }
      }
    }
  }
  printf("%d\n", answer == INT_MAX ? -1 : answer);
}
