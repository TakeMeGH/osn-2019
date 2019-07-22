#include <tcframe/spec.hpp>
using namespace tcframe;

#include <bits/stdc++.h>
using namespace std;

const int SMALLN = 200;
const int SMALLM = 400;

const int MEDIUMN = 2000;
const int MEDIUMM = 400000;

const int MAXN = 200000;
const int MAXM = 1000000000;

const vector<vector<int>> SUBTASK1_INTERVALS = {
  {1, 4, 2, 9, 7, 2, 2, 8},
  {7, 11, 4, 10, 11, 4, 8, 8},
};

const vector<vector<int>> SUBTASK2_INTERVALS = {
  {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20},
  {20, 20, 18, 20, 20, 18, 14, 16, 18, 20, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20},
};

class ProblemSpec : public BaseProblemSpec {
 protected:
  int N, M;
  vector<int> A, B;

  vector<int> ANS;

  void InputFormat() {
    LINE(N, M);
    LINES(A, B) % SIZE(N);
  }

  void OutputFormat() {
    LINES(ANS) % SIZE(N);
  }

  void StyleConfig() {
    CustomScorer();
  }

  void Constraints() {
    CONS(1 <= N && N <= MAXN);
    CONS(1 <= M && M <= MAXM);
    CONS(validIntervals(1, A, B, M));
  }

  void Subtask1() {
    CONS(N == 8);
    CONS(M == 11);
    CONS(A == SUBTASK1_INTERVALS[0]);
    CONS(B == SUBTASK1_INTERVALS[1]);
  }

  void Subtask2() {
    CONS(N == 20);
    CONS(M == 20);
    CONS(A == SUBTASK2_INTERVALS[0]);
    CONS(B == SUBTASK2_INTERVALS[1]);
  }

  void Subtask3() {
    CONS(N <= SMALLN);
    CONS(M <= SMALLM);
  }

  void Subtask4() {
    CONS(N <= MEDIUMN);
  }
  
  void Subtask5() {
    CONS(M <= MEDIUMM);
  }
  
  void Subtask6() {
    CONS(atMostTwoOverlappingIntervals(A, B));
  }
  
  void Subtask7() {
  }

 private:
  bool validIntervals(int lo, const vector<int> &A,
      const vector<int> &B, int hi) {
    for (int i = 0; i < A.size(); ++i) {
      if (lo <= A[i] && A[i] <= B[i] && B[i] <= hi);
      else return false;
    }
    
    return true;
  }
  
  bool atMostTwoOverlappingIntervals(const vector<int> &A,
      const vector<int> &B) {
    vector<pair<int, int>> ends;
    for (int a: A) ends.push_back({a, -1});
    for (int b: B) ends.push_back({b, +1});
    
    sort(ends.begin(), ends.end());
    
    int overlap = 0;
    for (pair<int, int> en: ends) {
      overlap -= en.second;
      
      if (overlap > 2) return false;
    }
    
    return true;
  }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
 protected:
  void SampleTestCase1() {
    Subtasks({3, 4, 5, 6, 7});
    Input({
      "4 5",
      "2 3",
      "1 2",
      "3 4",
      "5 5",
    });
    Output({
      "2",
      "1",
      "1",
      "0",
    });
  }
  
  void BeforeTestCase() {
    A.clear(); B.clear();
    A.reserve(MAXN); B.reserve(MAXN);
  }
  
  void AfterTestCase() {
    if (vector<vector<int>>({A, B}) == SUBTASK1_INTERVALS ||
        vector<vector<int>>({A, B}) == SUBTASK2_INTERVALS) {
      // Do not shuffle!
      return;
    }
    
    vector<pair<int, int>> AB(A.size());
    
    for (int i = 0; i < A.size(); ++i) {
      AB[i] = {A[i], B[i]};
    }
    
    rnd.shuffle(AB.begin(), AB.end());
    
    for (int i = 0; i < AB.size(); ++i) {
      tie(A[i], B[i]) = AB[i];
    }
  }

  void TestGroup1() {
    Subtasks({1, 3, 4, 5, 7});
    CASE(N = 8; M = 11; A = SUBTASK1_INTERVALS[0]; B = SUBTASK1_INTERVALS[1]);
  }

