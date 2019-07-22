#include <tcframe/runner.hpp>
using namespace tcframe;

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN=2E5;
const int MAXM=2E5;
const int MAXS=1E6;
const int MAXP=1E6;

class ProblemSpec : public BaseProblemSpec {
protected:
	int N,M;
	int S;
	vector<int> A,B,P;
	
	ll ANS;

	void InputFormat() {
		LINE(N,M,S);
		LINES(A,B,P)%SIZE(M);
	}

	void OutputFormat() {
		LINE(ANS);
	}

	void StyleConfig() {
		CustomScorer();
	}

	void Constraints() {
		CONS(between(N,1,MAXN));
		CONS(between(M,1,MAXM));
		CONS(between(S,1,MAXS));
		CONS(allBetween(A,1,MAXN));
		CONS(allBetween(B,1,MAXN));
		CONS(validAB(A,B));
		CONS(allBetween(P,1,MAXP));
	}

	void Subtask1() {	//open subtask 1
		CONS(N==1001);
		CONS(M==1);
		CONS(S==999);
		CONS(A==vector<int>({1}));
		CONS(B==vector<int>({1001}));
		CONS(P==vector<int>({1000000}));
	}

	void Subtask2() {	//open subtask 2
		CONS(N==16);
		CONS(M==7);
		CONS(S==10);
		CONS(A==vector<int>({1,2,5,7,11,12,15}));
		CONS(B==vector<int>({6,4,10,9,15,14,16}));
		CONS(P==vector<int>({17,8,30,22,47,28,18}));
	}

	void Subtask3() {
		CONS(N<=200);
		CONS(M<=16);
	}
	
	void Subtask4() {
		CONS(N<=200);
		CONS(M<=200);
	}
	
	void Subtask5() {
		CONS(N<=2000);
		CONS(M<=2000);
	}
	
	void Subtask6() {
		CONS(allBetween(P,S,S));
	}
	
	void Subtask7() {
	}

private:
	bool between(int x,int l,int r) {
		return (l<=x && x<=r);
	}
	bool allBetween(vector<int> &x,int l,int r) {
		for (auto data:x) if (!between(data,l,r)) return false; return true;
	}
	bool validAB(vector<int> &a,vector<int> &b) {
		for (int i=0;i<a.size();i++) if (a[i]>b[i]) return false; return true;
	}
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:

	void SampleTestCase1() {
		Subtasks({3,4,5,7});
		Input({
			"5 3 3",
			"1 2 2",
			"4 5 1",
			"2 4 10"
		});
		Output({"6"});
	}
	
	void SampleTestCase2() {
		Subtasks({3,4,5,7});
		Input({
			"5 3 3",
			"1 2 2",
			"4 5 1",
			"2 4 2"
		});
		Output({"5"});
	}

	void BeforeTestCase() {
		A.clear(); B.clear(); P.clear();
	}

	void TestGroup1() {	//open subtask 1
		Subtasks({1,5,7});
		CASE(
			N=1001,M=1,S=999,
			A={1},
			B={1001},
			P={1000000}
		);
	}

	void TestGroup2() {	//open subtask 2
		Subtasks({2,3,4,5,7});
		CASE(
			N=16,M=7,S=10,
			A={1,2,5,7,11,12,15},
			B={6,4,10,9,15,14,16},
			P={17,8,30,22,47,28,18}
		);
	}

	void TestGroup3() {	//N<=200, M<=16, P[i]=S
		Subtasks({3,4,5,6,7});
		CASE(
			N=1,M=1,S=1,
			A={1},
			B={1},
			P={1}
		);
		CASE(
			N=200,M=1,S=1,
			A={1},
			B={1},
			P={1}
		);
		CASE(
			N=20,M=5,S=1,
			A={3,4,5,12,19},
			B={12,11,13,14,20},
			randomVector(P,M,S,S),
			reordering(A,B,P)
		);
		
		CASE(
			N=200,M=16,S=rnd.nextInt(1,MAXS),
			AB_RandomWithRangeSize(A,B,M,1,N,0,10),
			randomVector(P,M,S,S)
		);
		CASE(
			N=200,M=16,S=rnd.nextInt(1,MAXS),
			AB_RandomWithRangeSize(A,B,M,1,N,50,150),
			randomVector(P,M,S,S)
		);
		CASE(
			N=200,M=16,S=rnd.nextInt(1,MAXS),
			AB_RandomWithRangeSize(A,B,M,1,N,100,100),
			randomVector(P,M,S,S)
		);
		
		CASE(
			N=rnd.nextInt(1,200),M=rnd.nextInt(1,16),S=rnd.nextInt(1,MAXS),
			AB_Random(A,B,M,1,N),
			randomVector(P,M,S,S)
		);
		CASE(
			N=200,M=16,S=rnd.nextInt(1,MAXS),
			AB_Random(A,B,M,1,N),
			randomVector(P,M,S,S)
		);
	}
	
