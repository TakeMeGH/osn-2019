#include <bits/stdc++.h>
using namespace std;

vector<int> query(vector<int> A) {
  printf("? %d", A.size());
  for (int i = 0; i < A.size(); ++i) {
    ++A[i];
    printf(" %d", A[i]);
  }
  puts("");
  fflush(stdout);
  int Y;
  if (scanf("%d", &Y) == EOF) {
    exit(0);
  }
  vector<int> B(Y);
  for (int i = 0; i < Y; ++i) {
    scanf("%d", &B[i]);
    --B[i];
  }
  return B;
}

void answer(int Z) {
  printf("! %d\n", Z + 1);
  fflush(stdout);
  exit(0);
}

int main() {
  int N, M, Q;
  scanf("%d %d %d", &N, &M, &Q);

  vector<int> firstSet(N);
  iota(firstSet.begin(), firstSet.end(), 0);

  vector<int> secondSet(M);
  iota(secondSet.begin(), secondSet.end(), N);

  if (firstSet.size() > secondSet.size()) {
    swap(firstSet, secondSet);
  }

  vector<int> firstSetQuery = query(firstSet);
  set<int> firstSetQuerySet = set<int>(firstSetQuery.begin(),
                                       firstSetQuery.end());
  if (firstSet.size() >= firstSetQuery.size()) {
    for (int i = 0; i < secondSet.size(); ++i) {
      if (firstSetQuerySet.count(secondSet[i]) == 0) {
        answer(secondSet[i]);
      }
    }
  } else {
    int L = 0;
    int R = firstSet.size() - 1;
    while (L < R) {
      int M = (L + R) >> 1;
      vector<int> tempSet(firstSet.begin() + L, firstSet.begin() + M + 1);
      if (query(tempSet).size() > tempSet.size()) {
        R = M;
      } else {
        L = M + 1;
      }
    }
    assert(L == R);
    answer(firstSet[L]);
  }
}
