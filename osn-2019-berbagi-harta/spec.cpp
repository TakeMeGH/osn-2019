#include <tcframe/spec.hpp>
using namespace tcframe;

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200000;
const int MAXH = 1000000;

class ProblemSpec : public BaseProblemSpec {
 protected:
  int N, P, Q;
  vector<int> H, A, B;

  long long ANS;

  void InputFormat() {
    LINE(N, P, Q);
    LINE(H % SIZE(N));
    LINE(A % SIZE(P));
    LINE(B % SIZE(Q));
  }

  void OutputFormat() {
    LINE(ANS);
  }

  void StyleConfig() {
    CustomScorer();
  }

  void Constraints() {
    CONS(1 <= N && N <= MAXN);
    CONS(1 <= P && P <= N);
    CONS(1 <= Q && Q <= N);
    CONS(eachElementBetween(H, 0, MAXH));
    CONS(eachElementBetween(A, 1, N));
    CONS(eachElementBetween(B, 1, N));
    CONS(strictlyIncreasing(A));
    CONS(strictlyIncreasing(B));
    CONS(unionCoversN(A, B, N));
  }

  void Subtask1() {
    CONS(N == 6);
    CONS(P == 6);
    CONS(Q == 3);
    CONS(H == vector<int>({4, 8, 15, 16, 23, 42}));
    CONS(A == vector<int>({1, 2, 3, 4, 5, 6}));
    CONS(B == vector<int>({2, 4, 5}));
  }

  void Subtask2() {
    CONS(N == 20);
    CONS(P == 10);
    CONS(Q == 10);
    CONS(H == vector<int>({1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20}));
    CONS(A == vector<int>({1, 3, 5, 7, 9, 11, 13, 15, 17, 19}));
    CONS(B == vector<int>({2, 4, 6, 8, 10, 12, 14, 16, 18, 20}));
  }

  void Subtask3() {
    CONS(N <= 2);
  }

  void Subtask4() {
    CONS(N <= 2000);
  }
  
  void Subtask5() {
    CONS(allElementSame(H));
  }
  
  void Subtask6() {
    CONS(A == B);
  }

  void Subtask7() {
  }

 private:
  bool eachElementBetween(const vector<int> &A, int lo, int hi) {
    for (int num: A) if (num < lo || num > hi) return false;
    return true;
  }
  
  bool strictlyIncreasing(const vector<int> &A) {
    for (int i = 1; i < A.size(); ++i) if (A[i-1] >= A[i]) return false;
    return true;
  }
  
  bool allElementSame(const vector<int> &A) {
    for (int a: A) if (a != A[0]) return false;
    return true;
  }
  
  bool unionCoversN(const vector<int> &A, const vector<int> &B, int N) {
    vector<int> u;
    int i, j;
    for (i = 0, j = 0; i < A.size(); ++i) {
      while (j < B.size() && B[j] < A[i]) {
        u.push_back(B[j++]);
      }
      u.push_back(A[i]);
    }
    
    while (j < B.size()) u.push_back(B[j++]);
    
    u.resize(unique(u.begin(), u.end()) - u.begin());
    if (u.size() != N) return false;

    for (int i = 0; i < N; ++i) {
      if (u[i] != i+1) return false;
    }
    
    return true;
  }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
 protected:
  void SampleTestCase1() {
    Subtasks({4, 7});
    Input({
      "7 5 5",
      "1 3 6 0 4 2 10",
      "1 3 4 5 6",
      "2 3 4 5 7",
    });
    Output({
      "9",
    });
  }
  
  void BeforeTestCase() {
    A.clear(); B.clear(); H.clear();
  }

  void AfterTestCase() {
    P = A.size();
    Q = B.size();
  }

  void TestGroup1() {
    Subtasks({1, 4, 7});
    CASE(N = 6; H = {4, 8, 15, 16, 23, 42};
         A = {1, 2, 3, 4, 5, 6}; B = {2, 4, 5});
  }