	void TestGroup4() {	//N<=200, M<=16
		Subtasks({3,4,5,7});
		CASE(
			N=200,M=1,S=1,
			A={1},
			B={200},
			P={199}
		);
		CASE(
			N=200,M=1,S=1,
			A={1},
			B={200},
			P={201}
		);
		CASE(
			N=200,M=2,S=100,
			A={1,2},
			B={199,200},
			P={101,101}
		);
		CASE(
			N=4,M=4,S=10,
			A={2,2,2,2},
			B={3,3,3,3},
			P={3,2,2,3}
		);
		for (int i=0,s=100;i<3;i++,s*=10) CASE(
			N=6,M=3,S=s,
			A={1,2,3},
			B={6,5,4},
			P={10000,1000,100},
			reordering(A,B,P)
		);
		//A[i]=B[i]
		CASE(
			N=200,M=16,S=rnd.nextInt(1,MAXS),
			AB_RandomWithRangeSize(A,B,M,1,N,0,0),
			randomVector(P,M,1,S)
		);
		//All possible pairs of (A,B)
		CASE(
			N=5,M=N*(N-1)/2,S=rnd.nextInt(MAXS-10,MAXS),
			AB_AllCombination(A,B,N),
			P_BasedOnRange(P,M,rnd.nextInt(1,MAXP/N),A,B),
			reordering(A,B,P)
		);
		CASE(
			N=5,M=N*(N-1)/2,S=rnd.nextInt(1,MAXS/N),
			AB_AllCombination(A,B,N),
			P_BasedOnRange(P,M,S,A,B),
			reordering(A,B,P)
		);
		//Very large S, random P
		CASE(
			N=200,M=16,S=rnd.nextInt(MAXS-10,MAXS),
			AB_RandomWithRangeSize(A,B,M,1,N,0,10),
			randomVector(P,M,1,10)
		);
		CASE(
			N=200,M=16,S=rnd.nextInt(MAXS-10,MAXS),
			AB_RandomWithRangeSize(A,B,M,1,N,50,150),
			randomVector(P,M,1,10)
		);
		CASE(
			N=200,M=16,S=rnd.nextInt(MAXS-10,MAXS),
			AB_RandomWithRangeSize(A,B,M,1,N,100,100),
			randomVector(P,M,1,10)
		);
		//Very large S, P scale based on range size
		CASE(
			N=200,M=16,S=rnd.nextInt(MAXS-10,MAXS),
			AB_RandomWithRangeSize(A,B,M,1,N,0,10),
			P_BasedOnRange(P,M,rnd.nextInt(1,MAXP/N),A,B)
		);
		CASE(
			N=200,M=16,S=rnd.nextInt(MAXS-10,MAXS),
			AB_RandomWithRangeSize(A,B,M,1,N,50,150),
			P_BasedOnRange(P,M,rnd.nextInt(1,MAXP/N),A,B)
		);
		CASE(
			N=200,M=16,S=rnd.nextInt(MAXS-10,MAXS),
			AB_Random(A,B,M,1,N),
			P_BasedOnRange(P,M,rnd.nextInt(1,MAXP/N),A,B)
		);
		//Use large range only will be slightly more expensive than the answer
		CASE(
			N=200,M=16,S=2,
			AB_RandomWithRangeSize(A,B,M-3,1,N,0,10),
			AB_RandomWithRangeSize(A,B,3,1,N,N-10,N-1),
			randomVector(P,M-3,1,3),
			randomVector(P,3,N-10,N)
		);
		//P is slightly larger than S
		CASE(
			N=200,M=16,S=rnd.nextInt(1,MAXS-10),
			AB_RandomWithRangeSize(A,B,M,1,N,50,150),
			randomVector(P,M,S,S+10)
		);
		CASE(
			N=200,M=16,S=rnd.nextInt(1,MAXS-10),
			AB_Random(A,B,M,1,N),
			randomVector(P,M,S,S+10)
		);
		//Normal
		CASE(
			N=200,M=16,S=rnd.nextInt(1,MAXS/N),
			AB_RandomWithRangeSize(A,B,M,1,N,0,10),
			P_BasedOnRange(P,M,S,A,B)
		);
		CASE(
			N=200,M=16,S=rnd.nextInt(1,MAXS/N),
			AB_RandomWithRangeSize(A,B,M,1,N,50,150),
			P_BasedOnRange(P,M,S,A,B)
		);
		CASE(
			N=200,M=16,S=rnd.nextInt(1,MAXS),
			AB_RandomWithRangeSize(A,B,M,1,N,0,10),
			randomVector(P,M,1,MAXP)
		);
		CASE(
			N=200,M=16,S=rnd.nextInt(1,MAXS),
			AB_RandomWithRangeSize(A,B,M,1,N,50,150),
			randomVector(P,M,1,MAXP)
		);
		CASE(
			N=200,M=16,S=rnd.nextInt(1,MAXS),
			AB_Random(A,B,M,1,N),
			randomVector(P,M,1,MAXP)
		);
		CASE(
			N=200,M=16,S=rnd.nextInt(1,MAXS/N),
			AB_Random(A,B,M,1,N),
			P_BasedOnRange(P,M,S,A,B)
		);
		CASE(
			N=200,M=16,S=rnd.nextInt(1,MAXS),
			AB_DuplicateRange(A,B,M,M/3,1,N),
			randomVector(P,M,1,MAXP),
			reordering(A,B,P)
		);
	}
	
