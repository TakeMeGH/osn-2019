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

int wa() {
  puts("WA");
  return 0;
}

const double EPS = 1e-9;
const int POW_CONSTANT = 4;

int R, C;
char S[1005][1005];

char OUT[1005][1005];

bool watched[1005][1005];

int main(int argc, char *argv[]) {
  FILE *in = fopen(argv[1], "r");
  FILE *out = fopen(argv[2], "r");
  FILE *con = fopen(argv[3], "r");

  fscanf(in, "%d %d", &R, &C);
  for (int i = 0; i < R; ++i) fscanf(in, "%s", S[i]);
  
  for (int i = 0; i < R; ++i) {
    fscanf(con, "\n");
    for (int j = 0; j < C; ++j) fscanf(con, "%c", &OUT[i][j]);
    
    for (int j = 0; j < C; ++j) {
      if (S[i][j] == '.') {
        if ((i + j) % 2 == 1 && OUT[i][j] != '.') return wa();
        if (OUT[i][j] != '.' && OUT[i][j] != 'v' && OUT[i][j] != '^' &&
            OUT[i][j] != '<' && OUT[i][j] != '>') return wa();
      } else if (S[i][j] == 'x') {
        if (OUT[i][j] != 'x') return wa();
      }
    }
  }
  
  fscanf(con, "\n");
  if (fscanf(con, "%*c") != EOF) return wa();
  
  for (int i = 0; i < R; ++i) for (int j = 0; j < C; ++j) {
    if (i+1 < R && OUT[i][j] == 'v') watched[i+1][j] = true;
    if (j+1 < C && OUT[i][j] == '>') watched[i][j+1] = true;
    if (i-1 >= 0 && OUT[i][j] == '^') watched[i-1][j] = true;
    if (j-1 >= 0 && OUT[i][j] == '<') watched[i][j-1] = true;
  }
  
  int P = 0, Q = 0;
  for (int i = 0; i < R; ++i) for (int j = 0; j < C; ++j) {
    if (S[i][j] == 'x') {
      ++Q;
      if (watched[i][j]) ++P;
    }
  }
  
  if (P == Q) {
    return ac();
  } else if (P < Q) {
    double frac = (double) P / Q;
    double fracPowed = pow(frac, POW_CONSTANT);
    int score = floor(20 * fracPowed + EPS);
    return ok(score);
  }
 
  assert(false); 
  return 0;
}
