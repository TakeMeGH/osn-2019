#include <tcframe/spec.hpp>
using namespace tcframe;

#include <bits/stdc++.h>
using namespace std;

#define ii pair<int,int> 
const int k1e9 = 1e9;

const int kMaxN = 2e5;
const int kMaxQ = 2e5;
const int kMaxS = 1e9;
const int kMaxSumO = 2e5;
const int kMaxNSub[] = {0, 0, 50, 50, 200, 2000};
const int kMaxQSub[] = {0, 0, 50, 50, 200, 2000};
const int kMaxSSub[] = {0, 0, 50, k1e9, k1e9, k1e9};
const int kMaxSumOSub[] = {0, 0, 50, 50, 200, 2000};

class ProblemSpec : public BaseProblemSpec {
protected:
  int N, S, Q;
  vector<int> O, P, ANS;
  vector< vector<int> > AB;

  void InputFormat(){
    LINE(N, S, Q);
    LINES(O, AB) % SIZE(N);
    LINES(P) % SIZE(Q);
  }

  void OutputFormat(){
    LINES(ANS) % SIZE(Q);
  }

  void GradingConfig(){
    TimeLimit(1);
    MemoryLimit(256);
  }

  void Constraints(){
    CONS(1 <= N && N <= kMaxN);
    CONS(1 <= Q && Q <= kMaxQ);
    CONS(1 <= S && S <= kMaxS);

    CONS(validIntervalNumber(AB, O));

    CONS(eachElementBetween(O, 1, S));
    CONS(sumBetween(O, 1, kMaxSumO));
    CONS(eachElementBetween(AB, 1, S));
    CONS(allSegmentIsValid(AB));
    CONS(eachElementBetween(P, 1, N));
    CONS(sortedIncreasing(P));
  }

  void Subtask1(){
    CONS(N == 5);
    CONS(S == 10);
    CONS(Q == 2);
    CONS(O == vector<int>({2, 1, 1, 1, 2}));

    CONS(AB[0] == vector<int>({1, 3, 9, 10}));
    CONS(AB[1] == vector<int>({5, 6}));
    CONS(AB[2] == vector<int>({5, 6}));
    CONS(AB[3] == vector<int>({4, 4}));
    CONS(AB[4] == vector<int>({4, 4, 7, 9}));

    CONS(P == vector<int>({1, 2}));
  }

  void Subtask2(){
    CONS(N == 10);
    CONS(S == 10);
    CONS(Q == 5);
    CONS(O == vector<int>({5, 1, 1, 1, 1, 1, 1, 1, 1, 1}));

    CONS(AB[0] == vector<int>({2, 2, 4, 4, 6, 6, 8, 8, 10, 10}));
    CONS(AB[1] == vector<int>({2, 2}));
    CONS(AB[2] == vector<int>({3, 3}));
    CONS(AB[3] == vector<int>({4, 4}));
    CONS(AB[4] == vector<int>({5, 5}));
    CONS(AB[5] == vector<int>({6, 6}));
    CONS(AB[6] == vector<int>({7, 7}));
    CONS(AB[7] == vector<int>({8, 8}));
    CONS(AB[8] == vector<int>({9, 9}));
    CONS(AB[9] == vector<int>({10, 10}));

    CONS(P == vector<int>({1, 5, 6, 8, 9}));
  }

  void Subtask3(){
    CONS(1 <= N && N <= kMaxNSub[2]);
    CONS(1 <= S && S <= kMaxSSub[2]);
    CONS(1 <= Q && Q <= kMaxQSub[2]);
    CONS(sumBetween(O, 1, kMaxSumOSub[2]));
  }

  void Subtask4(){
    CONS(1 <= N && N <= kMaxNSub[3]);
    CONS(1 <= S && S <= kMaxSSub[3]);
    CONS(1 <= Q && Q <= kMaxQSub[3]);
    CONS(sumBetween(O, 1, kMaxSumOSub[3]));
  }