	void TestGroup5() {	//N<=200, M<=200, P[i]=S
		Subtasks({4,5,6,7});
		CASE(
			N=200,M=200,S=rnd.nextInt(1,MAXS),
			AB_RandomWithRangeSize(A,B,M,1,N,0,10),
			randomVector(P,M,S,S)
		);
		CASE(
			N=200,M=200,S=rnd.nextInt(1,MAXS),
			AB_RandomWithRangeSize(A,B,M,1,N,50,150),
			randomVector(P,M,S,S)
		);
		CASE(
			N=200,M=200,S=rnd.nextInt(1,MAXS),
			AB_RandomWithRangeSize(A,B,M,1,N,10,10),
			randomVector(P,M,S,S)
		);
		
		CASE(
			N=rnd.nextInt(1,200),M=rnd.nextInt(17,200),S=rnd.nextInt(1,MAXS),
			AB_Random(A,B,M,1,N),
			randomVector(P,M,S,S)
		);
		CASE(
			N=200,M=200,S=rnd.nextInt(1,MAXS),
			AB_Random(A,B,M,1,N),
			randomVector(P,M,S,S)
		);
	}
	
	void TestGroup6() {	//N<=200, M<=200
		Subtasks({4,5,7});
		//A[i]=B[i]
		CASE(
			N=200,M=200,S=rnd.nextInt(1,MAXS),
			AB_RandomWithRangeSize(A,B,M,1,N,0,0),
			randomVector(P,M,1,S)
		);
		//All possible pairs of (A,B)
		CASE(
			N=20,M=N*(N-1)/2,S=rnd.nextInt(MAXS-10,MAXS),
			AB_AllCombination(A,B,N),
			P_BasedOnRange(P,M,rnd.nextInt(1,MAXP/N),A,B),
			reordering(A,B,P)
		);
		CASE(
			N=20,M=N*(N-1)/2,S=rnd.nextInt(1,MAXS/N),
			AB_AllCombination(A,B,N),
			P_BasedOnRange(P,M,S,A,B),
			reordering(A,B,P)
		);
		//Very large S, random P
		CASE(
			N=200,M=200,S=rnd.nextInt(MAXS-10,MAXS),
			AB_RandomWithRangeSize(A,B,M,1,N,0,10),
			randomVector(P,M,1,10)
		);
		CASE(
			N=200,M=200,S=rnd.nextInt(MAXS-10,MAXS),
			AB_RandomWithRangeSize(A,B,M,1,N,50,150),
			randomVector(P,M,1,10)
		);
		CASE(
			N=200,M=200,S=rnd.nextInt(MAXS-10,MAXS),
			AB_RandomWithRangeSize(A,B,M,1,N,10,10),
			randomVector(P,M,1,10)
		);
		CASE(
			N=200,M=200,S=rnd.nextInt(MAXS-10,MAXS),
			AB_RandomWithRangeSize(A,B,M,1,N,M/2,M/2),
			randomVector(P,M,1,10)
		);
		//Very large S, P scale based on range size
		CASE(
			N=200,M=200,S=rnd.nextInt(MAXS-10,MAXS),
			AB_RandomWithRangeSize(A,B,M,1,N,0,10),
			P_BasedOnRange(P,M,rnd.nextInt(1,MAXP/N),A,B)
		);
		CASE(
			N=200,M=200,S=rnd.nextInt(MAXS-10,MAXS),
			AB_RandomWithRangeSize(A,B,M,1,N,50,150),
			P_BasedOnRange(P,M,rnd.nextInt(1,MAXP/N),A,B)
		);
		CASE(
			N=200,M=200,S=rnd.nextInt(MAXS-10,MAXS),
			AB_Random(A,B,M,1,N),
			P_BasedOnRange(P,M,rnd.nextInt(1,MAXP/N),A,B)
		);
		//Use large range only will be slightly more expensive than the answer
		CASE(
			N=200,M=200,S=2,
			AB_RandomWithRangeSize(A,B,M-10,1,N,0,10),
			AB_RandomWithRangeSize(A,B,10,1,N,N-10,N-1),
			randomVector(P,M-10,1,3),
			randomVector(P,10,N-10,N)
		);
		//P is slightly larger than S
		CASE(
			N=200,M=200,S=rnd.nextInt(1,MAXS-10),
			AB_RandomWithRangeSize(A,B,M,1,N,0,10),
			randomVector(P,M,S,S+10)
		);
		CASE(
			N=200,M=200,S=rnd.nextInt(1,MAXS-10),
			AB_RandomWithRangeSize(A,B,M,1,N,50,150),
			randomVector(P,M,S,S+10)
		);
		CASE(
			N=200,M=200,S=rnd.nextInt(1,MAXS-10),
			AB_Random(A,B,M,1,N),
			randomVector(P,M,S,S+10)
		);
		//Normal
		CASE(
			N=200,M=200,S=rnd.nextInt(1,MAXS/N),
			AB_RandomWithRangeSize(A,B,M,1,N,0,10),
			P_BasedOnRange(P,M,S,A,B)
		);
		CASE(
			N=200,M=200,S=rnd.nextInt(1,MAXS/N),
			AB_RandomWithRangeSize(A,B,M,1,N,50,150),
			P_BasedOnRange(P,M,S,A,B)
		);
		CASE(
			N=200,M=rnd.nextInt(17,200),S=rnd.nextInt(1,MAXS),
			AB_Random(A,B,M,1,N),
			randomVector(P,M,1,MAXP)
		);
		CASE(
			N=200,M=rnd.nextInt(17,200),S=rnd.nextInt(1,MAXS/N),
			AB_Random(A,B,M,1,N),
			P_BasedOnRange(P,M,S,A,B)
		);
		CASE(
			N=200,M=200,S=rnd.nextInt(1,MAXS),
			AB_Random(A,B,M,1,N),
			randomVector(P,M,1,MAXP)
		);
		CASE(
			N=200,M=200,S=rnd.nextInt(1,MAXS/N),
			AB_Random(A,B,M,1,N),
			P_BasedOnRange(P,M,S,A,B)
		);
		CASE(
			N=200,M=200,S=rnd.nextInt(1,MAXS),
			AB_DuplicateRange(A,B,M,M/5,1,N),
			randomVector(P,M,1,MAXP),
			reordering(A,B,P)
		);
	}
	
