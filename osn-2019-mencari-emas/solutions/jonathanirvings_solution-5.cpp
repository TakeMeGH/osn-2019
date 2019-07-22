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

int main() {
  int R, C, Q;
  scanf("%d %d %d", &R, &C, &Q);
  int distanceLeft = query(Point(1, 1));
  int distanceRight = query(Point(1, C));
  answer(Point(1, distanceLeft + 1), Point(1, C - distanceRight));
}