  void Subtask5(){
    CONS(1 <= N && N <= kMaxNSub[4]);
    CONS(1 <= S && S <= kMaxSSub[4]);
    CONS(1 <= Q && Q <= kMaxQSub[4]);
    CONS(sumBetween(O, 1, kMaxSumOSub[4]));
  }

  void Subtask6(){
    CONS(1 <= N && N <= kMaxNSub[5]);
    CONS(1 <= S && S <= kMaxSSub[5]);
    CONS(1 <= Q && Q <= kMaxQSub[5]);
    CONS(sumBetween(O, 1, kMaxSumOSub[5]));
  }

  void Subtask7(){
    // Tidak ada batasan tambahan
  }

private:
  bool eachElementBetween(const vector<int>& X, int lo, int hi){
    for(int i : X){
      if(i < lo || i > hi){
        return false;
      }
    }
    return true;
  }
  bool eachElementBetween(const vector< vector<int> >& X, int lo, int hi){
    for(vector<int> i : X){
      for(int j : i){
        if(j < lo || j > hi){
          return false;
        }
      }
    }
    return true;
  }
  bool sumBetween(const vector<int>& X, int lo, int hi){
    int currentSum = 0;
    for(int i : X){
      currentSum += i;
      if(currentSum > hi)
        return false;
    }
    if(currentSum < lo || currentSum > hi)
      return false;
    return true;
  }
  bool validIntervalNumber(const vector< vector<int> >& X, const vector<int>& len){
    if(X.size() != len.size())
      return false;
    for(int i = 0; i < X.size(); ++i){
      if(X[i].size() != 2*len[i]){
        return false;
      }
    }
    return true;
  }
  bool segmentIsValid(const vector<int>& AB){
    for(int i = 0; i < AB.size()-1; i += 2){
      if(AB[i] > AB[i+1])
        return false;
    }
    for(int i = 1; i < AB.size()-1; i += 2){
      if(AB[i] >= AB[i+1]){
        return false;
      }
    }
    return true;
  }
  bool allSegmentIsValid(const vector< vector<int> >& AB){
    for(int i = 0; i < AB.size(); ++i){
      if(!segmentIsValid(AB[i])){
        return false;
      }
    }
    return true;
  }
  bool sortedIncreasing(const vector<int>& X){
    for(int i = 1; i < X.size(); ++i){
      if(X[i-1] >= X[i]){
        return false;
      }
    }
    return true;
  }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
  void SampleTestCase1(){
    Subtasks({3, 4, 5, 6, 7});

    Input({
      "5 10 2",
      "2 2 4 7 9",
      "1 1 3",
      "1 1 1", 
      "1 9 10", 
      "1 5 6", 
      "1", 
      "5"
    });
    Output({
      "4", 
      "1"
    });
  }

  void BeforeTestCase(){
    O.clear();
    P.clear();
    AB.clear();
  }

  void TestGroup1(){
    Subtasks({1, 3, 4, 5, 6, 7});
    CASE(
      N=5, S=10, Q=2,
      O={2,1,1,1,2},
      AB={
        {1,3,9,10},
        {5,6},
        {5,6},
        {4,4},
        {4,4,7,9}
      },
      P={1,2}
    );
  }

  void TestGroup2(){
    Subtasks({2, 3, 4, 5, 6, 7});
    CASE(
      N=10, S=10, Q=5,
      O={5,1,1,1,1,1,1,1,1,1},
      AB={
        {2,2,4,4,6,6,8,8,10,10},
        {2,2},
        {3,3},
        {4,4},
        {5,5},
        {6,6},
        {7,7},
        {8,8},
        {9,9},
        {10,10}
      },
      P={1,5,6,8,9}
    );
  }

