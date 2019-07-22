#include <tcframe/spec.hpp>
#include <bits/stdc++.h>
typedef long long ll;
using namespace tcframe;
using namespace std;

const int MAX = 1e9;

class ProblemSpec : public BaseProblemSpec {
protected:
    int R, C, Q;
    int Ax, Ay, Bx, By;

    void InputFormat() {
        LINE(R, C, Q);
        LINE(Ax, Ay);
        LINE(Bx, By);
    }

    void StyleConfig() {
        InteractiveEvaluator();
    }

    void Constraints() {
        CONS(1 <= R && R <= MAX);
        CONS(1 <= C && C <= MAX);
        CONS(1 <= Ax && Ax <= R);
        CONS(1 <= Bx && Bx <= R);
        CONS(1 <= Ay && Ay <= C);
        CONS(1 <= By && By <= C);
    }

    void Subtask1() {
        CONS(1 <= R && R <= 100);
        CONS(1 <= C && C <= 100);
        CONS(Ax == Bx);
        CONS(Ay == By);
        CONS(Q == 100);
    }

    void Subtask2() {
        CONS(Ax == Bx);
        CONS(Ay == By);
        CONS(Q == 5);
    }

    void Subtask3() {
        CONS(1 <= R && R <= 10);
        CONS(1 <= C && C <= 10);
        CONS(Q == 100);
    }

    void Subtask4() {
        CONS(1 <= R && R <= 50);
        CONS(1 <= C && C <= 50);
        CONS(Q == 100);
    }

    void Subtask5() {
        CONS(R == 1);
        CONS(Q == 5);
    }

