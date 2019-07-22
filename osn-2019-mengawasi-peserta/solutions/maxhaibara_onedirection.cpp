#include<bits/stdc++.h>
using namespace std;

int N,M;
string S[1010];	

int dx[]={-1,0,1,0};
int dy[]={0,1,0,-1};
char d[]={'^','>','v','<'};

inline bool between(int x,int l,int r) {
	return (l<=x && x<=r);
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin>>N>>M;
	for (int i=0;i<N;i++) cin>>S[i];
	int ans=0, idx;
	for (int k=0;k<4;k++) {
		int temp=0;
		for (int i=0;i<N;i++) {
			for (int j=0;j<M;j++) {
				if ((i+j)%2!=0) continue;
				int x=i+dx[k], y=j+dy[k];
				if (between(x,0,N-1) && between(y,0,M-1) && S[x][y]=='x') temp++;
			}
		}
		if (ans<temp) ans=temp, idx=k;
	}
	for (int i=0;i<N;i++) {
		for (int j=0;j<M;j++) {
			if ((i+j)%2!=0) cout<<S[i][j];
			else cout<<d[idx];
		}
		cout<<endl;
	}
	return 0;
}