  void TestGroup3(){ // 1 <= N, S, Q <= 50
    Subtasks({3, 4, 5, 6, 7});

    CASE( // 3_1 Simplest case
      N=1, S=1, Q=1,
      O={1},
      AB={{1, 1}},
      P={1}
    );
    CASE( // 3_2 All connected
      N=3, S=1, Q=3,
      O={1, 1, 1},
      AB={
        {1, 1},
        {1, 1},
        {1, 1}
      },
      P={1, 2, 3}
    );
    CASE( // 3_3 Two users with disjoint online time
      N=2, S=10, Q=2,
      O={2, 2},
      AB={
        {1, 2, 5, 7},
        {3, 4, 8, 10}
      },
      P={1, 2}
    );
    CASE( // 3_4 Ten users with chaining intervals (1 <-> 2, 2 <-> 3, 3 <-> 4, .... ), shuffled
      N=10, Q=5,
      generateChainingIntervals(N, S, O, AB),
      P={1, 2, 3, 5, 7}
    );
    CASE( // 3_5
      N=kMaxNSub[2]-5, Q=N,
      generateChainingIntervals(N, S, O, AB),
      generateRandomQuery(N, Q, P)
    );
    CASE( // 3_6
      N=kMaxNSub[2]-1, Q=N,
      generateChainingIntervals(N, S, O, AB),
      generateRandomQuery(N, Q, P)
    );
    CASE( // 3_7 6 users with three connected groups
      N=9, S=6, Q=4,
      O={1, 1, 1, 1, 1, 1, 1, 1, 1},
      AB={
        {1, 2},
        {1, 1},
        {2, 2},
        {3, 4},
        {3, 3},
        {4, 4},
        {5, 6},
        {5, 5},
        {6, 6}
      },
      P={1, 5, 8, 9}
    );
    CASE( // 3_8 Random intervals
      N=32, S=48, Q=30,
      generateRandomIntervalsForAll(N, S, kMaxSumOSub[2], O, AB),
      generateRandomQuery(N, Q, P)
    );
    CASE( // 3_9 Largest case with random intervals
      N=kMaxNSub[2], S=kMaxSSub[2], Q=30,
      generateRandomIntervalsForAll(N, S, kMaxSumOSub[2], O, AB),
      generateRandomQuery(N, Q, P)
    );
    CASE( // 3_10 Nesting intervals
      N=7, S=42, Q=3,
      O={1, 1, 1, 1, 1, 1, 1},
      AB={
        {8, 30},
        {11, 28},
        {15, 20},
        {16, 18},
        {17, 17},
        {38, 41},
        {39, 41}
      },
      shufflePartition(O, AB),
      P={1, 4, 6}
    );
    CASE( // 3_11 [A][B][A][C][B][A]
      N=3, S=50, Q=3,
      O={2, 3, 1},
      AB={
        {10, 19, 30, 40},
        {5, 7, 20, 27, 45, 47},
        {26, 29}
      },
      shufflePartition(O, AB),
      P={1, 2, 3}
    );
    CASE( // 3_12 All users acive all the time
      N=kMaxNSub[2], S=kMaxSSub[2], Q=min(N, kMaxQSub[2]),
      generateAllPeopleActive(N, S, kMaxSumOSub[2], O, AB, false),
      generateRandomQuery(N, Q, P)
    );
    CASE( // 3_13 All users active in splitted intervals
      N=7, S=kMaxSSub[2], Q=min(N, kMaxQSub[2]),
      generateAllPeopleActive(N, S, kMaxSumOSub[2], O, AB, true),
      generateRandomQuery(N, Q, P)
    );
    CASE( // 3_14 Random intervals, splitted over 4 groups
      N=12, S=kMaxSSub[2], Q=min(N, kMaxQSub[2]),
      generateIntervalsFromPartition(N, S, 4, O, AB),
      generateRandomQuery(N, Q, P)
    );
    CASE( // 3_15 Random intervals, splitted over 5 groups
      N=25, S=kMaxSSub[2], Q=min(N, kMaxQSub[2]),
      generateIntervalsFromPartition(N, S, 5, O, AB),
      generateRandomQuery(N, Q, P)
    );
    CASE( // 3_16 Random intervals, splitted over 7 groups
      N=32, S=kMaxSSub[2], Q=min(N, kMaxQSub[2]),
      generateIntervalsFromPartition(N, S, 7, O, AB),
      generateRandomQuery(N, Q, P)
    );
    CASE( // 3_17 3 users, one with two online times, connecting the other two
      N=3, S=50, Q=1,
      O={1, 2, 1},
      AB={{1, 2}, {2, 3, 4, 5}, {5, 6}},
      P={3}
    );
    CASE( // 3_18 Same as 3_17, but a bit more complex
      N=5, S=40, Q=1,
      O={1, 2, 1, 2, 1},
      AB={
        {1, 5}, {3, 7, 10, 12},
        {11, 15}, {13, 18, 22, 29},
        {29, 35}
      },
      P={5}
    );
    for(int i = 0; i < 3; ++i){
      CASE(
        N=kMaxNSub[2]-3, S=kMaxSSub[2], Q=min(N, kMaxQSub[2]),
        generateRandomMultipleIntervalCase(N, S, Q, O, AB, P, 3)
      );
    }
  }

