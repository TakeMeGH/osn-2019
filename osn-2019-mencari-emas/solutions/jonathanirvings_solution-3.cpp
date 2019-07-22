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
  vector<Point> answers;
  for (int x = 1; x <= R; ++x) {
    for (int y = 1; y <= C; ++y) {
      if (query(Point(x,y)) == 0) {
        answers.push_back(Point(x,y));
      }
    }
  }
  assert(1 <= answers.size() && answers.size() <= 2);
  answer(answers[0], answers.size() == 1 ? answers[0] : answers[1]);
}
