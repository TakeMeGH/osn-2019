#include <tcframe/runner.hpp>
using namespace tcframe;

#include <bits/stdc++.h>
using namespace std;

class ProblemSpec : public BaseProblemSpec {
 protected:
  int R, C;
  vector<vector<char>> S;

  vector<vector<char>> OUT;

  void InputFormat() {
    LINE(R, C);
    GRID(S) % SIZE(R, C);
  }

  void OutputFormat() {
    GRID(OUT) % SIZE(R, C);
  }

  void StyleConfig() {
    CustomScorer();
  }

  void Constraints() {
    CONS(2 <= R && R <= 1000);
    CONS(2 <= C && C <= 1000);
    CONS(validGrid(S));
  }

  void Subtask1() {
    Points(20);
    CONS(R == 4);
    CONS(C == 4);
  }

  void Subtask2() {
    Points(20);
    CONS(R == 53);
    CONS(C == 97);
    CONS(firstColIsEmpty(S));
  }

  void Subtask3() {
    Points(20);
    CONS(R == 90);
    CONS(C == 76);
  }

  void Subtask4() {
    Points(20);
    CONS(R == 1000);
    CONS(C == 1000);
    CONS(checkerboard(S));
  }

  void Subtask5() {
    Points(20);
    CONS(R == 1000);
    CONS(C == 1000);
  }

private:
  bool validGrid(const vector<vector<char>> &S) {
    for (int i = 0; i < S.size(); ++i) {
      for (int j = 0; j < S[i].size(); ++j) {
        if ((i + j) % 2 == 0) {
          if (S[i][j] != '.') return false;  
        } else {
          if (S[i][j] != '.' && S[i][j] != 'x') return false;
        }
      }
    }

    return true;
  }
  
  bool firstColIsEmpty(const vector<vector<char>> &S) {
    for (const vector<char>&s: S) if (s[0] != '.') return false;
    return true;
  }
  
  bool checkerboard(const vector<vector<char>> &S) {
    for (int i = 0; i < S.size(); ++i) for (int j = 0; j < S[i].size(); ++j) {
      if ((i + j & 1) && S[i][j] != 'x') return false;
    }
    
    return true;
  }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:

  void SampleTestCase1() {
    Subtasks({});
    Input({
      "4 5",
      ".x.x.",
      "..x..",
      ".....",
      "....x",
    });
    Output({
      ".x>x.",
      ".^x..",
      "..^..",
      "...>x",
    });
  }

  void BeforeTestCase() {
    S.clear();
  }

  void TestGroup1() {
    Subtasks({1});

    CASE(R = 4; C = 4; S = {
      {'.', '.', '.', 'x'},
      {'x', '.', '.', '.'},
      {'.', 'x', '.', '.'},
      {'x', '.', 'x', '.'},
    });
  }

  void TestGroup2() {
    Subtasks({2});

    CASE(R = 53; C = 97; firstColumnEmpty(R, C));
  }

  void TestGroup3() {
    Subtasks({3});

    CASE(R = 90; C = 76; randomGrid(R, C));
  }

  void TestGroup4() {
    Subtasks({4, 5});

    CASE(R = 1000; C = 1000; checkerboard(R, C));
  }

  void TestGroup5() {
    Subtasks({5});

    CASE(R = 1000; C = 1000; randomGrid(R, C, 3));
  }

 private:
  void checkerboard(int R, int C) {
    S = vector<vector<char>>(R, vector<char>(C, '.'));
    for (int i = 0; i < R; ++i) {
      for (int j = i+1&1; j < C; j += 2) {
        S[i][j] = 'x';
      }
    }
  }
  
  void randomGrid(int R, int C, int density=1) {
    assert(density >= 1);
    
    S = vector<vector<char>>(R, vector<char>(C, '.'));
    for (int i = 0; i < R; ++i) {
      for (int j = 0; j < C; ++j) {
        if (i + j & 1) {
          if (rnd.nextInt(density+1) < density) S[i][j] = 'x';
        }
      }
    }
  }
  
  void firstColumnEmpty(int R, int C, int density=1) {
    randomGrid(R, C, density);
    for (int i = 0; i < R; ++i) S[i][0] = '.';
  }
};