  void TestGroup4(){
    Subtasks({4, 5, 6, 7});
    CASE( // 4_1 All users acive all the time
      N=kMaxNSub[3], S=kMaxSSub[3], Q=min(N, kMaxQSub[3]),
      generateAllPeopleActive(N, S, kMaxSumOSub[3], O, AB, false),
      generateRandomQuery(N, Q, P)
    );
    CASE( // 4_2 All users active in splitted intervals
      N=7, S=kMaxSSub[3], Q=min(N, kMaxQSub[3]),
      generateAllPeopleActive(N, S, kMaxSumOSub[3], O, AB, true),
      generateRandomQuery(N, Q, P)
    );
    for(int i = 0; i < 5; ++i){
      CASE(
        N=rnd.nextInt(1, kMaxNSub[3]),
        S=rnd.nextInt(kMaxNSub[3], kMaxSSub[3]),
        Q=rnd.nextInt(1, min(N, kMaxQSub[3])),
        generateRandomSingleIntervalCase(N, S, Q, O, AB, P)
      );
    }
    for(int i = 0; i < 5; ++i){
      CASE(
        N=kMaxNSub[3]-3, S=kMaxSSub[3], Q=min(N, kMaxQSub[3]),
        generateRandomMultipleIntervalCase(N, S, Q, O, AB, P, 3)
      );
    }
    for(int i = 0; i < 5; ++i){
      CASE(
        N=rnd.nextInt(1, kMaxNSub[3]),
        S=rnd.nextInt(kMaxNSub[3], kMaxSSub[3]),
        Q=rnd.nextInt(1, min(N, kMaxQSub[3])),
        generateRandomIntervalsForAll(N, S, kMaxSumOSub[3], O, AB),
        generateRandomQuery(N, Q, P)
      );
    }
    for(int i = 0; i < 10; ++i){
      CASE(
        N=kMaxNSub[3], S=kMaxSSub[3], Q=min(N, kMaxQSub[3]),
        generateRandomIntervalsForAll(N, S, kMaxSumOSub[3], O, AB),
        generateRandomQuery(N, Q, P)
      );
    }
  }

