#include <tcframe/runner.hpp>
using namespace tcframe;

#include <bits/stdc++.h>
using namespace std;

class ProblemSpec : public BaseProblemSpec {
protected:
  int R, C;
  string M;
  vector<string> S;
  vector<string> OUT;

  void InputFormat() {
    LINE(R, C);
    LINE(M);
    LINES(S) % SIZE(R);
  }

  void OutputFormat() {
    LINES(OUT) % SIZE(R);
  }

  void StyleConfig() {
    CustomScorer();
  }

  void GradingConfig() {
  }

  void Constraints() {
    CONS(5 <= R && R <= 1000);
    CONS(5 <= C && C <= 1000);
    CONS(all_of(M.begin(), M.end(), [&](const char& m) {
      return m == '>' || m == 'v';
    }));
    CONS(all_of(S.begin(), S.end(), [&](const string& s) {
      return all_of(s.begin(), s.end(), [&](const char& c) {
        return c == '.' || c == '#';
      });
    }));
    CONS(validPath());
  }

  void Subtask1() {
    Points(10);
    CONS(R == 6);
    CONS(C == 6);
    CONS(emptyGrid());
  }

  void Subtask2() {
    Points(10);
    CONS(R == 5);
    CONS(C == 7);
    CONS(singleTurn());
  }

  void Subtask3() {
    Points(10);
    CONS(R == 7);
    CONS(C == 5);
  }

  void Subtask4() {
    Points(10);
    CONS(R == 100);
    CONS(C == 16);
  }

  void Subtask5() {
    Points(10);
    CONS(R == 677);
    CONS(C == 751);
    CONS(singleTurn());
    CONS(emptyGrid());
  }

  void Subtask6() {
    Points(10);
    CONS(R == 93);
    CONS(C == 78);
    CONS(emptyGrid());
  }

  void Subtask7() {
    Points(10);
    CONS(R == 1000);
    CONS(C == 1000);
    CONS(emptyGrid());
  }

  void Subtask8() {
    Points(10);
    CONS(R == 100);
    CONS(C == 99);
    CONS(singleTurn());
  }

  void Subtask9() {
    Points(10);
    CONS(R == 853);
    CONS(C == 814);
    CONS(singleTurn());
  }

  void Subtask10() {
    Points(10);
    CONS(R == 1000);
    CONS(C == 1000);
    CONS(singleTurn());
  }

private:
  bool validPath() {
    pair<int, int> now = make_pair(0, 0);
    if (S[now.first][now.second] == '#') {
      return false;
    }
    for (int i = 0; i < M.size(); ++i) {
      if (M[i] == '>') {
        ++now.second;
      } else {
        ++now.first;
      }
      if (now.first < 0 || now.first >= R ||
          now.second < 0 || now.second >= C) {
        return false;
      }
      if (S[now.first][now.second] == '#') {
        return false;
      }
    }
    return true;
  }

  bool singleTurn() {
    for (int i = 0; i < C - 1; ++i) {
      if (M[i] != '>') {
        return false;
      }
    }
    for (int i = C - 1; i < R + C - 2; ++i) {
      if (M[i] != 'v') {
        return false;
      }
    }
    return true;
  }

  bool emptyGrid() {
    return all_of(S.begin(), S.end(), [&](const string& s) {
      return all_of(s.begin(), s.end(), [&](const char& c) {
        return c == '.';
      });
    });
  }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:

  void SampleTestCase1() {
    Subtasks({});
    Input({"5 5", ">>vvv>>v", "....#", ".#..#", ".#.#.", ".....", "...#."});
    Output({"....#", "x#..#", ".#.#.", ".....", "...#."});
  }

  void SampleTestCase2() {
    Subtasks({});
    Input({"7 6",
           ">>>>>vvvvvv",
           "......",
           ".####.",
           "....#.",
           "###.#.",
           "....#.",
           ".####.",
           "......"});
    Output({"......",
            ".####.",
            "....#.",
            "###.#.",
            "....#.",
            ".####.",
            "......"});
  }

  void BeforeTestCase() {
    M.clear();
    S.clear();
  }

  void TestGroup1() {
    Subtasks({1});

    CASE(R = 6, C = 6, M = ">vv>>>vv>v", S = vector<string>(R, string(C, '.')));
  }

  void TestGroup2() {
    Subtasks({2});

    CASE(R = 5, C = 7, M = ">>>>>>vvvv",
         S = {".......",
              ".#.....",
              "....#..",
              "...#...",
              "......."});
  }