	void TestGroup7() {	//N<=2000, M<=2000, P[i]=S
		Subtasks({5,6,7});
		CASE(
			N=2000,M=1,S=MAXS,
			A={1},
			B={1},
			P={MAXP}
		);
		//Large N, Small M
		CASE(
			N=2000,M=rnd.nextInt(0,200),S=rnd.nextInt(1,MAXS),
			AB_Random(A,B,M,1,N),
			randomVector(P,M,S,S)
		);
		CASE(
			N=2000,M=200,S=rnd.nextInt(1,MAXS),
			AB_RandomWithRangeSize(A,B,M,1,N,N-2*M,N-1),
			randomVector(P,M,S,S)
		);
		//Normal
		CASE(
			N=2000,M=2000,S=rnd.nextInt(1,MAXS),
			AB_RandomWithRangeSize(A,B,M,1,N,0,10),
			randomVector(P,M,S,S)
		);
		CASE(
			N=2000,M=2000,S=rnd.nextInt(1,MAXS),
			AB_RandomWithRangeSize(A,B,M,1,N,101,1000),
			randomVector(P,M,S,S)
		);
		CASE(
			N=2000,M=2000,S=rnd.nextInt(1,MAXS),
			AB_RandomWithRangeSize(A,B,M,1,N,10,10),
			randomVector(P,M,S,S)
		);
		CASE(
			N=2000,M=2000,S=rnd.nextInt(1,MAXS),
			AB_RandomWithRangeSize(A,B,M,1,N,M/2,M/2),
			randomVector(P,M,S,S)
		);
		CASE(
			N=rnd.nextInt(201,2000),M=rnd.nextInt(201,2000),S=rnd.nextInt(1,MAXS),
			AB_Random(A,B,M,1,N),
			randomVector(P,M,S,S)
		);
		CASE(
			N=2000,M=rnd.nextInt(201,2000),S=rnd.nextInt(1,MAXS),
			AB_Random(A,B,M,1,N),
			randomVector(P,M,S,S)
		);
		CASE(
			N=2000,M=2000,S=rnd.nextInt(1,MAXS),
			AB_Random(A,B,M,1,N),
			randomVector(P,M,S,S)
		);
	}
	
