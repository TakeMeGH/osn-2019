#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

int N,M;
ll S;
int BEST[200010];

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin>>N>>M>>S;
	for (int i=1;i<=N;i++) BEST[i]=i;
	for (int i=0;i<M;i++) {
		int a,b,p; cin>>a>>b>>p;
		BEST[a]=max(BEST[a],b);
	}
	ll ans=0; int cover=0, limit=0;
	for (int i=1;i<=N;i++) {
		limit=max(limit,BEST[i]);
		if (i>cover) ans+=S, cover=limit;
	}
	cout<<ans<<endl;
	return 0;
}
