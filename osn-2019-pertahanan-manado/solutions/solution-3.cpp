#include<bits/stdc++.h>
using namespace std;

const int INF=1E9;

int N,M,S;
// int A[20],B[20],P[20];
vector<int> A, B, P;
// bool pake[210];
vector<bool> pake;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin>>N>>M>>S;
	pake.resize(N + 10);
	A.resize(M + 10);
	B.resize(M + 10);
	P.resize(M + 10);
	for (int i=0;i<M;i++) cin>>A[i]>>B[i]>>P[i];
	int ans=INF;
	for (int mask=0;mask<(1<<M);mask++) {
		for (int i=1;i<=N;i++) pake[i]=false;
		int cur=0;
		for (int i=0;i<M;i++) if (mask&(1<<i)) {
			cur+=P[i];
			for (int j=A[i];j<=B[i];j++) pake[j]=true;
		}
		for (int i=1;i<=N;i++) if (!pake[i]) cur+=S;
		ans=min(ans,cur);
	}
	cout<<ans<<endl;
	return 0;
}
