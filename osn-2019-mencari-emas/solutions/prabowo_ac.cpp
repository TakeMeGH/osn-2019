#include <bits/stdc++.h>
using namespace std;

int ask(int x, int y) {
  printf("? %d %d\n", x, y);
  fflush(stdout);
  
  int ret;
  if (scanf("%d", &ret)) return ret;
  return -1;
}

int ask(const pair<int, int> &p) {
  return ask(p.first, p.second);
}

void answer(const pair<int, int> &p, const pair<int, int> &q) {
  printf("! %d %d %d %d", p.first, p.second, q.first, q.second);
  fflush(stdout);
  exit(0);
}

// x + y = a
// x - y = b
pair<int, int> solve(int a, int b) {
  return {(a + b) / 2, (a - b) / 2};
}

int main() {
  int r, c, q;
  assert(scanf("%d %d %d", &r, &c, &q) == 3);
  
  int d[4] = {ask(1, 1), ask(1, c), ask(r, c), ask(r, 1)};
  
  pair<int, int> corners[4] = {
    solve(1+1 + d[0], 1-c + d[1]),
    solve(1+1 + d[0], r-1 - d[3]),
    solve(r+c - d[2], 1-c + d[1]),
    solve(r+c - d[2], r-1 - d[3]),
  };

  function<bool(pair<int, int> p)> insideGrid = [&](const pair<int, int> &p) {
    return 1 <= p.first && p.first <= r && 1 <= p.second && p.second <= c;
  };

  if (insideGrid(corners[0]) && insideGrid(corners[3]) &&
      ask(corners[0]) == 0) {
    answer(corners[0], corners[3]);
  } else answer(corners[1], corners[2]);
  return 0;
}
