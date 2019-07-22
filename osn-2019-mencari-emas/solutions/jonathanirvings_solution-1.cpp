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
  pair<int, int> minimumDistance = make_pair(INT_MAX, 0);
  for (int x = 1; x <= R; ++x) {
    int distance = query(Point(x, 1));
    minimumDistance = min(minimumDistance, make_pair(distance, x));
  }
  Point A = Point(minimumDistance.second, minimumDistance.first + 1);
  answer(A, A);
}
