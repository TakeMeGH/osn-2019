#include <bits/stdc++.h>
using namespace std;

struct Point {
  int x, y;

  Point(int x, int y): x(x), y(y) {}
};

int query(Point P) {
  printf("? %d %d\n", P.x, P.y);
  fflush(stdout);
  int K;
  if (scanf("%d", &K) == EOF) {
    exit(0);
  }
  return K;
}

void answer(Point A, Point B) {
  printf("! %d %d %d %d\n", A.x, A.y, B.x, B.y);
  fflush(stdout);
  exit(0);
}

Point solve(int plus, int minus) {
  assert((plus & 1) == (minus & 1));
  return Point((plus + minus) >> 1, (plus - minus) >> 1);
}

int main() {
  int R, C, Q;
  scanf("%d %d %d", &R, &C, &Q);
  int distanceFromTopLeft = query(Point(1, 1));
  int distanceFromBottomLeft = query(Point(R, 1));
  Point A = solve(2 + distanceFromTopLeft, (R - 1) - distanceFromBottomLeft);
  answer(A, A);
}