  void TestGroup5(){
    Subtasks({5, 6, 7});

    CASE( // 5_1 All users acive all the time
      N=kMaxNSub[4], S=kMaxSSub[4], Q=min(N, kMaxQSub[4]),
      generateAllPeopleActive(N, S, kMaxSumOSub[4], O, AB, false),
      generateRandomQuery(N, Q, P)
    );
    CASE( // 5_2 All users active in splitted intervals
      N=14, S=kMaxSSub[4], Q=min(N, kMaxQSub[4]),
      generateAllPeopleActive(N, S, kMaxSumOSub[4], O, AB, true),
      generateRandomQuery(N, Q, P)
    );
    for(int i = 0; i < 10; ++i){
      CASE(
        N=rnd.nextInt(kMaxNSub[3]+1, kMaxNSub[4]),
        S=rnd.nextInt(kMaxNSub[4], kMaxSSub[4]),
        Q=rnd.nextInt(1, min(N, kMaxQSub[4])),
        generateRandomSingleIntervalCase(N, S, Q, O, AB, P)
      );
    }
    for(int i = 0; i < 5; ++i){
      CASE(
        N=kMaxNSub[4]-10, S=kMaxSSub[4], Q=min(N, kMaxQSub[4]),
        generateRandomMultipleIntervalCase(N, S, Q, O, AB, P)
      );
    }
    for(int i = 0; i < 10; ++i){
      CASE(
        N=rnd.nextInt(kMaxNSub[3]+1, kMaxNSub[4]),
        S=rnd.nextInt(kMaxNSub[4], kMaxSSub[4]),
        Q=rnd.nextInt(1, min(N, kMaxQSub[4])),
        generateRandomIntervalsForAll(N, S, kMaxSumOSub[4], O, AB),
        generateRandomQuery(N, Q, P)
      );
    }
    for(int i = 0; i < 20; ++i){
      CASE(
        N=kMaxNSub[4], S=kMaxSSub[4], Q=min(N, kMaxQSub[4]),
        generateRandomIntervalsForAll(N, S, kMaxSumOSub[4], O, AB),
        generateRandomQuery(N, Q, P)
      );
    }
  }

  void TestGroup6(){
    Subtasks({6, 7});

    CASE( // 6_1 All users acive all the time
      N=kMaxNSub[5], S=kMaxSSub[5], Q=min(N, kMaxQSub[5]),
      generateAllPeopleActive(N, S, kMaxSumOSub[5], O, AB, false),
      generateRandomQuery(N, Q, P)
    );
    CASE( // 6_2 All users active in splitted intervals
      N=44, S=kMaxSSub[5], Q=min(N, kMaxQSub[5]),
      generateAllPeopleActive(N, S, kMaxSumOSub[5], O, AB, true),
      generateRandomQuery(N, Q, P)
    );
    for(int i = 0; i < 3; ++i){
      CASE(
        N=1337, S=123456789, Q=min(N, kMaxQSub[5]),
        generateRandomSingleIntervalCase(N, S, Q, O, AB, P)
      );
    }
    for(int i = 0; i < 5; ++i){
      CASE(
        N=kMaxNSub[5]-10, S=kMaxSSub[5], Q=min(N, kMaxQSub[5]),
        generateRandomMultipleIntervalCase(N, S, Q, O, AB, P)
      );
    }
    for(int i = 0; i < 10; ++i){
      CASE(
        N=rnd.nextInt(kMaxNSub[4]+1, kMaxNSub[5]),
        S=rnd.nextInt(kMaxNSub[5], kMaxSSub[5]),
        Q=rnd.nextInt(1, min(N, kMaxQSub[5])),
        generateRandomIntervalsForAll(N, S, kMaxSumOSub[5], O, AB),
        generateRandomQuery(N, Q, P)
      );
    }
    for(int i = 0; i < 20; ++i){
      CASE(
        N=kMaxNSub[5], S=kMaxSSub[5], Q=min(N, kMaxQSub[5]),
        generateRandomIntervalsForAll(N, S, kMaxSumOSub[5], O, AB),
        generateRandomQuery(N, Q, P)
      );
    }
  }

