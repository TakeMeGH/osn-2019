#include <tcframe/spec.hpp>
#include <bits/stdc++.h>
#define pb push_back
#define fi first
#define se second
using namespace tcframe;
using namespace std;

const int MAXR = 100000;

const vector<string> SUBTASK1_GRID = {
    "0000000001",
    "0010000100",
    "0110111000",
    "0111111000",
    "0111111001",
    "0101111000",
    "0110111010",
    "0110101000",
    "0111111000",
    "0000000000",
};

const vector<string> SUBTASK2_GRID = {
    "0101010101",
    "1010101010",
    "0101010101",
    "1010101010",
    "0101010101",
    "1010101010",
    "0101010101",
    "1010101010",
    "0101010101",
    "1010101010"
};

class ProblemSpec : public BaseProblemSpec {
 protected:
  int R, C;
  vector<string> V;
  int ans;

  void InputFormat() {
    LINE(R, C);
    LINES(V) % SIZE(R);
  }

  void OutputFormat() {
    LINE(ans);
  }

  void StyleConfig() {
    BatchEvaluator();
  }

  void Constraints() {
    CONS(1 <= R && R <= MAXR);
    CONS(1 <= R * C && R * C <= MAXR);
    CONS(isValidGrid(V, R, C));
  }

  void Subtask1() {
    CONS(R == 10);
    CONS(C == 10);
    CONS(V == SUBTASK1_GRID);
  }

  void Subtask2() {
     CONS(R == 10);
     CONS(C == 10);
     CONS(V == SUBTASK2_GRID);
  }

  void Subtask3() {
      CONS(R == 1);
      CONS(1 <= C && C <= 2000);
  }

  void Subtask4() {
      CONS(R == 1);
      CONS(1 <= C && C <= MAXR);
  }

  void Subtask5() {
    CONS(1 <= R && R <= 200);
    CONS(1 <= R * C && R * C <= 200);
  }

  void Subtask6() {
      CONS(1 <= R && R <= 2000);
      CONS(1 <= R * C && R * C <= 2000);
  }

