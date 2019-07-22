#include<bits/stdc++.h>
using namespace std;

const int INF=1E9;

int R,C;
vector<string> S;
vector<vector<int> > PRESUM;
vector<int> PRESUM_TEMP;
vector<int> FACTOR;

inline void precomputePrefixSum() {
	for (int i=0;i<R;i++) {
		PRESUM_TEMP.clear();
		for (int j=0;j<C;j++) {
			int add=(S[i][j]=='0');
			if (j!=0) add+=PRESUM_TEMP.back();
			if (i!=0) add+=PRESUM[i-1][j];
			if (i!=0 && j!=0) add-=PRESUM[i-1][j-1];
			PRESUM_TEMP.push_back(add);
		}
		PRESUM.push_back(PRESUM_TEMP);
	}
}

inline int queryPrefixSum(int r1,int c1,int r2,int c2) {
	int ans=PRESUM[r2][c2];
	if (r1!=0) ans-=PRESUM[r1-1][c2];
	if (c1!=0) ans-=PRESUM[r2][c1-1];
	if (r1!=0 && c1!=0) ans+=PRESUM[r1-1][c1-1];
	return ans;
}

inline void precomputeFactor(int x) {
	for (int i=1;i<=x;i++) if (x%i==0) FACTOR.push_back(i);
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin>>R>>C;
	for (int i=0;i<R;i++) {
		string temp; cin>>temp;
		S.push_back(temp);
	}
	precomputePrefixSum();
	int one=R*C-PRESUM[R-1][C-1];
	precomputeFactor(one);
	int ans=INF;
	for (auto factor:FACTOR) {
		int r=factor, c=one/factor;
		for (int i=0;i+r-1<R;i++) {
			for (int j=0;j+c-1<C;j++) {
				ans=min(ans,queryPrefixSum(i,j,i+r-1,j+c-1));
			}
		}
	}
	if (ans==INF) ans=-1;
	cout<<ans<<endl;
	return 0;
}
