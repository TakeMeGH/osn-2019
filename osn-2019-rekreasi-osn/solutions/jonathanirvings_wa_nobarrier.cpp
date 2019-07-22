#include <bits/stdc++.h>
using namespace std;

const char EMPTY = '.';
const char BLOCK = 'x';

struct Point {
  int x, y;

  Point(int x, int y): x(x), y(y) {}

  void move(char c) {
    if (c == '>') {
      ++y;
    } else if (c == 'v') {
      ++x;
    } else {
      assert(false);
    }
  }
};

struct Test {
  int R, C;
  string M;
  vector<string> S;
};

namespace smallC {

const char IN_PATH = 'P';
const int NOT_COMPUTED = -1;

vector<string> S;
vector<vector<vector<int>>> dp;
Test T;

Point nextInRowMajorOrder(Point now) {
  if (now.y == T.C - 1) {
    return Point(now.x + 1, 0);
  }
  return Point(now.x, now.y + 1);
}

int f(Point now, int mask) {
  if (now.x == T.R) {
    return 0;
  }
  int &ret = dp[now.x][now.y][mask];
  if (ret != NOT_COMPUTED) {
    return ret;
  }
  int next_mask = (mask << 1) & ((1 << T.C) - 1);
  if (S[now.x][now.y] == IN_PATH) {
    int visitable = 0;
    if (now.x > 0) {
      visitable |= (mask & (1 << (T.C - 1)));
    }
    if (now.y > 0) {
      visitable |= (mask & (1 << 0));
    }
    if (__builtin_popcount(visitable) > 1) {
      return INT_MAX >> 1;
    }
    ret = f(nextInRowMajorOrder(now), next_mask | 1);
  } else {
    ret = f(nextInRowMajorOrder(now), next_mask)
          + (S[now.x][now.y] == EMPTY ? 1 : 0);

    if (S[now.x][now.y] == EMPTY) {
      int visitable = 0;
      if (now.x > 0) {
        visitable |= (mask & (1 << (T.C - 1)));
      }
      if (now.y > 0) {
        visitable |= (mask & (1 << 0));
      }
      ret = min(ret,
                f(nextInRowMajorOrder(now), next_mask + (visitable ? 1 : 0)));
    } else {
      ret = min(ret, f(nextInRowMajorOrder(now), next_mask));
    }
  }
  return ret;
}

void backtrack(Point now, int mask) {
  if (now.x == T.R) {
    return;
  }
  int ret = f(now, mask);

  int next_mask = (mask << 1) & ((1 << T.C) - 1);
  if (S[now.x][now.y] == IN_PATH) {
    S[now.x][now.y] = EMPTY;
    backtrack(nextInRowMajorOrder(now), next_mask | 1);
  } else {
    if (ret == f(nextInRowMajorOrder(now), next_mask)
                 + (S[now.x][now.y] == EMPTY ? 1 : 0)) {
      if (S[now.x][now.y] == EMPTY) {
        S[now.x][now.y] = BLOCK;
      }
      backtrack(nextInRowMajorOrder(now), next_mask);
    } else {
      if (S[now.x][now.y] == EMPTY) {
        int visitable = 0;
        if (now.x > 0) {
          visitable |= (mask & (1 << (T.C - 1)));
        }
        if (now.y > 0) {
          visitable |= (mask & (1 << 0));
        }
        backtrack(nextInRowMajorOrder(now), next_mask + (visitable ? 1 : 0));
      } else {
        backtrack(nextInRowMajorOrder(now), next_mask);
      }
    }
  }
}

vector<string> solve(const Test &T) {
  smallC::T = T;
  S = T.S;
  
  Point now = Point(0, 0);
  S[now.x][now.y] = IN_PATH;
  for (int i = 0; i < T.M.size(); ++i) {
    now.move(T.M[i]);
    S[now.x][now.y] = IN_PATH;
  }

  dp = vector<vector<vector<int>>>(T.R,
      vector<vector<int>>(T.C, vector<int>(1 << T.C, NOT_COMPUTED)));
  backtrack(Point(0, 0), 0);
  
  return S;
}

}  // namespace smallC