  void TestGroup2() {
    Subtasks({2, 4, 7});
    CASE(N = 20; H = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
         A = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19}; B = {2, 4, 6, 8, 10, 12, 14, 16, 18, 20});
  }

  // N <= 2, H[i] = H[j], A = B
  void TestGroup3() {
    Subtasks({3, 4, 5, 6, 7});
    
    CASE(N = 1; H = {11037}; A = B = {1});
    CASE(N = 2; H = {30303, 30303}; A = B = {1, 2});
  }

  // N <= 2, H[i] = H[j]
  void TestGroup4() {
    Subtasks({3, 4, 5, 7});

    CASE(N = 2; H = {123456, 123456}; A = {1}, B = {1, 2});
    CASE(N = 2; H = {123456, 123456}; A = {1, 2}, B = {1});
    CASE(N = 2; H = {123456, 123456}; A = {2}, B = {1, 2});
    CASE(N = 2; H = {123456, 123456}; A = {1, 2}, B = {2});
  }

  // N <= 2, A = B
  void TestGroup5() {
    Subtasks({3, 4, 6, 7});
    
    CASE(N = 2; H = {123, 456}; A = B = {1, 2});
    CASE(N = 2; H = {654, 312}; A = B = {1, 2});
  }
  
  // N <= 2
  void TestGroup6() {
    Subtasks({3, 4, 7});
    
    CASE(N = 2; H = {54321, 987650}; A = {1}; B = {1, 2});
    CASE(N = 2; H = {54321, 987650}; A = {1, 2}; B = {1});
    CASE(N = 2; H = {987650, 54321}; A = {1}; B = {1, 2});
    CASE(N = 2; H = {987650, 54321}; A = {1, 2}; B = {1});

    CASE(N = 2; H = {54321, 987650}; A = {2}; B = {1, 2});
    CASE(N = 2; H = {54321, 987650}; A = {1, 2}; B = {2});
    CASE(N = 2; H = {987650, 54321}; A = {2}; B = {1, 2});
    CASE(N = 2; H = {987650, 54321}; A = {1, 2}; B = {1});
  }

  // N <= 2000, H[i] = H[j], A = B
  void TestGroup7() {
    Subtasks({4, 5, 6, 7});

    generateCommonSameHABCases(2000);
  }

  // N <= 2000, H[i] = H[j]
  void TestGroup8() {
    Subtasks({4, 5, 7});

    generateCommonSameHCases(2000);
  }

  // N <= 2000, A = B
  void TestGroup9() {
    Subtasks({4, 6, 7});

    generateCommonSameABCases(2000);
  }
  
  // N <= 2000
  void TestGroup10() {
    Subtasks({4, 7});

    generateCommonCases(2000);
  }

  // N <= 200000, H[i] = H[j], A = B
  void TestGroup11() {
    Subtasks({5, 6, 7});

    generateCommonSameHABCases(MAXN);
  }

  // N <= 200000, H[i] = H[j]
  void TestGroup12() {
    Subtasks({5, 7});

    generateCommonSameHCases(MAXN);
  }

  // N <= 200000, A = B
  void TestGroup13() {
    Subtasks({6, 7});

    generateCommonSameABCases(MAXN);
  }

  // N <= 200000
  void TestGroup14() {
    Subtasks({7});

    generateCommonCases(MAXN);
  }

 private:
  void generateCommonCases(int n) {
    CASE(N = rnd.nextInt(n/2, n); H = randomVector(N); randomAB(N));

    CASE(N = n; H = randomVector(N); randomAB(N));
    CASE(N = n; H = increasingVector(N); randomAB(N));
    CASE(N = n; H = decreasingVector(N); randomAB(N));
    CASE(N = n; H = lotOfDuplicateElements(N); randomAB(N));

    CASE(N = n; H = randomVector(N);
         A = randomStrictlyIncreasing(N); B = iota1(N));
    CASE(N = n; H = increasingVector(N);
         A = randomStrictlyIncreasing(N); B = iota1(N));
    CASE(N = n; H = decreasingVector(N);
         A = randomStrictlyIncreasing(N); B = iota1(N));
    CASE(N = n; H = lotOfDuplicateElements(N);
         A = randomStrictlyIncreasing(N); B = iota1(N));

    CASE(N = n; H = randomVector(N);
         A = iota1(N); B = randomStrictlyIncreasing(N));
    CASE(N = n; H = increasingVector(N);
         A = iota1(N); B = randomStrictlyIncreasing(N));
    CASE(N = n; H = decreasingVector(N);
         A = iota1(N); B = randomStrictlyIncreasing(N));
    CASE(N = n; H = lotOfDuplicateElements(N);
         A = iota1(N); B = randomStrictlyIncreasing(N));
  }
  
  void generateCommonSameABCases(int n) {
    CASE(N = rnd.nextInt(n/2, n); H = randomVector(N); A = B = iota1(N));
  
    CASE(N = n; H = randomVector(N); A = B = iota1(N));
    CASE(N = n; H = increasingVector(N); A = B = iota1(N));
    CASE(N = n; H = decreasingVector(N); A = B = iota1(N));
    CASE(N = n; H = lotOfDuplicateElements(N); A = B = iota1(N));
  }
  
  void generateCommonSameHCases(int n) { 
    CASE(N = rnd.nextInt(n/2, n); H = vector<int>(N, rnd.nextInt(MAXH+1));
         randomAB(N));
  
    CASE(N = n; H = vector<int>(N, 0); randomAB(N));
    CASE(N = n; H = vector<int>(N, MAXH); randomAB(N));
    CASE(N = n; H = vector<int>(N, rnd.nextInt(MAXH+1));
         A = randomStrictlyIncreasing(N); B = iota1(N));
    CASE(N = n; H = vector<int>(N, rnd.nextInt(MAXH+1));
         A = iota1(N); B = randomStrictlyIncreasing(N));
  }
  
  void generateCommonSameHABCases(int n) {
    CASE(N = rnd.nextInt(n/2, n); H = vector<int>(N, rnd.nextInt(MAXH+1));
         A = B = iota1(N));
    CASE(N = n; H = vector<int>(N, 0); A = B = iota1(N));
    CASE(N = n; H = vector<int>(N, MAXH); A = B = iota1(N));
    CASE(N = n; H = vector<int>(N, rnd.nextInt(MAXH+1)), A = B = iota1(N));
  }
 
  vector<int> iota1(int N) {
    vector<int> ret(N);
    iota(ret.begin(), ret.end(), 1);
    return ret;
  }

  vector<int> randomStrictlyIncreasing(int N) {
    vector<int> ret;
    for (int i = 1; i <= N; ++i) if (rnd.nextInt(2)) {
      ret.push_back(i);  
    }
    return ret;
  }

  void randomAB(int N) {
    for (int i = 0; i < N; ++i) {
      int r = rnd.nextInt(1, 3);
      if (r & 1) A.push_back(i+1);
      if (r & 2) B.push_back(i+1);
    }
  }

  vector<int> randomVector(int N, int lo=0, int hi=MAXH) {
    vector<int> ret(N);
    for (int i = 0; i < N; ++i) ret[i] = rnd.nextInt(lo, hi);
    return ret;
  }

  vector<int> increasingVector(int N, int lo=0, int hi=MAXH) {
    vector<int> ret = randomVector(N, lo, hi);
    sort(ret.begin(), ret.end());
    return ret;
  }

  vector<int> decreasingVector(int N, int lo=0, int hi=MAXH) {
    vector<int> ret = randomVector(N, lo, hi);
    sort(ret.begin(), ret.end());
    return ret;
  }
  
  vector<int> lotOfDuplicateElements(int N, int lo=0, int hi=MAXH) {
    int sz = N/4;
    vector<int> ret = randomVector(sz, lo, hi);
    for (int i = sz; i < N; ++i) ret.push_back(ret[i % sz]);
    rnd.shuffle(ret.begin(), ret.end());
    return ret;
  }
};
