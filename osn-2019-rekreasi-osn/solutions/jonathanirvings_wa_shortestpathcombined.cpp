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

namespace solution {

Test T;
vector<string> S;
vector<vector<Point>> parent;
vector<vector<int>> distance;
vector<vector<bool>> visited;

pair<int, vector<Point>> findShortestPath(
    Point source,
    vector<pair<int, int>> freeDir,
    vector<pair<int, int>> payDir,
    function<bool(Point)> validPoint,
    function<bool(Point)> endPoint) {

  deque<Point> d;
  d.push_front(Point(source.x, source.y));
  distance[source.x][source.y] = 0;

  while (!d.empty()) {
    Point now = d.front();
    d.pop_front();

    if (visited[now.x][now.y]) {
      continue;
    }
    visited[now.x][now.y] = true;

    if (endPoint(now)) {
      int dist = distance[now.x][now.y];

      vector<Point> path;
      while (now.x != source.x || now.y != source.y) {
        path.push_back(now);
        now = parent[now.x][now.y];
      }
      path.push_back(now);
      reverse(path.begin(), path.end());
      return make_pair(dist, path);
    }

    for (pair<int, int> dir : freeDir) {
      Point dest = Point(now.x + dir.first, now.y + dir.second);
      int dist = distance[now.x][now.y];
      if (validPoint(dest) && dist < distance[dest.x][dest.y]) {
        distance[dest.x][dest.y] = dist;
        parent[dest.x][dest.y] = now;
        d.push_front(dest);
      }
    }
    for (pair<int, int> dir : payDir) {
      Point dest = Point(now.x + dir.first, now.y + dir.second);
      if (validPoint(dest)) {
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

pair<int, int> getRightDownShortestPath(
    Point start, Point end,
    vector<Point> &pathY, vector<Point> &pathX) {
  
  pathY.clear();
  int distanceY = 0;
  if (pathY.size() == 0) {
    for (int x = start.x + 1; x < T.R; ++x) {
      for (int y = start.y; y < end.y; ++y) {
        distance[x][y] = INT_MAX;
        visited[x][y] = false;
      }
    }

    pair<int, vector<Point>> shortestPath = findShortestPath(
        Point(start.x + 1, end.y - 1),
        {make_pair(-1, 0), make_pair(0, 1)},
        {make_pair(1, 0), make_pair(1, -1), make_pair(0, -1)},
        [&](Point p) {
          return start.x < p.x && p.x < T.R && start.y <= p.y && p.y < end.y;
        },
        [&](Point p) {
          return p.y == start.y;
        }
    );

    distanceY = shortestPath.first;
    pathY = shortestPath.second;
  }

  pathX.clear();
  int distanceX = 0;
  if (pathX.size() == 0) {
    for (int x = start.x + 1; x <= end.x; ++x) {
      for (int y = 0; y < end.y; ++y) {
        distance[x][y] = INT_MAX;
        visited[x][y] = false;
      }
    }

    pair<int, vector<Point>> shortestPath = findShortestPath(
        Point(start.x + 1, end.y - 1),
        {make_pair(-1, 0), make_pair(0, 1)},
        {make_pair(1, 0), make_pair(1, -1), make_pair(0, -1)},
        [&](Point p) {
          return start.x < p.x && p.x <= end.x && 0 <= p.y && p.y < end.y;
        },
        [&](Point p) {
          return p.x == end.x;
        }
    );

    distanceX = shortestPath.first;
    pathX = shortestPath.second;
  }

  return make_pair(distanceY, distanceX);
}

pair<int, int> getDownRightShortestPath(
    Point start, Point end,
    vector<Point> &pathX, vector<Point> &pathY) {
  
  pathX.clear();
  int distanceX = 0;
  if (pathX.size() == 0) {
    for (int x = start.x; x < end.x; ++x) {
      for (int y = start.y + 1; y < T.C; ++y) {
        distance[x][y] = INT_MAX;
        visited[x][y] = false;
      }
    }

    pair<int, vector<Point>> shortestPath = findShortestPath(
        Point(end.x - 1, start.y + 1),
        {make_pair(1, 0), make_pair(0, -1)},
        {make_pair(-1, 0), make_pair(-1, 1), make_pair(0, 1)},
        [&](Point p) {
          return start.x <= p.x && p.x < end.x && start.y < p.y && p.y < T.C;
        },
        [&](Point p) {
          return p.x == start.x;
        }
    );

    distanceX = shortestPath.first;
    pathX = shortestPath.second;
  }

  pathY.clear();
  int distanceY = 0;
  if (pathY.size() == 0) {
    for (int x = 0; x < end.x; ++x) {
      for (int y = start.y + 1; y <= end.y; ++y) {
        distance[x][y] = INT_MAX;
        visited[x][y] = false;
      }
    }

    pair<int, vector<Point>> shortestPath = findShortestPath(
        Point(end.x - 1, start.y + 1),
        {make_pair(1, 0), make_pair(0, -1)},
        {make_pair(-1, 0), make_pair(-1, 1), make_pair(0, 1)},
        [&](Point p) {
          return 0 <= p.x && p.x < end.x && start.y < p.y && p.y <= end.y;
        },
        [&](Point p) {
          return p.y == end.y;
        }
    );

    distanceY = shortestPath.first;
    pathY = shortestPath.second;
  }
  
  return make_pair(distanceX, distanceY);
}

void blockPoint(Point p) {
  if (S[p.x][p.y] == EMPTY) {
    S[p.x][p.y] = BLOCK;
  }
}

void blockRightDownPath(vector<Point> path) {
  blockPoint(path[0]);
  for (int i = 1; i < path.size(); ++i) {
    if (path[i].x >= path[i - 1].x && path[i].y <= path[i - 1].y) {
      blockPoint(path[i]);
    }
  }
}

void blockDownRightPath(vector<Point> path) {
  blockPoint(path[0]);
  for (int i = 1; i < path.size(); ++i) {
    if (path[i].x <= path[i - 1].x && path[i].y >= path[i - 1].y) {
      blockPoint(path[i]);
    }
  }
}

void blockRightDown(vector<pair<Point, Point>> rightDown, vector<string> &S) {
  vector<int> prefixSumY(rightDown.size());
  vector<int> suffixSumX(rightDown.size());

  pair<vector<Point>, vector<Point>> dummy;

  for (int i = 0; i < rightDown.size(); ++i) {
    prefixSumY[i] = getRightDownShortestPath(
        rightDown[i].first,
        rightDown[i].second,
        dummy.first,
        dummy.second).first;
    if (i > 0) {
      prefixSumY[i] += prefixSumY[i - 1];
    }
  }

  for (int i = rightDown.size() - 1; i >= 0; --i) {
    suffixSumX[i] = getRightDownShortestPath(
        rightDown[i].first,
        rightDown[i].second,
        dummy.first,
        dummy.second).second;
    if (i < rightDown.size() - 1) {
      suffixSumX[i] += suffixSumX[i + 1];
    }
  }

  pair<int, int> optimalCost = make_pair(INT_MAX, -1);
  for (int i = -1; i < (int)rightDown.size(); ++i) {
    // Use Y in range [0, i].
    int cost = 0;
    if (i >= 0) {
      cost += prefixSumY[i];
    }
    if (i < (int)rightDown.size() - 1) {
      cost += suffixSumX[i + 1];
    }
    optimalCost = min(optimalCost, make_pair(cost, i));
  }

  for (int i = 0; i < rightDown.size(); ++i) {
    getRightDownShortestPath(
        rightDown[i].first,
        rightDown[i].second,
        dummy.first,
        dummy.second);
    if (i <= optimalCost.second) {
      blockRightDownPath(dummy.first);
    } else {
      blockRightDownPath(dummy.second);
    }
  }
}

void blockDownRight(vector<pair<Point, Point>> downRight, vector<string> &S) {
  vector<int> prefixSumX(downRight.size());
  vector<int> suffixSumY(downRight.size());

  pair<vector<Point>, vector<Point>> dummy;

  for (int i = 0; i < downRight.size(); ++i) {
    prefixSumX[i] = getDownRightShortestPath(
        downRight[i].first,
        downRight[i].second,
        dummy.first,
        dummy.second).first;
    if (i > 0) {
      prefixSumX[i] += prefixSumX[i - 1];
    }
  }

  for (int i = downRight.size() - 1; i >= 0; --i) {
    suffixSumY[i] = getDownRightShortestPath(
        downRight[i].first,
        downRight[i].second,
        dummy.first,
        dummy.second).second;
    if (i < downRight.size() - 1) {
      suffixSumY[i] += suffixSumY[i + 1];
    }
  }

  pair<int, int> optimalCost = make_pair(INT_MAX, -1);
  for (int i = -1; i < (int)downRight.size(); ++i) {
    // Use X in range [0, i].
    int cost = 0;
    if (i >= 0) {
      cost += prefixSumX[i];
    }
    if (i < (int)downRight.size() - 1) {
      cost += suffixSumY[i + 1];
    }
    optimalCost = min(optimalCost, make_pair(cost, i));
  }

  for (int i = 0; i < downRight.size(); ++i) {
    getDownRightShortestPath(
        downRight[i].first,
        downRight[i].second,
        dummy.first,
        dummy.second);
    if (i <= optimalCost.second) {
      blockDownRightPath(dummy.first);
    } else {
      blockDownRightPath(dummy.second);
    }
  }
}

vector<string> solve(const Test &T) {
  S = T.S;
  solution::T = T;

  parent.clear();
  parent.resize(T.R, vector<Point>(T.C, Point(-1, -1)));
  distance.clear();
  distance.resize(T.R, vector<int>(T.C, INT_MAX));
  visited.clear();
  visited.resize(T.R, vector<bool>(T.C, false));
  
  pair<Point, Point> last = make_pair(Point(-1, -1), Point(0, 0));
  Point now = Point(0, 0);

  vector<pair<Point, Point>> rightDown;
  vector<pair<Point, Point>> downRight;

  now.move(T.M[0]);
  for (int i = 1; i <= T.R + T.C - 2; ++i) {
    if (i == T.R + T.C - 2 || T.M[i] != T.M[i - 1]) {
      if (last.first.x != -1) {
        if (last.first.x == last.second.x) {
          // >v
          rightDown.push_back(make_pair(last.first, now));
        } else {
          // v>
          downRight.push_back(make_pair(last.first, now));
        }
      }
      last = make_pair(last.second, now);
    }
    if (i < T.R + T.C - 2) {
      now.move(T.M[i]);
    }
  }

  blockRightDown(rightDown, S);
  blockDownRight(downRight, S);

  return S;
}

}  // namespace solution

vector<string> solve(const Test &T) {
  return solution::solve(T);
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
