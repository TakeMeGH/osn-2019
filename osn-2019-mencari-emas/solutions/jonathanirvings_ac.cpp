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
  if ((plus & 1) != (minus & 1)) {
    return Point(INT_MAX, INT_MAX);
  }
  return Point((plus + minus) >> 1, (plus - minus) >> 1);
}

bool validPoint(Point P, int R, int C) {
  return 1 <= P.x && P.x <= R && 1 <= P.y && P.y <= C;
}

int main() {
  int R, C, Q;
  scanf("%d %d %d", &R, &C, &Q);
  int distanceFromTopLeft = query(Point(1, 1));
  int plusTopLeft = 2 + distanceFromTopLeft;
  int distanceFromBottomRight = query(Point(R, C));
  int plusBottomRight = (R + C) - distanceFromBottomRight;

  int distanceFromBottomLeft = query(Point(R, 1));
  int minusBottomLeft = (R - 1) - distanceFromBottomLeft;
  int distanceFromTopRight = query(Point(1, C));
  int minusTopRight = (1 - C) + distanceFromTopRight;

  {
    Point A = solve(plusTopLeft, minusBottomLeft);
    Point B = solve(plusBottomRight, minusTopRight);
    if (validPoint(A, R, C) && validPoint(B, R, C) && query(A) == 0) {
      answer(A, B);
    }
  }

  {
    Point A = solve(plusTopLeft, minusTopRight);
    Point B = solve(plusBottomRight, minusBottomLeft);
    answer(A, B);
  }
}
