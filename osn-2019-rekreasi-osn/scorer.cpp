#include <bits/stdc++.h>
using namespace std;

int ac() {
  puts("AC");
  return 0;
}

int ok(int score) {
  printf("OK\n%d\n",score);
  return 0;
}

int wa(string message) {
  fprintf(stderr, "%s\n", message.c_str());
  puts("WA");
  return 0;
}

const double EPS = 1e-9;
const int POW_CONSTANT = 4;

int main(int argc, char *argv[])
{
  FILE *in = fopen(argv[1], "r");
  FILE *out = fopen(argv[2], "r");  // Judge's
  FILE *con = fopen(argv[3], "r");

  int R, C;
  fscanf(in, "%d %d\n", &R, &C);
  
  string M(R + C - 2, 0);
  for (int i = 0; i < R + C - 2; ++i) {
    fscanf(in, "%c", &M[i]);
  }

  vector<string> S(R, string(C, 0));
  for (int i = 0; i < R; ++i) {
    fscanf(in, "\n");
    for (int j = 0; j < C; ++j) {
      fscanf(in, "%c", &S[i][j]);
    }
  }

  int Q = 0;
  vector<string> OUT(R, string(C, 0));
  for (int i = 0; i < R; ++i) {
    fscanf(out, "\n");
    for (int j = 0; j < C; ++j) {
      fscanf(out, "%c", &OUT[i][j]);
      if (OUT[i][j] == 'x') {
        ++Q;
      }
    }
  }

  vector<string> CON(R, string(C, 0));
  int P = 0;
  for (int i = 0; i < R; ++i) {
    fscanf(con, "\n");
    for (int j = 0; j < C; ++j) {
      if (fscanf(con, "%c", &CON[i][j]) != 1) {
        return wa("Unexpected EOF.");
      }
      if (CON[i][j] == 'x') {
        ++P;
      }
    }
  }

  fscanf(con, "\n");
  char dummy;
  if (fscanf(con, "%c", &dummy) == 1) {
    return wa("Expected EOF.");
  }

  for (int i = 0; i < R; ++i) {
    for (int j = 0; j < C; ++j) {
      if (S[i][j] == '.') {
        if (CON[i][j] != '.' && CON[i][j] != 'x') {

          return wa("Invalid character at (" +
                    to_string(i + 1) +
                    ", " +
                    to_string(j + 1) +
                    ").");
        }
      }
      if (S[i][j] == '#') {
        if (CON[i][j] != '#') {
          return wa("Invalid character at (" +
                    to_string(i + 1) +
                    ", " +
                    to_string(j + 1) +
                    ").");
        }
      }
    }
  }

  pair<int, int> now = make_pair(0, 0);
  if (CON[now.first][now.second] != '.') {
    return wa("Suggested path is blocked at (" +
              to_string(now.first + 1) +
              ", " +
              to_string(now.second + 1) +
              ").");
  }
  for (int i = 0; i < M.size(); ++i) {
    if (M[i] == '>') {
      ++now.second;
    } else {
      ++now.first;
    }
    if (CON[now.first][now.second] != '.') {
      return wa("Suggested path is blocked at (" +
                to_string(now.first + 1) +
                ", " +
                to_string(now.second + 1) +
                ").");
    }
  }

  vector<vector<int>> dp(R, vector<int>(C, 0));
  dp[0][0] = 1;
  for (int i = 0; i < R; ++i) {
    for (int j = 0; j < C; ++j) {
      if (i > 0) {
        dp[i][j] += dp[i - 1][j];
      }
      if (j > 0) {
        dp[i][j] += dp[i][j - 1];
      }
      dp[i][j] = min(dp[i][j], 2);
      if (CON[i][j] != '.') {
        dp[i][j] = 0;
      }
    }
  }
  if (dp[R - 1][C - 1] != 1) {
    return wa("Another path exists.");
  }

  if (P == Q) {
    return ac();
  } else if (Q < P && P <= R + C - 2) {
    double frac = (double)(R + C - 2 - P) / (R + C - 2 - Q);
    double fracPowed = pow(frac, POW_CONSTANT);
    int score = floor(2 + 8 * fracPowed + EPS);
    return ok(score);
  } else if (R + C - 2 < P && P <= 2 * (R + C - 2)) {
    return ok(2);
  } else if (2 * (R + C - 2) < P) {
    return ok(1);
  }

  assert(false);

  return 0;
}