  void TestGroup2() {
    Subtasks({2, 3, 4, 5, 7});
    CASE(N = 20; M = 20; A = SUBTASK2_INTERVALS[0]; B = SUBTASK2_INTERVALS[1]);
  }

  // N <= 200, M <= 400, at most 2 overlaps
  void TestGroup3() {
    Subtasks({3, 4, 5, 6, 7});
    
    CASE(N = 3; M = 2; A = {1, 1, 2}; B = {1, 2, 2});
    CASE(N = 2; M = 1; A = {1, 1}; B = {1, 1});
    CASE(N = 1; M = 1; A = {1}; B = {1});
    CASE(N = 2; M = 3; A = {1, 2}; B = {2, 3});
    
    generateCommonTwoOverlappingIntervalCases(SMALLN, SMALLM);
    
    CASE(N = 10; M = 400, allSmallIntervals(N, M));
    CASE(N = 50, M = 400, allPointIntervals(N, M));
  }

  // N <= 200, M <= 400
  void TestGroup4() {
    Subtasks({3, 4, 5, 7});
    
    CASE(N = 3; M = 1; A = {1, 1, 1}; B = {1, 1, 1});
    CASE(N = 3; M = 5; A = {1, 2, 3}; B = {3, 4, 5});
    
    generateCommonIntervalCases(1, SMALLN, 20, SMALLM);
    
    CASE(N = 200; M = 20; allSmallIntervals(N, M));
  }

  // N <= 2000, M <= 400000, at most 2 overlaps
  void TestGroup5() {
    Subtasks({4, 5, 6, 7});
    
    generateCommonTwoOverlappingIntervalCases(MEDIUMN, MEDIUMM);
    
    CASE(N = 500; M = MEDIUMM; allSmallIntervals(N, M));
    CASE(N = 1000; M = MEDIUMM; allPointIntervals(N, M));
  }

  // N <= 2000, M <= 400000
  void TestGroup6() {
    Subtasks({4, 5, 7});
    
    generateCommonIntervalCases(SMALLN+1, MEDIUMN, SMALLM+1, MEDIUMM);
    
    CASE(N = 2000; M = 500; allSmallIntervals(N, M));
  }

  // N <= 2000, M <= MAXM, at most 2 overlaps
  void TestGroup7() {
    Subtasks({4, 6, 7});

    generateCommonTwoOverlappingIntervalCases(MEDIUMN, MAXM);
    
    CASE(N = 2000; M = MAXM; allPointIntervals(N, M));
    CASE(N = 2000; M = MAXM; allSmallIntervals(N, M));
  }

  // N <= 2000, M <= MAXM
  void TestGroup8() {
    Subtasks({4, 7});
    
    generateCommonIntervalCases(SMALLN+1, MEDIUMN, MEDIUMM+1, MAXM);

    CASE(N = MEDIUMN; M = MAXM; lotOfDuplicateIntervals(N, M, N));
  }
  
  // N <= MAXN, M <= 400000, at most 2 overlaps
  void TestGroup9() {
    Subtasks({5, 6, 7});

    generateCommonTwoOverlappingIntervalCases(MAXN, MEDIUMM);
    
  }
  
  // N <= MAXN, M <= 400000
  void TestGroup10() {
    Subtasks({5, 7});
    
    generateCommonIntervalCases(MEDIUMN+1, MAXN, SMALLM+1, MEDIUMM);

    CASE(N = MAXN; M = 10000; allSmallIntervals(N, M));
  }
  
  // N <= MAXN, M <= MAXM, at most 2 overlaps
  void TestGroup11() {
    Subtasks({6, 7});

    generateCommonTwoOverlappingIntervalCases(MAXN, MAXM);
    
    CASE(N = MAXN; M = MAXM; allPointIntervals(N, M));
    CASE(N = MAXN; M = MAXM; allSmallIntervals(N, M));
  }
  
  // N <= MAXN, M <= MAXM
  void TestGroup12() {
    Subtasks({7});

    generateCommonIntervalCases(MEDIUMN+1, MAXN, MEDIUMM+1, MAXM);
    
    CASE(N = MAXN; M = MAXM; lotOfDuplicateIntervals(N, M, N));
  }