  void Subtask7() {

  }

private:
    bool isValidGrid(const vector<string> A, int R, int C) {
            if (A.size() != R) return false;

        bool hasOne = false;
        for(int i = 0 ;i < A.size(); i++) {
            if(A[i].size() != C)
            {
                return false;
            }
            for(int j = 0; j < A[i].size(); j++) {
                if(A[i][j] == '0') continue;
                else if(A[i][j] == '1') {
                    hasOne = true;
                }
                else {
                    return false;
                }
            }
        }

        return hasOne;
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
    bool table[MAXR + 5];
    vector<int> primes;

protected:
    void SampleTestCase1() {
        Subtasks({5, 6, 7});

        Input({"4 3",
            "000",
            "110",
            "110",
            "000"});

        Output({"0"});
    }

    void SampleTestCase2() {
        Subtasks({5, 6, 7});

        Input({"3 4",
            "0010",
            "1100",
            "0100"});

        Output({"1"});
    }

    void SampleTestCase3() {
        Subtasks({5, 6, 7});

        Input({"3 3",
            "111",
            "101",
            "111"});

        Output({"-1"});
    }

    void BeforeTestCase() {
        V.clear();
    }

    // open tc 1
    void TestGroup1() {
        Subtasks({1, 5, 6, 7});

        CASE(R = 10, C = 10, V = SUBTASK1_GRID);
    }

    // open tc 2
    void TestGroup2() {
        Subtasks({2, 5, 6, 7});

        CASE(R = 10, C = 10, V = SUBTASK2_GRID);
    }

    void TestGroup3() {
        Subtasks({3, 4, 5, 6, 7});

        CASE(R = 1, C = rnd.nextInt(100, 200), V = randomOneRow(R, C));
        CASE(R = 1, C = 200, V = intervalOneRow(R, C));
        CASE(R = 1, C = 200, V = randomOneRow(R, C));
        CASE(R = 1, C = 200, V = goodRandomOneRow(R, C));
        CASE(R = 1, C = 200, V = goodRandomOneRow(R, C));
        CASE(R = 1, C = 200, V = intervalOneRow(R, C));
        CASE(R = 1, C = 200, V = answerAtEndOneRow(R, C));
        CASE(R = 1, C = 200, V = answerAtMiddleOneRow(R, C));
        CASE(R = 1, C = 200, V = answerAtBeginningOneRow(R, C));

        CASE(R = 1, C = 200, V = answerDecidedGrid(R, C, 180, 1, 10, 1, 189));

    }

    // R = 1, C <= 2000
    void TestGroup4() {
        Subtasks({3, 4, 6, 7});

        CASE(R = 1, C = rnd.nextInt(1000, 2000), V = randomOneRow(R, C));
        CASE(R = 1, C = 2000, V = intervalOneRow(R, C));
        CASE(R = 1, C = 2000, V = randomOneRow(R, C));
        CASE(R = 1, C = 2000, V = goodRandomOneRow(R, C));
        CASE(R = 1, C = 2000, V = goodRandomOneRow(R, C));
        CASE(R = 1, C = 2000, V = intervalOneRow(R, C));
        CASE(R = 1, C = 2000, V = answerAtEndOneRow(R, C));
        CASE(R = 1, C = 2000, V = answerAtMiddleOneRow(R, C));
        CASE(R = 1, C = 2000, V = answerAtBeginningOneRow(R, C));

        // most factor
        CASE(R = 1, C = 2000, V = answerDecidedGrid(R, C, 1680, 1, 201, 1, 1880));

        // highest x * f(x)
        CASE(R = 1, C = 2000, V = answerDecidedGrid(R, C, 1980, 1, 1, 1, 1980));
    }

    // R = 1, C = 100000
    void TestGroup5() {
        Subtasks({4, 7});
        CASE(R = 1, C = rnd.nextInt(50000, 100000), V = goodRandomOneRow(R, C));
        CASE(R = 1, C = rnd.nextInt(50000, 100000), V = randomOneRow(R, C));
        CASE(R = 1, C = 100000, V = intervalOneRow(R, C));
        CASE(R = 1, C = 100000, V = randomOneRow(R, C));
        CASE(R = 1, C = 100000, V = goodRandomOneRow(R, C));
        CASE(R = 1, C = 100000, V = goodRandomOneRow(R, C));
        CASE(R = 1, C = 100000, V = intervalOneRow(R, C));
        CASE(R = 1, C = 100000, V = answerAtEndOneRow(R, C));
        CASE(R = 1, C = 100000, V = answerAtMiddleOneRow(R, C));
        CASE(R = 1, C = 100000, V = answerAtBeginningOneRow(R, C));

        CASE(R = 1, C = 100000, V = answerDecidedGrid(R, C, 98280, 1, 10001, 1, 99280));

    }


    // R * C <= 200
    void TestGroup6() {
        Subtasks({5, 6, 7});
        CASE(R = 2, C = 2, V = {"11", "10"});
        CASE(R = 200, C = 1, V = flipFlopGrid(R, C));

        CASE(R = rnd.nextInt(2, 200), C = rnd.nextInt(1, 200 / R), V = flipFlopGrid(R, C));

        for(int i = 0; i < 2; i++) {
            CASE(R = rnd.nextInt(2, 200), C = rnd.nextInt(1, 200 / R), V = randomGrid(R, C, getRandomPrime(R, C)));
            CASE(R = rnd.nextInt(2, 200), C = rnd.nextInt(1, 200 / R), V = randomGrid(R, C, getManyFactor(R, C).back()));
            CASE(R = rnd.nextInt(2, 200), C = rnd.nextInt(1, 200 / R), V = randomGrid(R, C, getSquare(R, C)));
            CASE(R = rnd.nextInt(2, 200), C = rnd.nextInt(1, 200 / R), V = randomGrid(R, C, rnd.nextInt(1, R * C)));
        }

        // answer in the beginning hopefully can defeat unintended solution

        int tmp = getRandomPrime(200, 1);
        CASE(R = 200, C = 1, V = answerDecidedGrid(R, C, tmp, 1, 1, tmp, 1));
        tmp = sqrt(getSquare(14, 14));
        CASE(R = 14, C = 14, V = answerDecidedGrid(R, C, tmp * tmp, 1, 1, tmp, tmp));
        CASE(R = 14, C = 14, V = answerDecidedGrid(R, C, 105, 1, 1, 5, 7));

        // mosts factor , 2 * 2 * 3 * 3 * 5
        CASE(R = 13, C = 15, V = answerDecidedGrid(R, C, 180, 1, 1, 12, 15));



        tmp = getRandomPrime(200, 1);
        CASE(R = 200, C = 1, V = answerDecidedGrid(R, C, tmp, 200 - tmp + 1, 1, 200, 1));
        tmp = sqrt(getSquare(14, 14));
        CASE(R = 14, C = 14, V = answerDecidedGrid(R, C, tmp * tmp, 13 - tmp, 13 - tmp, 14, 14));
        CASE(R = 14, C = 14, V = answerDecidedGrid(R, C, 105, 10, 8, 14, 14));
    }

    // R * C <= 2000
    void TestGroup7() {
        Subtasks({6, 7});

        int sq = sqrt(2000);

        CASE(R = 2000, C = 1, V = flipFlopGrid(R, C));

        CASE(R = rnd.nextInt(2, 2000), C = rnd.nextInt(1, 2000 / R), V = flipFlopGrid(R, C));

        for(int i = 0; i < 2; i++) {
            CASE(R = rnd.nextInt(2, 2000), C = rnd.nextInt(1, 2000 / R), V = randomGrid(R, C, getRandomPrime(R, C)));
            CASE(R = rnd.nextInt(2, 2000), C = rnd.nextInt(1, 2000 / R), V = randomGrid(R, C, getManyFactor(R, C).back()));
            CASE(R = rnd.nextInt(2, 2000), C = rnd.nextInt(1, 2000 / R), V = randomGrid(R, C, getSquare(R, C)));
            CASE(R = rnd.nextInt(2, 2000), C = rnd.nextInt(1, 2000 / R), V = randomGrid(R, C, rnd.nextInt(1, R * C)));
        }

        // answer in the beginning hopefully can defeat unintended solution
        int tmp = getRandomPrime(2000, 1);
        CASE(R = 2000, C = 1, V = answerDecidedGrid(R, C, tmp, 1, 1, tmp, 1));
        tmp = sqrt(getSquare(sq, sq));
        CASE(R = sq, C = sq, V = answerDecidedGrid(R, C, tmp * tmp, 1, 1, tmp, tmp));
        CASE(R = sq, C = sq, V = answerDecidedGrid(R, C, 1890, 1, 1, 7, 9));

        // most factor
        CASE(R = 44, C = 45, V = answerDecidedGrid(R, C, 1680, 3, 3, 42, 44));

        // highest x * f(x)
        CASE(R = 44, C = 45, V = answerDecidedGrid(R, C, 1980, 1, 1, 44, 45));


        tmp = getRandomPrime(2000, 1);
        CASE(R = 2000, C = 1, V = answerDecidedGrid(R, C, tmp, 2000 - tmp + 1, 1, 2000, 1));
        tmp = sqrt(getSquare(sq, sq));
        CASE(R = sq, C = sq, V = answerDecidedGrid(R, C, tmp * tmp, sq - tmp - 1, sq - tmp - 1, sq, sq));

        // 2 * 3 * 5 * 7 * 9
        CASE(R = sq, C = sq, V = answerDecidedGrid(R, C, 1155, sq - 8, sq - 6, sq, sq));
    }

    // R * C <= 100.000
    void TestGroup8() {
        Subtasks({7});

        int sq = sqrt(10000);

        CASE(R = 100000, C = 1, V = flipFlopGrid(R, C));

        CASE(R = rnd.nextInt(2, 100000), C = rnd.nextInt(1, 100000 / R), V = flipFlopGrid(R, C));

        for(int i = 0; i < 2; i++) {
            CASE(R = rnd.nextInt(2, 100000), C = rnd.nextInt(1, 100000 / R), V = randomGrid(R, C, getRandomPrime(R, C)));
            CASE(R = rnd.nextInt(2, 100000), C = rnd.nextInt(1, 100000 / R), V = randomGrid(R, C, getManyFactor(R, C).back()));
            CASE(R = rnd.nextInt(2, 100000), C = rnd.nextInt(1, 100000 / R), V = randomGrid(R, C, getSquare(R, C)));
            CASE(R = rnd.nextInt(2, 100000), C = rnd.nextInt(1, 100000 / R), V = randomGrid(R, C, rnd.nextInt(1, R * C)));
        }

        // answer in the beginning hopefully can defeat unintended solution
        int tmp = getRandomPrime(100000, 1);
        CASE(R = 100000, C = 1, V = answerDecidedGrid(R, C, tmp, 1, 1, tmp, 1));
        tmp = sqrt(getSquare(sq, sq));
        CASE(R = sq, C = sq, V = answerDecidedGrid(R, C, tmp * tmp, 1, 1, tmp, tmp));

        // 2 * 3 * 3 * 5 * 7 * 11 * 13
        CASE(R = sq, C = sq, V = answerDecidedGrid(R, C, 90090, 1, 1, 11, 13));

        // most factor
        CASE(R = 316, C = 316, V = answerDecidedGrid(R, C, 98280, 2, 1, 313, 315));

        tmp = getRandomPrime(100000, 1);
        CASE(R = 100000, C = 1, V = answerDecidedGrid(R, C, tmp, 100000 - tmp + 1, 1, 100000, 1));
        tmp = sqrt(getSquare(sq, sq));
        CASE(R = sq, C = sq, V = answerDecidedGrid(R, C, tmp * tmp, sq - tmp - 1, sq - tmp - 1, sq, sq));

        // 2 * 3 * 5 * 7 * 11 * 13 * 3
        CASE(R = sq, C = sq, V = answerDecidedGrid(R, C, 1890, sq - 10, sq - 12, sq, sq));
    }
    private:
        void sieve() {
            table[1] = true;
            for(long long i = 2; i <= MAXR; i++) {
                if(table[i]) continue;
                primes.pb(i);
                for(long long j = i * i; j <= MAXR; j+= i) {
                    table[j] = true;
                }
            }
        }

        void generatePrime() {
            if(primes.size()) return;
            else {
                sieve();
            }
        }

        vector<string> randomOneRow(int R, int C) {
            string tmp = "";

            int count = rnd.nextInt(1, R * C);

            for(int i = 0; i < C; i++) {
                if(C - i == count) {
                    tmp += "1";
                    count--;
                }
                else if(count == 0) tmp += "0";
                else if(rnd.nextInt(2)) {
                    tmp += "1";
                    count--;
                }
                else tmp += "0";
            }

            vector<string> res;
            res.pb(tmp);

            return res;
        }

        // 01010101
        vector<string> intervalOneRow(int R, int C) {
            string tmp = "";
            vector<string> res;

            for(int i = 0; i < C; i++) {
                if(i % 2 == 0) tmp += "0";
                else tmp += "1";
            }

            res.pb(tmp);
            return res;

        }

        vector<string> answerAtBeginningOneRow(int R, int C) {
            string tmp = "";
            vector<string> res;

            int count = rnd.nextInt(1, R * C);

            for(int i = 0; i < count; i++) {
                tmp += "1";
            }
            for(int i = count; i < R * C;  i++) {
                tmp += "0";
            }

            res.pb(tmp);
            return res;
        }

        vector<string> answerAtMiddleOneRow(int R, int C) {
            string tmp = "";
            vector<string> res;

            int count = rnd.nextInt(1, R * C);

            int hit = R * C - count;
            hit /= 2;
            for(int i = 0; i < hit; i++) {
                tmp += "0";
            }
            for(int i = hit; i < hit + count; i++) {
                tmp += "1";
            }

            for(int i = hit + count; i < R * C; i++) {
                tmp += "0";
            }

            res.pb(tmp);
            return res;
        }

        vector<string> answerAtEndOneRow(int R, int C) {
            string tmp = "";
            vector<string> res;


            int count = rnd.nextInt(1, R * C);

            for(int i = 0; i < count; i++) {
                tmp += "1";
            }
            for(int i = count; i < R * C;  i++) {
                tmp += "0";
            }

            reverse(tmp.begin(), tmp.end());

            res.pb(tmp);
            return res;
        }

        vector<string> goodRandomOneRow(int R, int C) {
            string tmp = "";
            vector<string> res;

            int count = rnd.nextInt(1, R * C);

            for(int i = 0; i< count; i++) tmp += "1";
            for(int i = count; i < R * C; i++) tmp += "0";

            rnd.shuffle(tmp.begin(), tmp.end());

            res.pb(tmp);

            return res;
        }

        int getRandomPrime(int R, int C) {
            generatePrime();

            int many = R * C;
            int indeks = primes.size();

            for(int i = 0; i < primes.size(); i++) {
                if (primes[i] > many) {
                    indeks = i;
                    break;
                }
            }


            return primes[rnd.nextInt(indeks)];
        }

        // last one is the result, first one to last - 1 is the factor
        vector<int> getManyFactor(int R, int C) {
            generatePrime();
            int many = R * C;

            vector<int> result;
            int mult = 1;

            for(int i = 0; i < primes.size(); i++) {
                if(rnd.nextInt(10)) {
                    if(mult * primes[i] > many) {
                        break;
                    }
                    mult *= primes[i];
                    result.pb(primes[i]);
                }
            }
            result.pb(mult);
            return result;
        }

        // get square, so the answer will be a square
        int getSquare(int R, int C) {
            int many = R * C;

            int root = rnd.nextInt(1, sqrt(R * C));

            return root * root;
        }

        // answer it at (r1, c1) till (r2, c2)
        vector<string> answerDecidedGrid(int R, int C, int many, int r1, int c1, int r2, int c2, int magnitude = 10) {
            vector<string> res;

            magnitude = min(magnitude, many);
            vector<pair<int,int> > zeroGrid, oneGrid;

            for(int i = 1; i <= R; i++) {
                string tmp = "";
                for(int j = 1; j <= C; j++){
                    if(r1 <= i && i <= r2 && c1 <= j && j <= c2) {
                        tmp += "1";
                        oneGrid.pb({i - 1 ,j - 1});
                    }
                    else {
                        tmp += "0";
                        zeroGrid.pb({i - 1, j - 1});
                    }
                }
                res.pb(tmp);
            }

            magnitude = min(magnitude, (int)min(zeroGrid.size(), oneGrid.size()));
            rnd.shuffle(zeroGrid.begin(), zeroGrid.end());
            rnd.shuffle(oneGrid.begin(), oneGrid.end());

            for(int i = 0; i < magnitude; i++) {
                int a = zeroGrid[0].first, b = zeroGrid[0].second;
                int c = zeroGrid[1].first, d = zeroGrid[1].second;

                char tmp = res[a][b];
                res[a][b] = res[c][d];
                res[c][d] = tmp;
            }

            return res;
        }

        vector<string> flipFlopGrid(int R, int C) {
            vector<string> res;

            for(int i = 1; i <= R; i++) {
                string tmp = "";
                for(int j = 1; j <= C; j++) {
                    if((i + j) % 2 == 1) {
                        tmp += "1";
                    }
                    else{
                        tmp += "0";
                    }
                }
                res.pb(tmp);
            }

            return res;
        }

        vector<string> randomGrid(int R, int C, int many) {
            string ans = "";
            int mult = R * C;

            for(int i = 0;i  < many;i++) ans += "1";
            for(int i = many; i < mult; i++) ans += "0";

            rnd.shuffle(ans.begin(), ans.end());
            int ind = 0;

            vector<string> res;


            for(int i = 0; i < R; i++) {
                string tmp = "";
                for(int j = 0; j < C ;j ++) {
                    tmp += ans[ind];
                    ind++;
                }
                res.pb(tmp);
            }
            return res;
        }

};