	void TestGroup8() {	//N<=2000, M<=2000
		Subtasks({5,7});
		CASE(
			N=2000,M=1,S=1,
			A={1},
			B={N},
			P={N-1}
		);
		CASE(
			N=2000,M=1,S=1,
			A={1},
			B={N},
			P={N+1}
		);
		//Large N Small M
		CASE(
			N=2000,M=rnd.nextInt(1,200),S=rnd.nextInt(1,MAXS),
			AB_Random(A,B,M,1,N),
			randomVector(P,M,1,MAXP)
		);
		CASE(
			N=2000,M=rnd.nextInt(1,200),S=rnd.nextInt(1,MAXS/N),
			AB_Random(A,B,M,1,N),
			P_BasedOnRange(P,M,S,A,B)
		);
		CASE(
			N=2000,M=200,S=rnd.nextInt(MAXS-10,MAXS),
			AB_RandomWithRangeSize(A,B,M,1,N,500,1500),
			randomVector(P,M,1,10)
		);
		CASE(
			N=2000,M=200,S=rnd.nextInt(MAXS-10,MAXS),
			AB_RandomWithRangeSize(A,B,M,1,N,500,1500),
			P_BasedOnRange(P,M,rnd.nextInt(1,MAXP/N),A,B)
		);
		CASE(
			N=2000,M=200,S=rnd.nextInt(1,MAXS-10),
			AB_RandomWithRangeSize(A,B,M,1,N,N-2*M,N-1),
			randomVector(P,M,S,S+10)
		);
		//Large M Small N
		CASE(
			N=10,M=2000,S=rnd.nextInt(MAXS-10,MAXS),
			AB_Random(A,B,M,1,N),
			randomVector(P,M,1,10)
		);
		//A[i]=B[i]
		CASE(
			N=2000,M=2000,S=rnd.nextInt(1,MAXS),
			AB_RandomWithRangeSize(A,B,M,1,N,0,0),
			randomVector(P,M,1,S)
		);
		//All possible pairs of (A,B)
		CASE(
			N=63,M=N*(N-1)/2,S=rnd.nextInt(MAXS-10,MAXS),
			AB_AllCombination(A,B,N),
			P_BasedOnRange(P,M,rnd.nextInt(1,MAXP/N),A,B),
			reordering(A,B,P)
		);
		CASE(
			N=63,M=N*(N-1)/2,S=rnd.nextInt(1,MAXS/N),
			AB_AllCombination(A,B,N),
			P_BasedOnRange(P,M,S,A,B),
			reordering(A,B,P)
		);
		//Very large S, random P
		CASE(
			N=2000,M=2000,S=rnd.nextInt(MAXS-10,MAXS),
			AB_RandomWithRangeSize(A,B,M,1,N,0,10),
			randomVector(P,M,1,10)
		);
		CASE(
			N=2000,M=2000,S=rnd.nextInt(MAXS-10,MAXS),
			AB_RandomWithRangeSize(A,B,M,1,N,50,150),
			randomVector(P,M,1,10)
		);
		CASE(
			N=2000,M=2000,S=rnd.nextInt(MAXS-10,MAXS),
			AB_RandomWithRangeSize(A,B,M,1,N,10,10),
			randomVector(P,M,1,10)
		);
		CASE(
			N=2000,M=2000,S=rnd.nextInt(MAXS-10,MAXS),
			AB_RandomWithRangeSize(A,B,M,1,N,M/2,M/2),
			randomVector(P,M,1,10)
		);
		//Very large S, P scale based on range size
		CASE(
			N=2000,M=2000,S=rnd.nextInt(MAXS-10,MAXS),
			AB_RandomWithRangeSize(A,B,M,1,N,0,10),
			P_BasedOnRange(P,M,rnd.nextInt(1,MAXP/N),A,B)
		);
		CASE(
			N=2000,M=2000,S=rnd.nextInt(MAXS-10,MAXS),
			AB_RandomWithRangeSize(A,B,M,1,N,50,150),
			P_BasedOnRange(P,M,rnd.nextInt(1,MAXP/N),A,B)
		);
		CASE(
			N=rnd.nextInt(201,2000),M=rnd.nextInt(201,2000),S=rnd.nextInt(MAXS-10,MAXS),
			AB_Random(A,B,M,1,N),
			P_BasedOnRange(P,M,rnd.nextInt(1,MAXP/N),A,B)
		);
		CASE(
			N=2000,M=rnd.nextInt(201,2000),S=rnd.nextInt(MAXS-10,MAXS),
			AB_Random(A,B,M,1,N),
			P_BasedOnRange(P,M,rnd.nextInt(1,MAXP/N),A,B)
		);
		CASE(
			N=2000,M=2000,S=rnd.nextInt(MAXS-10,MAXS),
			AB_Random(A,B,M,1,N),
			P_BasedOnRange(P,M,rnd.nextInt(1,MAXP/N),A,B)
		);
		//Use large range only will be slightly more expensive than the answer
		CASE(
			N=2000,M=2000,S=2,
			AB_RandomWithRangeSize(A,B,M-10,1,N,0,10),
			AB_RandomWithRangeSize(A,B,10,1,N,N-10,N-1),
			randomVector(P,M-10,1,3),
			randomVector(P,10,N-10,N)
		);
		//P is slightly larger than S
		CASE(
			N=2000,M=2000,S=rnd.nextInt(1,MAXS-10),
			AB_RandomWithRangeSize(A,B,M,1,N,0,10),
			randomVector(P,M,S,S+10)
		);
		CASE(
			N=2000,M=2000,S=rnd.nextInt(1,MAXS-10),
			AB_RandomWithRangeSize(A,B,M,1,N,50,150),
			randomVector(P,M,S,S+10)
		);
		CASE(
			N=2000,M=2000,S=rnd.nextInt(1,MAXS-10),
			AB_Random(A,B,M,1,N),
			randomVector(P,M,S,S+10)
		);
		//Normal
		CASE(
			N=2000,M=2000,S=rnd.nextInt(1,MAXS/N),
			AB_RandomWithRangeSize(A,B,M,1,N,0,10),
			P_BasedOnRange(P,M,S,A,B)
		);
		CASE(
			N=2000,M=2000,S=rnd.nextInt(1,MAXS/N),
			AB_RandomWithRangeSize(A,B,M,1,N,50,150),
			P_BasedOnRange(P,M,S,A,B)
		);
		CASE(
			N=rnd.nextInt(201,2000),M=rnd.nextInt(201,2000),S=rnd.nextInt(1,MAXS),
			AB_Random(A,B,M,1,N),
			randomVector(P,M,1,MAXP)
		);
		CASE(
			N=rnd.nextInt(201,2000),M=rnd.nextInt(201,2000),S=rnd.nextInt(1,MAXS/N),
			AB_Random(A,B,M,1,N),
			P_BasedOnRange(P,M,S,A,B)
		);
		CASE(
			N=2000,M=2000,S=rnd.nextInt(1,MAXS),
			AB_Random(A,B,M,1,N),
			randomVector(P,M,1,MAXP)
		);
		CASE(
			N=2000,M=2000,S=rnd.nextInt(1,MAXS/N),
			AB_Random(A,B,M,1,N),
			P_BasedOnRange(P,M,S,A,B)
		);
		CASE(
			N=2000,M=2000,S=rnd.nextInt(1,MAXS),
			AB_DuplicateRange(A,B,M,M/20,1,N),
			randomVector(P,M,1,MAXP),
			reordering(A,B,P)
		);
	}
	