  void TestGroup3() {
    Subtasks({3});

    CASE(R = 7, C = 5, M = "vv>v>v>>vv",
         S = {"...#.",
              ".#.#.",
              "..##.",
              "...#.",
              ".....",
              ".....",
              "..#.."});
  }

  void TestGroup4() {
    Subtasks({4});

    CASE(R = 100, C = 16, specialTest4());
  }

  void TestGroup5() {
    Subtasks({5});

    CASE(R = 677, C = 751, GenerateCase(1, 1));
  }

  void TestGroup6() {
    Subtasks({6});

    CASE(R = 93, C = 78, GenerateCase(0, 1));
  }

  void TestGroup7() {
    Subtasks({7});

    CASE(R = 1000, C = 1000, GenerateCase(0, 1));
  }

  void TestGroup8() {
    Subtasks({8});

    CASE(R = 100, C = 99, GenerateCase(1, 0));
  }

  void TestGroup9() {
    Subtasks({9});

    CASE(R = 853, C = 814, GenerateCase(1, 0));
  }

  void TestGroup10() {
    Subtasks({10});

    CASE(R = 1000, C = 1000, GenerateCase(1, 0));
  }

private:
  void GenerateCase(bool singleTurn, bool emptyGrid) {
    GenerateTurns(singleTurn);
    GenerateGrid(emptyGrid);
  }

  void GenerateTurns(bool singleTurn) {
    if (singleTurn) {
      for (int i = 0; i < C - 1; ++i) {
        M.push_back('>');
      }
      for (int i = C - 1; i < R + C - 2; ++i) {
        M.push_back('v');
      }
    } else {
      pair<int, int> now = make_pair(0, 0);
      for (int i = 0; i < R + C - 2; ++i) {
        string possible = "";
        for (int j = now.second; j < C - 1; ++j) {
          possible += '>';
        }
        for (int j = now.first; j < R - 1; ++j) {
          possible += 'v';
        }
        M.push_back(possible[rnd.nextInt(possible.size())]);
        if (M[i] == '>') {
          ++now.second;
        } else {
          ++now.first;
        }
      }
    }
  }

  void GenerateGrid(bool emptyGrid) { 
    if (emptyGrid) {  
      S = vector<string>(R, string(C, '.'));  
    } else {  
      S = vector<string>(R, string(C, '.'));  
      for (int i = 0; i < R; ++i) { 
        for (int j = 0; j < C; ++j) { 
          S[i][j] = "..#"[rnd.nextInt(3)];  
        } 
      } 
      pair<int, int> now = make_pair(0, 0); 
      S[now.first][now.second] = '.'; 
      for (int i = 0; i < R + C - 2; ++i) { 
        if (M[i] == '>') {  
          ++now.second; 
        } else {  
          ++now.first;  
        } 
        S[now.first][now.second] = '.'; 
      } 
    } 
  }

  void specialTest4() {
    M = ">>>vv>>vv>>vvv";
    
    pair<int, int> now = make_pair(0, 0);
    for (int i = 0; i < R + C - 2; ++i) {
      string possible = "";
      for (int j = now.second; j < C - 1; ++j) {
        possible += '>';
      }
      for (int j = now.first; j < R - 1; ++j) {
        possible += 'v';
      }
      if (i >= M.size()) {
        M.push_back(possible[rnd.nextInt(possible.size())]);
      }
      if (M[i] == '>') {
        ++now.second;
      } else {
        ++now.first;
      }
    }

    S = vector<string>(R, string(C, '?'));
    assert(C == 16);
    S[0] = "????????????????";
    S[1] = "..#?????????????";
    S[2] = "..#?????????????";
    S[3] = "..#.#???????????";
    S[4] = "....#???????????";
    S[5] = "###.###?????????";
    S[6] = ".......?????????";
    S[7] = ".......?????????";

    for (int i = 0; i < R; ++i) {
      for (int j = 0; j < C; ++j) {
        if (S[i][j] == '?') {
          string possible = "..#";
          S[i][j] = possible[rnd.nextInt(possible.size())];
        }
      }
    }
    now = make_pair(0, 0);
    S[now.first][now.second] = '.';
    for (int i = 0; i < R + C - 2; ++i) {
      if (M[i] == '>') {
        ++now.second;
      } else {
        ++now.first;
      }
      S[now.first][now.second] = '.';
    }
  }
};