  void TestGroup7(){
    Subtasks({7});

    CASE( // 7_1 All users acive all the time
      N=kMaxN, S=kMaxS, Q=min(N, kMaxQ),
      generateAllPeopleActive(N, S, kMaxSumO, O, AB, false),
      generateRandomQuery(N, Q, P)
    );
    CASE( // 7_2 All users active in splitted intervals
      N=444, S=kMaxS, Q=min(N, kMaxQ),
      generateAllPeopleActive(N, S, kMaxSumO, O, AB, true),
      generateRandomQuery(N, Q, P)
    );
    for(int i = 0; i < 5; ++i){ // Randomized answer
      CASE(
        N=kMaxN, S=kMaxS, Q=min(N, kMaxQ),
        generateRandomSingleIntervalCase(N, S, Q, O, AB, P)
      );
    }
    for(int i = 0; i < 5; ++i){
      CASE(
        N=kMaxN-10, S=kMaxS, Q=min(N, kMaxQ),
        generateRandomMultipleIntervalCase(N, S, Q, O, AB, P)
      );
    }
    for(int i = 0; i < 10; ++i){ // Randomized N, S, and Q
      CASE(
        N=rnd.nextInt(kMaxNSub[5]+1, kMaxN),
        S=rnd.nextInt(kMaxN, kMaxS),
        Q=rnd.nextInt(1, min(N, kMaxQ)),
        generateRandomIntervalsForAll(N, S, kMaxSumO, O, AB),
        generateRandomQuery(N, Q, P)
      );
    }
    for(int i = 0; i < 10; ++i){ // Random intervals
      CASE(
        N=kMaxN, S=kMaxS, Q=min(N, kMaxQ),
        generateRandomIntervalsForAll(N, S, kMaxSumO, O, AB),
        generateRandomQuery(N, Q, P)
      );
    }
  }

private:
  void generateRandomStrictlyIncreasingVector(int size, int lo, int hi, vector<int> &A){
    assert(hi-lo+1 >= size);
    A.clear();
    int last = lo-1;
    for(int i = size-1; i >= 0; --i){
      int nextElem = rnd.nextInt(last+1, hi-i);
      A.push_back(nextElem);
      last = nextElem;
    }
  }

  void generateRandomIntervals(int onlineTime, int lo, int hi, 
                               vector<int> &AB){
    AB.clear();
    vector<int> A; A = vector<int>();
    generateRandomStrictlyIncreasingVector(onlineTime, lo, hi, A);
    for(int i = 0; i < onlineTime-1; ++i){
      int nextElem = rnd.nextInt(A[i], A[i+1]-1);
      AB.push_back(A[i]);
      AB.push_back(nextElem);
    }
    AB.push_back(A[onlineTime-1]);
    AB.push_back(rnd.nextInt(A[onlineTime-1], hi));
  }

  void generateRandomIntervalsForAll(int N, int S, int maxSumO,
                                     vector<int> &O,
                                     vector< vector<int> > &AB){
    assert(maxSumO >= N);
    AB.assign(N, vector<int>());
    // Generate O
    int remainingSum = maxSumO-N;
    for(int i = 0; i < N; ++i){
      int addTime = rnd.nextInt(0, min(S-1, remainingSum)); // Making sure everyone gets at least 1 online time
      O.push_back(1 + addTime);
      remainingSum -= addTime;
    }
    // Generate A and B
    for(int i = 0; i < N; ++i){
      generateRandomIntervals(O[i], 1, S, AB[i]);
    }
  }

  void generateRandomQuery(int N, int Q, vector<int> &P){
    generateRandomStrictlyIncreasingVector(Q, 1, N, P);
  }

  void shufflePartition(
      vector<int> &O,
      vector< vector<int> > &AB){
    vector<int> shuffled;
    shuffled.resize(O.size());
    for(int i = 0; i < O.size(); ++i)
      shuffled[i] = i;
    rnd.shuffle(shuffled.begin(), shuffled.end());
    vector<int> newO;
    vector< vector<int> > newAB;
    for(int i = 0; i < O.size(); ++i){
      newO.push_back(O[shuffled[i]]);
      newAB.push_back(AB[shuffled[i]]);
    }
    O = newO;
    AB = newAB;
  }

  void generateChainingIntervals(int N, int &S,
                                 vector<int> &O,
                                 vector< vector<int> > &AB){
    S = N+1;
    O.assign(N, 1);
    AB.clear();
    for(int i = 0; i < N; ++i){
      AB.push_back(vector<int>({i+1, i+2}));
    }
    shufflePartition(O, AB);
  }

