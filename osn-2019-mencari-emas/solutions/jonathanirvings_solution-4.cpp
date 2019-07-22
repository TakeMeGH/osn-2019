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
  pair<int, int> minimumDistanceLeft = make_pair(INT_MAX, 0);
  pair<int, int> minimumDistanceRight = make_pair(INT_MAX, 0);
  for (int x = 1; x <= R; ++x) {
    int distanceLeft = query(Point(x, 1));
    int distanceRight = query(Point(x, C));
    minimumDistanceLeft = min(minimumDistanceLeft,
                              make_pair(distanceLeft, x));
    minimumDistanceRight = min(minimumDistanceRight,
                               make_pair(distanceRight, -x));
  }
  // We find the largest x with distance = minimumDistanceRight to mistakenly
  // returning the same value as minimumDistanceLeft.
  minimumDistanceRight.second *= -1;

  Point A = Point(minimumDistanceLeft.second, minimumDistanceLeft.first + 1);
  Point B = Point(minimumDistanceRight.second, C - minimumDistanceRight.first);
  answer(A, B);
}