 private:
  void generateCommonIntervalCases(int loN, int hiN, int loM, int hiM) {
    CASE(N = rnd.nextInt(loN, hiN); M = rnd.nextInt(loM, hiM);
        randomIntervals(N, M));
    CASE(N = rnd.nextInt(loN, hiN); M = rnd.nextInt(loM, hiM);
        allLargeIntervals(N, M));
    CASE(N = rnd.nextInt(loN, hiN); M = rnd.nextInt(loM, hiM);
        lotOfDuplicateIntervals(N, M));
    CASE(N = rnd.nextInt(loN, hiN); M = rnd.nextInt(loM, hiM);
        mixLargeSmallPointIntervals(N, M));

    CASE(N = hiN; M = hiM; randomIntervals(N, M));
    CASE(N = hiN; M = hiM; allLargeIntervals(N, M));
    CASE(N = hiN; M = hiM; lotOfDuplicateIntervals(N, M));
    CASE(N = hiN; M = hiM; mixLargeSmallPointIntervals(N, M));
    CASE(N = hiN; M = hiM; shrinkingIntervals(N, M));
  }
  
  void generateCommonTwoOverlappingIntervalCases(int n, int m) {
    // Reasons for not using random on n and m:
    //  if m is too small compared to n, some cases may fail

    CASE(N = n; M = m; noOverlappingIntervals(N, M));
    CASE(N = n; M = m; atMostTwoOverlappingIntervals(N, M));
    CASE(N = n; M = m; atMostTwoOverlappingIntervals(N, M, 10));
  }

  void randomIntervals(int n, int m) {
    for (int i = 0; i < n; ++i) {
      int l = rnd.nextInt(1, m);
      int r = rnd.nextInt(1, m);
      if (r < l) swap(l, r);
      
      A.push_back(l); B.push_back(r);
    }
  }
  
  void allLargeIntervals(int n, int m, int d=10) {
    assert(d*2 - 1 <= m);

    for (int i = 0; i < n; ++i) {
      A.push_back(rnd.nextInt(1, d));
      B.push_back(rnd.nextInt(m-d+1, m));
    }
  }
  
  void allSmallIntervals(int n, int m, int d=10) {
    assert(d <= m);
    
    for (int i = 0; i < n; ++i) {
      A.push_back(rnd.nextInt(1, m-d+1));
      B.push_back(A.back() + rnd.nextInt(d));
    }
  }
  
  void allPointIntervals(int n, int m) {
    for (int i = 0; i < n; ++i) {
      A.push_back(rnd.nextInt(1, m));
      B.push_back(A.back());
    }
  }
  
  void lotOfDuplicateIntervals(int n, int m, int d=10) {
    int nn = n/d;
    randomIntervals(nn, m);
    
    for (int i = nn; i < n; ++i) {
      A.push_back(A[i % nn]);
      B.push_back(B[i % nn]);
    }
  }
  
  void mixLargeSmallPointIntervals(int n, int m) {
    allLargeIntervals(n/3, m);
    allSmallIntervals(n/3, m);
    allPointIntervals(n - n/3 - n/3, m);
  }
  
  void shrinkingIntervals(int n, int m) {
    for (int i = 0; i < n; ++i) {
      A.push_back(i+1);
      B.push_back(m-i);
    }
  }
  
  void noOverlappingIntervals(int n, int m) {
    if (m <= MEDIUMM) {
      assert(n*2 <= m);

      vector<int> bits(m, 0);
      for (int i = 0; i < n*2; ++i) bits[i] = 1;
      
      rnd.shuffle(bits.begin(), bits.end());
      
      for (int i = 0; i < m; ++i) {
        if (bits[i] == 0) continue;
        
        if (A.size() == B.size()) A.push_back(i+1);
        else B.push_back(i+1);
      }
    } else {
      vector<int> ends;
      while (ends.size() < n*2) {
        for (int i = ends.size(); i < n*2; ++i) {
          ends.push_back(rnd.nextInt(1, m));
        }
        
        sort(ends.begin(), ends.end());
        ends.resize(unique(ends.begin(), ends.end()) - ends.begin());
      }
      
      for (int i = 0; i < ends.size(); ++i) {
        if (i & 1) B.push_back(ends[i]);
        else A.push_back(ends[i]);
      }
    }
  }
  
  void atMostTwoOverlappingIntervals(int n, int m, int d=2) {
    noOverlappingIntervals(n/d, m);
    noOverlappingIntervals(n - n/d, m);
  }
};