  void generateAllPeopleActive(int N, int S, int maxO,
                               vector<int> &O,
                               vector< vector<int> > &AB,
                               bool split){
    AB.assign(N, vector<int>());
    if(!split){
      O.assign(N, 1);
      for(int i = 0; i < N; ++i){
        AB[i] = vector<int>({1, S});
      }
    }else{
      int intervalNum = min(S, maxO/N);
      O.assign(N, intervalNum);
      for(int i = 0; i < N; ++i){
        for(int j = 0; j < intervalNum; ++j){
          int l = (S/intervalNum)*j + 1, r = (S/intervalNum)*(j+1);
          AB[i].push_back(l);
          AB[i].push_back(r);
        }
      }
    }
  }

  void generateIntervalsFromPartition(
      int N,
      int S,
      int partitionSize,
      vector<int> &O,
      vector< vector<int> > &AB){
    vector<int> partition; // Number of people in each partition

    O.assign(N, 1);
    partition.assign(partitionSize, 1);
    for(int i = 0; i < N-partitionSize; ++i){
      int nextToAdd = rnd.nextInt(0, partitionSize-1);
      partition[nextToAdd]++;
    }

    // Determine ranges of each partition
    vector<int> range;
    generateRandomStrictlyIncreasingVector(2*partitionSize, 1, S, range);
    for(int i = 0; i < partitionSize; ++i){
      int l = range[2*i], r = range[2*i+1];
      int newL, newR, meetingPoint;
      newL = rnd.nextInt(l, r);
      newR = rnd.nextInt(newL, r);
      meetingPoint = rnd.nextInt(newL, newR);
      AB.push_back({newL, newR});
      for(int j = 1; j < partition[i]; ++j){
        newL = rnd.nextInt(l, meetingPoint);
        newR = rnd.nextInt(meetingPoint, r);
        meetingPoint = rnd.nextInt(newL, newR);
        AB.push_back({newL, newR});
      }
    }
    shufflePartition(O, AB);
  }

  void generateRandomSingleIntervalCase(int N, int S, int Q,
      vector<int> &O,
      vector< vector<int> > &AB,
      vector<int> &P){
    // Determine number of partitions
    int partitionSize = rnd.nextInt(1, min(N, S/2));
    generateIntervalsFromPartition(N, S, partitionSize, O, AB);
    generateRandomQuery(N, Q, P);
  }

  void generateRandomMultipleIntervalCase(int N, int S, int Q,
      vector<int> &O,
      vector< vector<int> > &AB,
      vector<int> &P,
      int connectingUser=10){
    vector<int> partition;

    int partitionSize = rnd.nextInt(connectingUser+1, min(N, S/2));
    O.assign(N, 1);
    partition.assign(partitionSize, 1);

    for(int i = 0; i < N-partitionSize; ++i){
      int nextToAdd = rnd.nextInt(0, partitionSize-1);
      partition[nextToAdd]++;
    }

    // Determine ranges of each partition
    vector<int> range;
    generateRandomStrictlyIncreasingVector(2*partitionSize, 1, S, range);
    for(int i = 0; i < partitionSize; ++i){
      int l = range[2*i], r = range[2*i+1];
      int newL, newR, meetingPoint;
      newL = rnd.nextInt(l, r);
      newR = rnd.nextInt(newL, r);
      meetingPoint = rnd.nextInt(newL, newR);
      if(partitionSize-i <= connectingUser){
        // Define first user as connecting user. Choose one partition to connect and add another interval
        int conn = rnd.nextInt(0, AB.size()-1);
        int interL = rnd.nextInt(AB[conn][0], AB[conn][1]);
        int interR = rnd.nextInt(AB[conn][0], AB[conn][1]);
        if(interL > interR)
          swap(interL, interR);
        O[AB.size()]++;
        AB.push_back({interL, interR, newL, newR});
      }else{
        AB.push_back({newL, newR});
      }
      for(int j = 1; j < partition[i]; ++j){
        newL = rnd.nextInt(l, meetingPoint);
        newR = rnd.nextInt(meetingPoint, r);
        meetingPoint = rnd.nextInt(newL, newR);
        AB.push_back({newL, newR});
      }
    }

    shufflePartition(O, AB);
    generateRandomQuery(N, Q, P);
  }

};