namespace shortestPath {

bool validPoint(Point p, const Test &T) {
  return 1 <= p.x && p.x < T.R && 0 <= p.y && p.y < T.C - 1;
}

vector<string> solve(const Test &T) {
  vector<string> S = T.S;

  vector<vector<Point>> parent(T.R, vector<Point>(T.C, Point(-1, -1)));
  vector<vector<int>> distance(T.R, vector<int>(T.C, INT_MAX));
  vector<vector<bool>> visited(T.R, vector<bool>(T.C, false));
  
  deque<Point> d;
  d.push_front(Point(1, T.C - 2));
  distance[1][T.C - 2] = 0;

  while (!d.empty()) {
    Point now = d.front();
    d.pop_front();

    if (visited[now.x][now.y]) {
      continue;
    }
    visited[now.x][now.y] = true;

    if (now.x == T.R - 1 || now.y == 0) {
      while (now.x != 1 || now.y != T.C - 2) {
        Point pt = parent[now.x][now.y];
        if (now.x >= pt.x && now.y <= pt.y) {
          if (S[now.x][now.y] == EMPTY) {
            S[now.x][now.y] = BLOCK;
          }
        }
        now = pt;
      }
      if (S[now.x][now.y] == EMPTY) {
        S[now.x][now.y] = BLOCK;
      }
      return S;
    }

    for (pair<int, int> dir : {make_pair(-1, 0), make_pair(0, 1)}) {
      Point dest = Point(now.x + dir.first, now.y + dir.second);
      int dist = distance[now.x][now.y];
      if (validPoint(dest, T) && dist < distance[dest.x][dest.y]) {
        distance[dest.x][dest.y] = dist;
        parent[dest.x][dest.y] = now;
        d.push_front(dest);
      }
    }
    for (pair<int, int> dir:
        {make_pair(1, 0), make_pair(1, -1), make_pair(0, -1)}) {
      Point dest = Point(now.x + dir.first, now.y + dir.second);
      if (validPoint(dest, T)) {
        int dist =
            distance[now.x][now.y] + (T.S[dest.x][dest.y] == EMPTY ? 1 : 0);

        if (dist < distance[dest.x][dest.y]) {
          distance[dest.x][dest.y] = dist;
          parent[dest.x][dest.y] = now;
          if (T.S[dest.x][dest.y] == EMPTY) {
            d.push_back(dest);
          } else {
            d.push_front(dest);
          }
        }
      }
    }
  }
  assert(false);
}

}  // namespace shortestPath

namespace noBarrier {

vector<string> solve(const Test &T) {
  vector<string> S = T.S;
  
  pair<Point, Point> last = make_pair(Point(-1, -1), Point(0, 0));
  Point now = Point(0, 0);

  now.move(T.M[0]);
  for (int i = 1; i <= T.R + T.C - 2; ++i) {
    if (i == T.R + T.C - 2 || T.M[i] != T.M[i - 1]) {
      if (last.first.x != -1) {
        if (last.first.x == last.second.x) {
          // >v
          if (last.second.y - last.first.y <= now.x - last.second.x) {
            for (int y = last.first.y; y < last.second.y; ++y) {
              S[last.first.x + 1][y] = BLOCK;
            }
          } else {
            for (int x = last.second.x + 1; x <= now.x; ++x) {
              S[x][now.y - 1] = BLOCK;
            }
          }
        } else {
          // v>
          if (now.y - last.second.y <= last.second.x - last.first.x) {
            for (int y = last.second.y + 1; y <= now.y; ++y) {
              S[now.x - 1][y] = BLOCK;
            }
          } else {
            for (int x = last.first.x; x < last.second.x; ++x) {
              S[x][last.first.y + 1] = BLOCK;
            }
          }
        }
      }
      last = make_pair(last.second, now);
    }
    if (i < T.R + T.C - 2) {
      now.move(T.M[i]);
    }
  }
  return S;
}

}  // namespace noBarrier

bool singleTurn(const Test &T) {
  for (int i = 0; i < T.C - 1; ++i) {
    if (T.M[i] != '>') {
      return false;
    }
  }
  for (int i = T.C - 1; i < T.R + T.C - 2; ++i) {
    if (T.M[i] != 'v') {
      return false;
    }
  }
  return true;
}

bool emptyGrid(const Test &T) {
  return all_of(T.S.begin(), T.S.end(), [&](const string& s) {
    return all_of(s.begin(), s.end(), [&](const char& c) {
      return c == EMPTY;
    });
  });
}

vector<string> solve(const Test &T) {
  if (T.R <= 100 && T.C <= 16) {
    return smallC::solve(T);
  }
  if (singleTurn(T)) {
    return shortestPath::solve(T);
  }
  if (emptyGrid(T)) {
    return noBarrier::solve(T);
  }
  assert(false);
}

int main() {
  int R, C;
  scanf("%d %d\n", &R, &C);
  
  string M(R + C - 2, 0);
  for (int i = 0; i < R + C - 2; ++i) {
    scanf("%c", &M[i]);
  }

  vector<string> S(R, string(C, 0));
  for (int i = 0; i < R; ++i) {
    scanf("\n");
    for (int j = 0; j < C; ++j) {
      scanf("%c", &S[i][j]);
    }
  }

  Test T = (Test){R, C, M, S};
  vector<string> answer = solve(T);

  for (int i = 0; i < answer.size(); ++i) {
    printf("%s\n", answer[i].c_str());
  }
}
