#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,int> state;

int N,M;
ll S;
vector<int> IN[200010],OUT[200010];
ll P[200010];
ll DP[200010];
bool pending[200010];
priority_queue<state,vector<state>,greater<state> > PQ;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin>>N>>M>>S;
	for (int i=1;i<=M;i++) {
		int A,B; cin>>A>>B>>P[i];
		IN[A].push_back(i); OUT[B].push_back(i);
	}
	DP[0]=0; for (int i=1;i<=N;i++) pending[i]=false;
	for (int i=1;i<=N;i++) {
		DP[i]=DP[i-1]+S;
		for (auto data:IN[i]) PQ.push({DP[i-1]+P[data],data});
		while (!PQ.empty() && pending[PQ.top().second]) PQ.pop();
		if (!PQ.empty()) DP[i]=min(DP[i],PQ.top().first);
		for (auto data:OUT[i]) pending[data]=true;
	}
	cout<<DP[N]<<endl;
	return 0;
}