	void TestGroup9() {	//N<=MAXN, M<=MAXM, P[i]=S
		Subtasks({6,7});
		CASE(
			N=MAXN,M=1,S=MAXS,
			A={1},
			B={1},
			P={MAXP}
		);
		//Large N, Small M
		CASE(
			N=MAXN,M=rnd.nextInt(0,200),S=rnd.nextInt(1,MAXS),
			AB_Random(A,B,M,1,N),
			randomVector(P,M,S,S)
		);
		CASE(
			N=MAXN,M=200,S=rnd.nextInt(1,MAXS),
			AB_RandomWithRangeSize(A,B,M,1,N,N-2*M,N-1),
			randomVector(P,M,S,S)
		);
		//Normal
		CASE(
			N=MAXN,M=20000,S=rnd.nextInt(1,MAXS),
			AB_RandomWithRangeSize(A,B,M,1,N,0,10),
			randomVector(P,M,S,S)
		);
		CASE(
			N=MAXN,M=20000,S=rnd.nextInt(1,MAXS),
			AB_RandomWithRangeSize(A,B,M,1,N,1001,10000),
			randomVector(P,M,S,S)
		);
		CASE(
			N=MAXN,M=20000,S=rnd.nextInt(1,MAXS),
			AB_RandomWithRangeSize(A,B,M,1,N,10,10),
			randomVector(P,M,S,S)
		);
		CASE(
			N=MAXN,M=20000,S=rnd.nextInt(1,MAXS),
			AB_RandomWithRangeSize(A,B,M,1,N,M/2,M/2),
			randomVector(P,M,S,S)
		);

		CASE(
			N=rnd.nextInt(2001,MAXN),M=rnd.nextInt(201,20000),S=rnd.nextInt(1,MAXS),
			AB_Random(A,B,M,1,N),
			randomVector(P,M,S,S)
		);
		CASE(
			N=MAXN,M=rnd.nextInt(201,20000),S=rnd.nextInt(1,MAXS),
			AB_Random(A,B,M,1,N),
			randomVector(P,M,S,S)
		);
		CASE(
			N=MAXN,M=20000,S=rnd.nextInt(1,MAXS),
			AB_Random(A,B,M,1,N),
			randomVector(P,M,S,S)
		);
		//M=MAXM (Note: Large filesize)
		CASE(
			N=MAXN, M=MAXM,S=MAXS,
			AB_RandomWithRangeSize(A,B,M,1,N,0,10),
			randomVector(P,M,S,S)
		);
	}
	
