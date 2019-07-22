#include <bits/stdc++.h>
using namespace std;

int main() {
  int R, C;
  scanf("%d %d", &R, &C);
  vector<string> S(R, string(C, 0));

  int contestantsCount = 0;

  for (int i = 0; i < R; ++i) {
    scanf("\n");
    for (int j = 0; j < C; ++j) {
      scanf("%c", &S[i][j]);
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
      if (contestantsCount % (i2 - i1 + 1) == 0) {
        int columnLength = contestantsCount / (i2 - i1 + 1);
        if (columnLength <= C) {
          int currentTotalContestants = 0;
          for (int j = 0; j < columnLength; ++j) {
            currentTotalContestants += rowAggregate[j];
          }
          for (int j = columnLength; j <= C; ++j) {
            answer = min(answer, contestantsCount - currentTotalContestants);
            if (j < C) {
              currentTotalContestants += rowAggregate[j];
              currentTotalContestants -= rowAggregate[j - columnLength];
            }
          }
        }
      }
    }
  }
  printf("%d\n", answer == INT_MAX ? -1 : answer);
}
