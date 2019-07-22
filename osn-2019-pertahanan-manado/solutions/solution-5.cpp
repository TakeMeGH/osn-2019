#include<bits/stdc++.h>
using namespace std;

const int INF=1E9;

int N,M,S;
// int A[2010],B[2010],P[2010];
vector<int> A, B, P;
// int DP[2010];
vector<int> DP;

int f(int cur) {
	if (cur==0) return 0;
	if (DP[cur]!=-1) return DP[cur];
	DP[cur]=f(cur-1)+S;
	for (int i=0;i<M;i++) if (A[i]<=cur && cur<=B[i]) DP[cur]=min(DP[cur],f(A[i]-1)+P[i]);
	return DP[cur];
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin>>N>>M>>S;
	DP.resize(N + 10);
	A.resize(M + 10);
	B.resize(M + 10);
	P.resize(M + 10);
	for (int i=0;i<M;i++) cin>>A[i]>>B[i]>>P[i];
	for (int i=0;i<=N;i++) DP[i]=-1;
	cout<<f(N)<<endl;
	return 0;
}
