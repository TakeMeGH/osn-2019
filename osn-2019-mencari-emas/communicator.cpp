#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> Point;

int ac() {
  cerr << "AC" << endl;
  return 0;
}

int wa() {
  cerr << "WA" << endl;
  return 0;
}

int waTooManyQueries() {
  cerr << "WA" << endl;
  cerr << "P > Q" << endl;
  return 0;
}

int L1Distance(Point A, Point B) {
  return abs(A.first - B.first) + abs(A.second - B.second);
}

int NearerL1Distance(Point X, Point A, Point B) {
  return min(L1Distance(X, A), L1Distance(X, B));
}

int main(int argc, char* argv[]) {
  ifstream tc_in(argv[1]);

  int R, C, Q;
  Point A, B;

  tc_in >> R >> C >> Q;
  tc_in >> A.first >> A.second;
  tc_in >> B.first >> B.second;
  cout << R << " " << C << " " << Q << endl;

  vector<pair<Point, int>> queries;

  while (true) {
    string op;
    if (!(cin >> op)) {
      return wa();
    }
    if (op == "?") {
      if (queries.size() == Q) {
        return waTooManyQueries();
      }
      
      int X, Y;
      if (!(cin >> X >> Y)) {
        return wa();
      }
      if (1 <= X && X <= R && 1 <= Y && Y <= C) {
        Point P = Point(X, Y);

        int K = NearerL1Distance(P, A, B);
        cout << K << endl;
        queries.push_back(make_pair(P, K));
      } else {
        return wa();
      }
    } else if (op == "!") {
      Point Ap, Bp;
      if (!(cin >> Ap.first >> Ap.second >> Bp.first >> Bp.second)) {
        return wa();
      }

      if ((Ap == A && Bp == B) || (Ap == B && Bp == A)) {
        // TODO(jonathanirvings): Make this semi-adaptive.
        // Even though the contestant gives the correct answer, the judge should
        // give WA if there is another valid solution (based on the queries).
        return ac();
      } else {
        return wa();
      }
    } else {
      return wa();
    }
  }
}