    void Subtask6() {
        CONS(Q == 5);
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {

#define DISTINCT_CASE(...) distinctABCase([=] {__VA_ARGS__;})

protected:
    void SampleTestCase1() {
        Subtasks({6});
        Input({
            "4 5 5",
            "2 2",
            "3 5"
        });
    }

    void TestGroup1() {
        Subtasks({1, 3, 4});
        CASE(R = 10, C = 10, Q = 100, Ax = 1, Ay = 1, Bx = Ax, By = Ay);                    // ujung
        CASE(R = 10, C = 10, Q = 100, Ax = 1, Ay = C, Bx = Ax, By = Ay);
        CASE(R = 10, C = 10, Q = 100, Ax = R, Ay = 1, Bx = Ax, By = Ay);
        CASE(R = 10, C = 10, Q = 100, Ax = R, Ay = C, Bx = Ax, By = Ay);
        CASE(R = 10, C = 10, Q = 100, Ax = 1, Ay = rnd.nextInt(1, C), Bx = Ax, By = Ay);     // pinggir
        CASE(R = 10, C = 10, Q = 100, Ax = rnd.nextInt(1, R), Ay = C, Bx = Ax, By = Ay);
        CASE(R = 10, C = 10, Q = 100, Ax = R, Ay = rnd.nextInt(1, C), Bx = Ax, By = Ay);
        CASE(R = 10, C = 10, Q = 100, Ax = rnd.nextInt(1, R), Ay = 1, Bx = Ax, By = Ay);
        CASE(R = rnd.nextInt(1, 10), C = rnd.nextInt(1, 10), Q = 100, Ax = 1, Ay = 1, Bx = Ax, By = Ay);
        CASE(R = rnd.nextInt(1, 10), C = rnd.nextInt(1, 10), Q = 100, Ax = 1, Ay = C, Bx = Ax, By = Ay);
        CASE(R = rnd.nextInt(1, 10), C = rnd.nextInt(1, 10), Q = 100, Ax = R, Ay = 1, Bx = Ax, By = Ay);
        CASE(R = rnd.nextInt(1, 10), C = rnd.nextInt(1, 10), Q = 100, Ax = R, Ay = C, Bx = Ax, By = Ay);
        CASE(R = rnd.nextInt(1, 10), C = rnd.nextInt(1, 10), Q = 100, Ax = 1, Ay = rnd.nextInt(1, C), Bx = Ax, By = Ay);
        CASE(R = rnd.nextInt(1, 10), C = rnd.nextInt(1, 10), Q = 100, Ax = rnd.nextInt(1, R), Ay = C, Bx = Ax, By = Ay);
        CASE(R = rnd.nextInt(1, 10), C = rnd.nextInt(1, 10), Q = 100, Ax = R, Ay = rnd.nextInt(1, C), Bx = Ax, By = Ay);
        CASE(R = rnd.nextInt(1, 10), C = rnd.nextInt(1, 10), Q = 100, Ax = rnd.nextInt(1, R), Ay = 1, Bx = Ax, By = Ay);
        for (int i = 0; i < 6; i++){
            CASE(R = 10, C = 10, Q = 100, Ax = rnd.nextInt(1, R), Ay = rnd.nextInt(1, C), Bx = Ax, By = Ay);
            CASE(R = rnd.nextInt(1, 10), C = rnd.nextInt(1, 10), Q = 100,
                Ax = rnd.nextInt(1, R), Ay = rnd.nextInt(1, C), Bx = Ax, By = Ay);
        }
    }

    void TestGroup2() {
        Subtasks({1, 4});
        CASE(R = 50, C = 50, Q = 100, Ax = 1, Ay = 1, Bx = Ax, By = Ay);                    // ujung
        CASE(R = 50, C = 50, Q = 100, Ax = 1, Ay = C, Bx = Ax, By = Ay);
        CASE(R = 50, C = 50, Q = 100, Ax = R, Ay = 1, Bx = Ax, By = Ay);
        CASE(R = 50, C = 50, Q = 100, Ax = R, Ay = C, Bx = Ax, By = Ay);
        CASE(R = 50, C = 50, Q = 100, Ax = 1, Ay = rnd.nextInt(1, C), Bx = Ax, By = Ay);     // pinggir
        CASE(R = 50, C = 50, Q = 100, Ax = rnd.nextInt(1, R), Ay = C, Bx = Ax, By = Ay);
        CASE(R = 50, C = 50, Q = 100, Ax = R, Ay = rnd.nextInt(1, C), Bx = Ax, By = Ay);
        CASE(R = 50, C = 50, Q = 100, Ax = rnd.nextInt(1, R), Ay = 1, Bx = Ax, By = Ay);
        CASE(R = rnd.nextInt(11, 50), C = rnd.nextInt(11, 50), Q = 100, Ax = 1, Ay = 1, Bx = Ax, By = Ay);
        CASE(R = rnd.nextInt(11, 50), C = rnd.nextInt(11, 50), Q = 100, Ax = 1, Ay = C, Bx = Ax, By = Ay);
        CASE(R = rnd.nextInt(11, 50), C = rnd.nextInt(11, 50), Q = 100, Ax = R, Ay = 1, Bx = Ax, By = Ay);
        CASE(R = rnd.nextInt(11, 50), C = rnd.nextInt(11, 50), Q = 100, Ax = R, Ay = C, Bx = Ax, By = Ay);
        CASE(R = rnd.nextInt(11, 50), C = rnd.nextInt(11, 50), Q = 100, Ax = 1, Ay = rnd.nextInt(1, C), Bx = Ax, By = Ay);
        CASE(R = rnd.nextInt(11, 50), C = rnd.nextInt(11, 50), Q = 100, Ax = rnd.nextInt(1, R), Ay = C, Bx = Ax, By = Ay);
        CASE(R = rnd.nextInt(11, 50), C = rnd.nextInt(11, 50), Q = 100, Ax = R, Ay = rnd.nextInt(1, C), Bx = Ax, By = Ay);
        CASE(R = rnd.nextInt(11, 50), C = rnd.nextInt(11, 50), Q = 100, Ax = rnd.nextInt(1, R), Ay = 1, Bx = Ax, By = Ay);
        for (int i = 0; i < 6; i++){
            CASE(R = 50, C = 50, Q = 100, Ax = rnd.nextInt(1, R), Ay = rnd.nextInt(1, C), Bx = Ax, By = Ay);
            CASE(R = rnd.nextInt(11, 50), C = rnd.nextInt(11, 50), Q = 100,
                Ax = rnd.nextInt(1, R), Ay = rnd.nextInt(1, C), Bx = Ax, By = Ay);
        }
    }

    void TestGroup3() {
        Subtasks({1});
        CASE(R = 100, C = 100, Q = 100, Ax = 1, Ay = 1, Bx = Ax, By = Ay);                  // ujung
        CASE(R = 100, C = 100, Q = 100, Ax = 1, Ay = C, Bx = Ax, By = Ay);
        CASE(R = 100, C = 100, Q = 100, Ax = R, Ay = 1, Bx = Ax, By = Ay);
        CASE(R = 100, C = 100, Q = 100, Ax = R, Ay = C, Bx = Ax, By = Ay);
        CASE(R = 100, C = 100, Q = 100, Ax = 1, Ay = rnd.nextInt(1, C), Bx = Ax, By = Ay);   // pinggir
        CASE(R = 100, C = 100, Q = 100, Ax = rnd.nextInt(1, R), Ay = C, Bx = Ax, By = Ay);
        CASE(R = 100, C = 100, Q = 100, Ax = R, Ay = rnd.nextInt(1, C), Bx = Ax, By = Ay);
        CASE(R = 100, C = 100, Q = 100, Ax = rnd.nextInt(1, R), Ay = 1, Bx = Ax, By = Ay);
        CASE(R = rnd.nextInt(51, 100), C = rnd.nextInt(51, 100), Q = 100, Ax = 1, Ay = 1, Bx = Ax, By = Ay);
        CASE(R = rnd.nextInt(51, 100), C = rnd.nextInt(51, 100), Q = 100, Ax = 1, Ay = C, Bx = Ax, By = Ay);
        CASE(R = rnd.nextInt(51, 100), C = rnd.nextInt(51, 100), Q = 100, Ax = R, Ay = 1, Bx = Ax, By = Ay);
        CASE(R = rnd.nextInt(51, 100), C = rnd.nextInt(51, 100), Q = 100, Ax = R, Ay = C, Bx = Ax, By = Ay);
        CASE(R = rnd.nextInt(51, 100), C = rnd.nextInt(51, 100), Q = 100, Ax = 1, Ay = rnd.nextInt(1, C), Bx = Ax, By = Ay);
        CASE(R = rnd.nextInt(51, 100), C = rnd.nextInt(51, 100), Q = 100, Ax = rnd.nextInt(1, R), Ay = C, Bx = Ax, By = Ay);
        CASE(R = rnd.nextInt(51, 100), C = rnd.nextInt(51, 100), Q = 100, Ax = R, Ay = rnd.nextInt(1, C), Bx = Ax, By = Ay);
        CASE(R = rnd.nextInt(51, 100), C = rnd.nextInt(51, 100), Q = 100, Ax = rnd.nextInt(1, R), Ay = 1, Bx = Ax, By = Ay);
        for (int i = 0; i < 6; i++){
            CASE(R = 100, C = 100, Q = 100, Ax = rnd.nextInt(1, R), Ay = rnd.nextInt(1, C), Bx = Ax, By = Ay);
            CASE(R = rnd.nextInt(51, 100), C = rnd.nextInt(51, 100), Q = 100,
                Ax = rnd.nextInt(1, R), Ay = rnd.nextInt(1, C), Bx = Ax, By = Ay);
        }
    }

    void TestGroup4() {
        Subtasks({2, 5, 6});
        CASE(R = 1, C = MAX, Q = 5, Ax = 1, Ay = 1, Bx = Ax, By = Ay);                    // ujung
        CASE(R = 1, C = MAX, Q = 5, Ax = 1, Ay = C, Bx = Ax, By = Ay);
        CASE(R = 1, C = rnd.nextInt(1, MAX), Q = 5, Ax = 1, Ay = 1, Bx = Ax, By = Ay);
        CASE(R = 1, C = rnd.nextInt(1, MAX), Q = 5, Ax = 1, Ay = C, Bx = Ax, By = Ay);
        for (int i = 0; i < 8; i++){
            CASE(R = 1, C = MAX, Q = 5, Ax = 1, Ay = rnd.nextInt(1, C), Bx = Ax, By = Ay);
            CASE(R = 1, C = rnd.nextInt(1, MAX), Q = 5, Ax = 1, Ay = rnd.nextInt(1, C), Bx = Ax, By = Ay);
        }
    }
    
    void TestGroup5() {
        Subtasks({2, 6});
        CASE(R = MAX, C = MAX, Q = 5, Ax = 1, Ay = 1, Bx = Ax, By = Ay);                    // ujung
        CASE(R = MAX, C = MAX, Q = 5, Ax = 1, Ay = C, Bx = Ax, By = Ay);
        CASE(R = MAX, C = MAX, Q = 5, Ax = R, Ay = 1, Bx = Ax, By = Ay);
        CASE(R = MAX, C = MAX, Q = 5, Ax = R, Ay = C, Bx = Ax, By = Ay);
        CASE(R = MAX, C = MAX, Q = 5, Ax = 1, Ay = rnd.nextInt(1, C), Bx = Ax, By = Ay);     // pinggir
        CASE(R = MAX, C = MAX, Q = 5, Ax = rnd.nextInt(1, R), Ay = C, Bx = Ax, By = Ay);
        CASE(R = MAX, C = MAX, Q = 5, Ax = R, Ay = rnd.nextInt(1, C), Bx = Ax, By = Ay);
        CASE(R = MAX, C = MAX, Q = 5, Ax = rnd.nextInt(1, R), Ay = 1, Bx = Ax, By = Ay);
        CASE(R = rnd.nextInt(2, MAX), C = rnd.nextInt(2, MAX), Q = 5, Ax = 1, Ay = 1, Bx = Ax, By = Ay);
        CASE(R = rnd.nextInt(2, MAX), C = rnd.nextInt(2, MAX), Q = 5, Ax = 1, Ay = C, Bx = Ax, By = Ay);
        CASE(R = rnd.nextInt(2, MAX), C = rnd.nextInt(2, MAX), Q = 5, Ax = R, Ay = 1, Bx = Ax, By = Ay);
        CASE(R = rnd.nextInt(2, MAX), C = rnd.nextInt(2, MAX), Q = 5, Ax = R, Ay = C, Bx = Ax, By = Ay);
        CASE(R = rnd.nextInt(2, MAX), C = rnd.nextInt(2, MAX), Q = 5, Ax = 1, Ay = rnd.nextInt(1, C), Bx = Ax, By = Ay);
        CASE(R = rnd.nextInt(2, MAX), C = rnd.nextInt(2, MAX), Q = 5, Ax = rnd.nextInt(1, R), Ay = C, Bx = Ax, By = Ay);
        CASE(R = rnd.nextInt(2, MAX), C = rnd.nextInt(2, MAX), Q = 5, Ax = R, Ay = rnd.nextInt(1, C), Bx = Ax, By = Ay);
        CASE(R = rnd.nextInt(2, MAX), C = rnd.nextInt(2, MAX), Q = 5, Ax = rnd.nextInt(1, R), Ay = 1, Bx = Ax, By = Ay);
        for (int i = 0; i < 8; i++){
            CASE(R = MAX, C = MAX, Q = 5, Ax = rnd.nextInt(1, R), Ay = rnd.nextInt(1, C), Bx = Ax, By = Ay);
            CASE(R = rnd.nextInt(1, MAX), C = rnd.nextInt(1, MAX), Q = 5,
                Ax = rnd.nextInt(1, R), Ay = rnd.nextInt(1, C), Bx = Ax, By = Ay);
        }
    }

    void TestGroup6() {
        Subtasks({3, 4});
        DISTINCT_CASE(R = 10, C = 10, Q = 100, Ax = 1, Ay = 1, Bx = 1, By = C);      // 2 ujung
        DISTINCT_CASE(R = 10, C = 10, Q = 100, Ax = 1, Ay = 1, Bx = R, By = 1);
        DISTINCT_CASE(R = 10, C = 10, Q = 100, Ax = 1, Ay = 1, Bx = R, By = C);
        DISTINCT_CASE(R = 10, C = 10, Q = 100, Ax = 1, Ay = C, Bx = 1, By = 1);
        DISTINCT_CASE(R = 10, C = 10, Q = 100, Ax = 1, Ay = C, Bx = R, By = 1);
        DISTINCT_CASE(R = 10, C = 10, Q = 100, Ax = 1, Ay = C, Bx = R, By = C);
        DISTINCT_CASE(R = 10, C = 10, Q = 100, Ax = R, Ay = 1, Bx = 1, By = 1);
        DISTINCT_CASE(R = 10, C = 10, Q = 100, Ax = R, Ay = 1, Bx = 1, By = C);
        DISTINCT_CASE(R = 10, C = 10, Q = 100, Ax = R, Ay = 1, Bx = R, By = C);
        DISTINCT_CASE(R = 10, C = 10, Q = 100, Ax = R, Ay = C, Bx = 1, By = 1);
        DISTINCT_CASE(R = 10, C = 10, Q = 100, Ax = R, Ay = C, Bx = 1, By = C);
        DISTINCT_CASE(R = 10, C = 10, Q = 100, Ax = R, Ay = C, Bx = R, By = 1);
        DISTINCT_CASE(R = 10, C = 10, Q = 100, Ax = 1, Ay = 1, Bx = rnd.nextInt(1, R), By = rnd.nextInt(1, C));    // ujung + bebas
        DISTINCT_CASE(R = 10, C = 10, Q = 100, Ax = 1, Ay = C, Bx = rnd.nextInt(1, R), By = rnd.nextInt(1, C));
        DISTINCT_CASE(R = 10, C = 10, Q = 100, Ax = R, Ay = 1, Bx = rnd.nextInt(1, R), By = rnd.nextInt(1, C));
        DISTINCT_CASE(R = 10, C = 10, Q = 100, Ax = R, Ay = C, Bx = rnd.nextInt(1, R), By = rnd.nextInt(1, C));
        DISTINCT_CASE(R = 10, C = 10, Q = 100, Ax = 1, Ay = rnd.nextInt(1, C), Bx = rnd.nextInt(1, R), By = C);    // 2 pinggir
        DISTINCT_CASE(R = 10, C = 10, Q = 100, Ax = 1, Ay = rnd.nextInt(1, C), Bx = R, By = rnd.nextInt(1, C));
        DISTINCT_CASE(R = 10, C = 10, Q = 100, Ax = 1, Ay = rnd.nextInt(1, C), Bx = rnd.nextInt(1, R), By = 1);
        DISTINCT_CASE(R = 10, C = 10, Q = 100, Ax = rnd.nextInt(1, R), Ay = C, Bx = 1, By = rnd.nextInt(1, C));
        DISTINCT_CASE(R = 10, C = 10, Q = 100, Ax = rnd.nextInt(1, R), Ay = C, Bx = R, By = rnd.nextInt(1, C));
        DISTINCT_CASE(R = 10, C = 10, Q = 100, Ax = rnd.nextInt(1, R), Ay = C, Bx = rnd.nextInt(1, R), By = 1);
        DISTINCT_CASE(R = 10, C = 10, Q = 100, Ax = R, Ay = rnd.nextInt(1, C), Bx = 1, By = rnd.nextInt(1, C));
        DISTINCT_CASE(R = 10, C = 10, Q = 100, Ax = R, Ay = rnd.nextInt(1, C), Bx = rnd.nextInt(1, R), By = C);
        DISTINCT_CASE(R = 10, C = 10, Q = 100, Ax = R, Ay = rnd.nextInt(1, C), Bx = rnd.nextInt(1, R), By = 1);
        DISTINCT_CASE(R = 10, C = 10, Q = 100, Ax = 1, Ay = rnd.nextInt(1, C), Bx = 1, By = rnd.nextInt(1, C));
        DISTINCT_CASE(R = 10, C = 10, Q = 100, Ax = rnd.nextInt(1, R), Ay = 1, Bx = rnd.nextInt(1, R), By = C);
        DISTINCT_CASE(R = 10, C = 10, Q = 100, Ax = rnd.nextInt(1, R), Ay = 1, Bx = R, By = rnd.nextInt(1, C));
        DISTINCT_CASE(R = 10, C = 10, Q = 100, Ax = rnd.nextInt(1, R), Ay = 1, Bx = rnd.nextInt(1, R), By = rnd.nextInt(1, C)); // pinggir
        DISTINCT_CASE(R = 10, C = 10, Q = 100, Ax = rnd.nextInt(1, R), Ay = C, Bx = rnd.nextInt(1, R), By = rnd.nextInt(1, C)); // + bebas
        DISTINCT_CASE(R = 10, C = 10, Q = 100, Ax = R, Ay = rnd.nextInt(1, C), Bx = rnd.nextInt(1, R), By = rnd.nextInt(1, C));
        DISTINCT_CASE(R = 10, C = 10, Q = 100, Ax = rnd.nextInt(1, R), Ay = 1, Bx = rnd.nextInt(1, R), By = rnd.nextInt(1, C));
        for (int i = 0; i < 8; i++){
            DISTINCT_CASE(R = rnd.nextInt(1, 10), C = rnd.nextInt(1, 10), Q = 100,                                              // bebas
                Ax = rnd.nextInt(1, R), Ay = rnd.nextInt(1, C), Bx = rnd.nextInt(1, R), By = rnd.nextInt(1, C));
        }
        for (int i = 0; i < 4; i++){
            DISTINCT_CASE(R = 10, C = 10, Q = 100, Ax = rnd.nextInt(2, R), Ay = rnd.nextInt(1, C), Bx = Ax-1, By = Ay);         // berse-
            DISTINCT_CASE(R = 10, C = 10, Q = 100, Ax = rnd.nextInt(1, R), Ay = rnd.nextInt(1, C-1), Bx = Ax, By = Ay+1);       // belahan
            DISTINCT_CASE(R = 10, C = 10, Q = 100, Ax = rnd.nextInt(1, R-1), Ay = rnd.nextInt(1, C), Bx = Ax+1, By = Ay);
            DISTINCT_CASE(R = 10, C = 10, Q = 100, Ax = rnd.nextInt(1, R), Ay = rnd.nextInt(2, C), Bx = Ax, By = Ay-1);
        }
        for (int i = 0; i < 4; i++){
            DISTINCT_CASE(R = 10, C = 10, Q = 100, Ax = rnd.nextInt(2, R), Ay = rnd.nextInt(2, C), Bx = Ax-1, By = Ay-1);       // dia-
            DISTINCT_CASE(R = 10, C = 10, Q = 100, Ax = rnd.nextInt(2, R), Ay = rnd.nextInt(1, C-1), Bx = Ax-1, By = Ay+1);     // gonal
            DISTINCT_CASE(R = 10, C = 10, Q = 100, Ax = rnd.nextInt(1, R-1), Ay = rnd.nextInt(2, C), Bx = Ax+1, By = Ay-1);
            DISTINCT_CASE(R = 10, C = 10, Q = 100, Ax = rnd.nextInt(1, R-1), Ay = rnd.nextInt(1, C-1), Bx = Ax+1, By = Ay+1);
        }
        for (int i = 0; i < 8; i++){
            for (int j = i+1; j < 9; j++){
                CASE(R = 3, C = 3, Q = 100, Ax = i/3+1, Ay = i%3+1, Bx = j/3+1, By = j%3+1);
            }
        }
    }
    
    void TestGroup7() {
        Subtasks({4});
        DISTINCT_CASE(R = 50, C = 50, Q = 100, Ax = 1, Ay = 1, Bx = 1, By = C);      // 2 ujung
        DISTINCT_CASE(R = 50, C = 50, Q = 100, Ax = 1, Ay = 1, Bx = R, By = 1);
        DISTINCT_CASE(R = 50, C = 50, Q = 100, Ax = 1, Ay = 1, Bx = R, By = C);
        DISTINCT_CASE(R = 50, C = 50, Q = 100, Ax = 1, Ay = C, Bx = 1, By = 1);
        DISTINCT_CASE(R = 50, C = 50, Q = 100, Ax = 1, Ay = C, Bx = R, By = 1);
        DISTINCT_CASE(R = 50, C = 50, Q = 100, Ax = 1, Ay = C, Bx = R, By = C);
        DISTINCT_CASE(R = 50, C = 50, Q = 100, Ax = R, Ay = 1, Bx = 1, By = 1);
        DISTINCT_CASE(R = 50, C = 50, Q = 100, Ax = R, Ay = 1, Bx = 1, By = C);
        DISTINCT_CASE(R = 50, C = 50, Q = 100, Ax = R, Ay = 1, Bx = R, By = C);
        DISTINCT_CASE(R = 50, C = 50, Q = 100, Ax = R, Ay = C, Bx = 1, By = 1);
        DISTINCT_CASE(R = 50, C = 50, Q = 100, Ax = R, Ay = C, Bx = 1, By = C);
        DISTINCT_CASE(R = 50, C = 50, Q = 100, Ax = R, Ay = C, Bx = R, By = 1);
        DISTINCT_CASE(R = 50, C = 50, Q = 100, Ax = 1, Ay = 1, Bx = rnd.nextInt(1, R), By = rnd.nextInt(1, C));    // ujung + bebas
        DISTINCT_CASE(R = 50, C = 50, Q = 100, Ax = 1, Ay = C, Bx = rnd.nextInt(1, R), By = rnd.nextInt(1, C));
        DISTINCT_CASE(R = 50, C = 50, Q = 100, Ax = R, Ay = 1, Bx = rnd.nextInt(1, R), By = rnd.nextInt(1, C));
        DISTINCT_CASE(R = 50, C = 50, Q = 100, Ax = R, Ay = C, Bx = rnd.nextInt(1, R), By = rnd.nextInt(1, C));
        DISTINCT_CASE(R = 50, C = 50, Q = 100, Ax = 1, Ay = rnd.nextInt(1, C), Bx = rnd.nextInt(1, R), By = rnd.nextInt(1, C)); // pinggir
        DISTINCT_CASE(R = 50, C = 50, Q = 100, Ax = rnd.nextInt(1, R), Ay = C, Bx = rnd.nextInt(1, R), By = rnd.nextInt(1, C)); // + bebas
        DISTINCT_CASE(R = 50, C = 50, Q = 100, Ax = R, Ay = rnd.nextInt(1, C), Bx = rnd.nextInt(1, R), By = rnd.nextInt(1, C));
        DISTINCT_CASE(R = 50, C = 50, Q = 100, Ax = rnd.nextInt(1, R), Ay = 1, Bx = rnd.nextInt(1, R), By = rnd.nextInt(1, C));
        for (int i = 0; i < 8; i++){                                                                                   // bebas
            DISTINCT_CASE(R = rnd.nextInt(11, 50), C = rnd.nextInt(11, 50), Q = 100,
                Ax = rnd.nextInt(1, R), Ay = rnd.nextInt(1, C), Bx = rnd.nextInt(1, R), By = rnd.nextInt(1, C));
        }
    }

    void TestGroup8() {
        Subtasks({5, 6});
        DISTINCT_CASE(R = 1, C = MAX, Q = 5, Ax = 1, Ay = 1, Bx = 1, By = rnd.nextInt(1, C));                    // pol
        DISTINCT_CASE(R = 1, C = MAX, Q = 5, Ax = 1, Ay = C, Bx = 1, By = rnd.nextInt(1, C));
        DISTINCT_CASE(R = 1, C = MAX, Q = 5, Ax = 1, Ay = 1, Bx = 1, By = C);
        DISTINCT_CASE(R = 1, C = rnd.nextInt(1, MAX), Q = 5, Ax = 1, Ay = 1, Bx = 1, By = rnd.nextInt(1, C));    // random
        DISTINCT_CASE(R = 1, C = rnd.nextInt(1, MAX), Q = 5, Ax = 1, Ay = C, Bx = 1, By = rnd.nextInt(1, C));
        DISTINCT_CASE(R = 1, C = rnd.nextInt(1, MAX), Q = 5, Ax = 1, Ay = 1, Bx = 1, By = C);
        for (int i = 0; i < 8; i++){
            DISTINCT_CASE(R = 1, C = MAX, Q = 5, Ax = 1, Ay = rnd.nextInt(1, C), Bx = 1, By = rnd.nextInt(1, C));
            DISTINCT_CASE(R = 1, C = rnd.nextInt(1, C), Q = 5, Ax = 1, Ay = rnd.nextInt(1, C), Bx = 1, By = rnd.nextInt(1, C));
        }
    }
    
    void TestGroup9() {
        Subtasks({6});
        DISTINCT_CASE(R = MAX, C = MAX, Q = 5, Ax = 1, Ay = 1, Bx = 1, By = C);      // 2 ujung
        DISTINCT_CASE(R = MAX, C = MAX, Q = 5, Ax = 1, Ay = 1, Bx = R, By = 1);
        DISTINCT_CASE(R = MAX, C = MAX, Q = 5, Ax = 1, Ay = 1, Bx = R, By = C);
        DISTINCT_CASE(R = MAX, C = MAX, Q = 5, Ax = 1, Ay = C, Bx = 1, By = 1);
        DISTINCT_CASE(R = MAX, C = MAX, Q = 5, Ax = 1, Ay = C, Bx = R, By = 1);
        DISTINCT_CASE(R = MAX, C = MAX, Q = 5, Ax = 1, Ay = C, Bx = R, By = C);
        DISTINCT_CASE(R = MAX, C = MAX, Q = 5, Ax = R, Ay = 1, Bx = 1, By = 1);
        DISTINCT_CASE(R = MAX, C = MAX, Q = 5, Ax = R, Ay = 1, Bx = 1, By = C);
        DISTINCT_CASE(R = MAX, C = MAX, Q = 5, Ax = R, Ay = 1, Bx = R, By = C);
        DISTINCT_CASE(R = MAX, C = MAX, Q = 5, Ax = R, Ay = C, Bx = 1, By = 1);
        DISTINCT_CASE(R = MAX, C = MAX, Q = 5, Ax = R, Ay = C, Bx = 1, By = C);
        DISTINCT_CASE(R = MAX, C = MAX, Q = 5, Ax = R, Ay = C, Bx = R, By = 1);
        DISTINCT_CASE(R = MAX, C = MAX, Q = 5, Ax = 1, Ay = 1, Bx = rnd.nextInt(1, R), By = rnd.nextInt(1, C));    // ujung + bebas
        DISTINCT_CASE(R = MAX, C = MAX, Q = 5, Ax = 1, Ay = C, Bx = rnd.nextInt(1, R), By = rnd.nextInt(1, C));
        DISTINCT_CASE(R = MAX, C = MAX, Q = 5, Ax = R, Ay = 1, Bx = rnd.nextInt(1, R), By = rnd.nextInt(1, C));
        DISTINCT_CASE(R = MAX, C = MAX, Q = 5, Ax = R, Ay = C, Bx = rnd.nextInt(1, R), By = rnd.nextInt(1, C));
        DISTINCT_CASE(R = MAX, C = MAX, Q = 5, Ax = 1, Ay = rnd.nextInt(1, C), Bx = rnd.nextInt(1, R), By = rnd.nextInt(1, C)); // pinggir
        DISTINCT_CASE(R = MAX, C = MAX, Q = 5, Ax = rnd.nextInt(1, R), Ay = C, Bx = rnd.nextInt(1, R), By = rnd.nextInt(1, C)); // + bebas
        DISTINCT_CASE(R = MAX, C = MAX, Q = 5, Ax = R, Ay = rnd.nextInt(1, C), Bx = rnd.nextInt(1, R), By = rnd.nextInt(1, C));
        DISTINCT_CASE(R = MAX, C = MAX, Q = 5, Ax = rnd.nextInt(1, R), Ay = 1, Bx = rnd.nextInt(1, R), By = rnd.nextInt(1, C));
        for (int i = 0; i < 8; i++){                                                                                   // bebas
            DISTINCT_CASE(R = rnd.nextInt(1, MAX), C = rnd.nextInt(1, MAX), Q = 5,
                Ax = rnd.nextInt(1, R), Ay = rnd.nextInt(1, C), Bx = rnd.nextInt(1, R), By = rnd.nextInt(1, C));
        }
        for (int i = 0; i < 8; i++){
            for (int j = i+1; j < 9; j++){
                CASE(R = 3, C = 3, Q = 5, Ax = i/3+1, Ay = i%3+1, Bx = j/3+1, By = j%3+1);
            }
        }
        CASE(R = 10, C = 10, Q = 5, Ax = 3, Ay = 1, Bx = 10, By = 7);
        CASE(R = 10, C = 10, Q = 5, Ax = 8, Ay = 1, Bx = 7, By = 1);
        CASE(R = 10, C = 10, Q = 5, Ax = 4, Ay = 1, Bx = 3, By = 1);
    }

private:
    void distinctABCase(function<void()> testcase) {
        testcase();

        while (Ax == Bx && Ay == By) {
            testcase();
        }
        int _R = R;
        int _C = C;
        int _Q = Q;
        int _Ax = Ax;
        int _Ay = Ay;
        int _Bx = Bx;
        int _By = By;
        CASE(R = _R, C = _C, Q = _Q, Ax = _Ax, Bx = _Bx, Ay = _Ay, By = _By);
    }
    
};