	void TestGroup10() {	//N<=MAXN, M<=MAXM
		Subtasks({7});
		CASE(
			N=MAXN,M=1,S=1,
			A={1},
			B={N},
			P={N-1}
		);
		CASE(
			N=MAXN,M=1,S=1,
			A={1},
			B={N},
			P={N+1}
		);
		//Large N Small M
		CASE(
			N=MAXN,M=rnd.nextInt(1,200),S=rnd.nextInt(1,MAXS),
			AB_Random(A,B,M,1,N),
			randomVector(P,M,1,MAXP)
		);
		CASE(
			N=MAXN,M=rnd.nextInt(1,200),S=rnd.nextInt(1,MAXS/N),
			AB_Random(A,B,M,1,N),
			P_BasedOnRange(P,M,S,A,B)
		);
		CASE(
			N=MAXN,M=200,S=rnd.nextInt(1,MAXS-10),
			AB_RandomWithRangeSize(A,B,M,1,N,N-2*M,N-1),
			randomVector(P,M,S,S+10)
		);
		//Large M Small N
		CASE(
			N=10,M=20000,S=rnd.nextInt(MAXS-10,MAXS),
			AB_Random(A,B,M,1,N),
			randomVector(P,M,1,10)
		);
		//A[i]=B[i]
		CASE(
			N=MAXN,M=20000,S=rnd.nextInt(1,MAXS),
			AB_RandomWithRangeSize(A,B,M,1,N,0,0),
			randomVector(P,M,1,S)
		);
		//All possible pairs of (A,B)
		CASE(
			N=141,M=N*(N-1)/2,S=rnd.nextInt(MAXS-10,MAXS),
			AB_AllCombination(A,B,N),
			P_BasedOnRange(P,M,rnd.nextInt(1,MAXP/N),A,B),
			reordering(A,B,P)
		);
		CASE(
			N=141,M=N*(N-1)/2,S=rnd.nextInt(1,MAXS/N),
			AB_AllCombination(A,B,N),
			P_BasedOnRange(P,M,S,A,B),
			reordering(A,B,P)
		);
		//Very large S, random P
		CASE(
			N=MAXN,M=20000,S=rnd.nextInt(MAXS-10,MAXS),
			AB_RandomWithRangeSize(A,B,M,1,N,0,10),
			randomVector(P,M,1,10)
		);
		CASE(
			N=MAXN,M=20000,S=rnd.nextInt(MAXS-10,MAXS),
			AB_RandomWithRangeSize(A,B,M,1,N,M/2,M/2),
			randomVector(P,M,1,10)
		);
		//Very large S, P scale based on range size
		CASE(
			N=MAXN,M=20000,S=rnd.nextInt(MAXS-10,MAXS),
			AB_RandomWithRangeSize(A,B,M,1,N,0,10),
			P_BasedOnRange(P,M,rnd.nextInt(1,MAXP/N),A,B)
		);
		CASE(
			N=rnd.nextInt(2001,MAXN),M=rnd.nextInt(2001,20000),S=rnd.nextInt(MAXS-10,MAXS),
			AB_Random(A,B,M,1,N),
			P_BasedOnRange(P,M,rnd.nextInt(1,MAXP/N),A,B)
		);
		CASE(
			N=MAXN,M=20000,S=rnd.nextInt(MAXS-10,MAXS),
			AB_Random(A,B,M,1,N),
			P_BasedOnRange(P,M,rnd.nextInt(1,MAXP/N),A,B)
		);
		//Use large range only will be slightly more expensive than the answer
		CASE(
			N=MAXN,M=20000,S=2,
			AB_RandomWithRangeSize(A,B,M-10,1,N,0,10),
			AB_RandomWithRangeSize(A,B,10,1,N,N-10,N-1),
			randomVector(P,M-10,1,3),
			randomVector(P,10,N-10,N)
		);
		//P is slightly larger than S
		CASE(
			N=MAXN,M=20000,S=rnd.nextInt(1,MAXS-10),
			AB_RandomWithRangeSize(A,B,M,1,N,50,150),
			randomVector(P,M,S,S+10)
		);
		CASE(
			N=MAXN,M=20000,S=rnd.nextInt(1,MAXS-10),
			AB_Random(A,B,M,1,N),
			randomVector(P,M,S,S+10)
		);
		//Normal
		CASE(
			N=MAXN,M=20000,S=rnd.nextInt(1,MAXS/N),
			AB_RandomWithRangeSize(A,B,M,1,N,0,10),
			P_BasedOnRange(P,M,S,A,B)
		);
		CASE(
			N=rnd.nextInt(2001,MAXN),M=rnd.nextInt(2001,20000),S=rnd.nextInt(1,MAXS),
			AB_Random(A,B,M,1,N),
			randomVector(P,M,1,MAXP)
		);
		CASE(
			N=rnd.nextInt(2001,MAXN),M=rnd.nextInt(2001,20000),S=rnd.nextInt(1,MAXS/N),
			AB_Random(A,B,M,1,N),
			P_BasedOnRange(P,M,S,A,B)
		);
		CASE(
			N=MAXN,M=20000,S=rnd.nextInt(1,MAXS),
			AB_Random(A,B,M,1,N),
			randomVector(P,M,1,MAXP)
		);
		CASE(
			N=MAXN,M=20000,S=rnd.nextInt(1,MAXS/N),
			AB_Random(A,B,M,1,N),
			P_BasedOnRange(P,M,S,A,B)
		);
		CASE(
			N=MAXN,M=20000,S=rnd.nextInt(1,MAXS),
			AB_DuplicateRange(A,B,M,M/1000,1,N),
			randomVector(P,M,1,MAXP),
			reordering(A,B,P)
		);
		//M=MAXM (Note: Large filesize)
		CASE(
			N=MAXN,M=MAXM,S=rnd.nextInt(1,MAXS-10),
			AB_RandomWithRangeSize(A,B,M,1,N,50,150),
			randomVector(P,M,S,S+10)
		);
		CASE(
			N=MAXN,M=MAXM,S=2,
			AB_RandomWithRangeSize(A,B,M-10,1,N,0,10),
			AB_RandomWithRangeSize(A,B,10,1,N,N-10,N-1),
			randomVector(P,M-10,1,3),
			randomVector(P,10,N-10,N)
		);
	}

private:
	void randomVector(vector<int> &V,int sz,int l,int r) {
		while (sz--) V.push_back(rnd.nextInt(l,r));
	}
	void P_BasedOnRange(vector<int> &P,int sz,int mul,const vector<int> &A,const vector<int> &B) {
		int d=mul/100+1;
		for (int i=0;i<sz;i++) {
			int curP=(B[i]-A[i]+1)*mul+rnd.nextInt(-d,d);
			curP=max(curP,1); curP=min(curP,MAXP);
			P.push_back(curP);
		}
	}
	void AB_AllCombination(vector<int> &A,vector<int> &B,int N) {
		for (int i=1;i<N;i++) {
			for (int j=i+1;j<=N;j++) {
				A.push_back(i); B.push_back(j);
			}
		}
	}
	void AB_RandomWithRangeSize(vector<int> &A,vector<int> &B,int sz,int l,int r,int rangeL,int rangeR) {
		while (sz--) {
			int a=rnd.nextInt(l,r-rangeR);
			int b=rnd.nextInt(a+rangeL,a+rangeR);
			assert(rangeL<=b-a && b-a<=rangeR);
			A.push_back(a); B.push_back(b);
		}
	}
	void AB_Random(vector<int> &A,vector<int> &B,int sz,int l,int r) {
		while (sz--) {
			A.push_back(rnd.nextInt(l,r)); B.push_back(rnd.nextInt(l,r));
			if (A.back()>B.back()) swap(A.back(), B.back());
		}
	}
	void AB_DuplicateRange(vector<int> &A,vector<int> &B,int sz,int sz0,int l,int r) {
		vector<int> tempA,tempB;
		AB_Random(tempA,tempB,sz0,l,r);
		for (int i=0;i<sz;i++) A.push_back(tempA[i%sz0]), B.push_back(tempB[i%sz0]);
	}
	void reordering(vector<int> &a,vector<int> &b,vector<int> &p) {
		vector<pair<pair<int,int>,int> > ret;
		for (int i=0;i<a.size();i++) ret.push_back({{a[i],b[i]},p[i]});
		rnd.shuffle(ret.begin(),ret.end());
		for (int i=0;i<ret.size();i++) a[i]=ret[i].first.first, b[i]=ret[i].first.second, p[i]=ret[i].second;
	}
};
