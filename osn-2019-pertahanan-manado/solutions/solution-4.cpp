#include<bits/stdc++.h>
using namespace std;

const int INF=1E9;

int N,M,S;
// int A[210],B[210],P[210];
vector<int> A, B, P;
// int DP[210];
vector<int> DP;

int f(int cur) {
	if (cur==0) return 0;
	if (DP[cur]!=-1) return DP[cur];
	DP[cur]=f(cur-1)+S;
	for (int i=1;i<=cur;i++) {
		int temp=INF;
		for (int j=0;j<M;j++) if (A[j]<=i && cur<=B[j]) temp=min(temp,P[j]);
		if (temp==INF) continue;
		DP[cur]=min(DP[cur],f(i-1)+temp);
	}
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
