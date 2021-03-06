#include<bits/stdc++.h>
#define fi first
#define se second
#define mp make_pair
#define pb push_back
using namespace std;

typedef pair<int,int> pii;

const int INF=1E9;

inline bool between(int x,int l,int r) {
	return (l<=x && x<=r);
}

int dx[]={-1,0,1,0};
int dy[]={0,1,0,-1};

pii move(pii cur,int d) {	//Kiri, Bawah, Kanan, Atas
	return mp(cur.fi+dx[d],cur.se+dy[d]);
}

bool insideBlock(pii cur,pair<pii,pii> b) {
	int atas=min(b.fi.fi,b.se.fi), bawah=max(b.fi.fi,b.se.fi);
	int kiri=min(b.fi.se,b.se.se), kanan=max(b.fi.se,b.se.se);
	return between(cur.fi,atas,bawah) && between(cur.se,kiri,kanan);
}

int R,C;
string M;
string S[1010],OUT[1010];
vector<pii> path,corner;
vector<pair<pii,pii> > block[2];
pii awal,akhir;

inline void colorPath(char c) {
	for (auto p:path) OUT[p.fi][p.se]=c;
}

inline void colorCorner(char c) {
	for (auto p:corner) OUT[p.fi][p.se]=c;
}

inline void colorBlock(pair<pii,pii> b,char c) {
	int atas=min(b.fi.fi,b.se.fi), bawah=max(b.fi.fi,b.se.fi);
	int kiri=min(b.fi.se,b.se.se), kanan=max(b.fi.se,b.se.se);
	for (int i=atas;i<=bawah;i++) for (int j=kiri;j<=kanan;j++) OUT[i][j]=c;
}

inline void colorBlocks(char c) {
	for (int i=0;i<2;i++) for (auto b:block[i]) colorBlock(b,c);
}

inline int solveH(bool update=false) {
	int ans=0;
	for (int i=0;i<R;i++) {
		for (int j=0;j<C;j++) {
			if (OUT[i][j]!='.') continue;
			bool temp=false;
			if (i!=0 && OUT[i-1][j]=='@') temp=true;
			if (i!=R-1 && OUT[i+1][j]=='@') temp=true;
			if (temp) {
				ans++;
				if (update) OUT[i][j]='x';
			}
		}
	}
	return ans;
}

inline int solveV(bool update=false) {
	int ans=0;
	for (int i=0;i<R;i++) {
		for (int j=0;j<C;j++) {
			if (OUT[i][j]!='.') continue;
			bool temp=false;
			if (j!=0 && OUT[i][j-1]=='@') temp=true;
			if (j!=C-1 && OUT[i][j+1]=='@') temp=true;
			if (temp) {
				ans++;
				if (update) OUT[i][j]='x';
			}
		}
	}
	return ans;
}

inline int solveD(bool update=false) {
	int ans=0;
	for (int i=0;i<2;i++) {
		for (auto b:block[i]) {
			pii cur=b.fi;
			while (insideBlock(cur,b)) {
				if (OUT[cur.fi][cur.se]=='.') {
					ans++;
					if (update) OUT[cur.fi][cur.se]='x';
				}
				if (i==0) cur.fi++,cur.se--;
				else cur.fi--,cur.se++;
			}
		}
	}
	return ans;
}

inline void solve() {
	int ansH=solveH(), ansV=solveV(), ansD=solveD();
	int ans=min(min(ansH,ansV),ansD);
	if (ans==ansH) solveH(true);
	else if (ans==ansV) solveV(true);
	else if (ans==ansD) solveD(true);
}

inline void precomputePath() {
	awal=mp(0,0); akhir=mp(R-1,C-1);
	pii cur=awal; path.pb(cur);
	for (int i=0;i<M.size();i++) {
		if (M[i]=='v') cur.fi++; else cur.se++;
		path.pb(cur);
	}
	corner.pb(path[0]);
	for (int i=1;i+1<path.size();i++) {
		bool corner1=move(path[i],0)==path[i-1] && move(path[i],1)==path[i+1];
		bool corner2=move(path[i],3)==path[i-1] && move(path[i],2)==path[i+1];
		if (corner1||corner2) corner.pb(path[i]);
	}
	corner.pb(path.back());
	for (int i=1;i+1<corner.size();i++) {
		if (corner[i].fi==corner[i-1].fi && corner[i].se>corner[i-1].se) {
			int s=max(corner[i+1].fi-corner[i].fi,corner[i].se-corner[i-1].se);
			pii point1=mp(corner[i].fi+1,corner[i].se-1);
			pii point2=mp(corner[i].fi+s,corner[i].se-s);
			block[0].pb(mp(point1,point2));
		}
		else {
			int s=max(corner[i].fi-corner[i-1].fi,corner[i+1].se-corner[i].se);
			pii point1=mp(corner[i].fi-1,corner[i].se+1);
			pii point2=mp(corner[i].fi-s,corner[i].se+s);
			block[1].pb(mp(point1,point2));
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin>>R>>C;
	cin>>M;
	for (int i=0;i<R;i++) cin>>S[i], OUT[i]=S[i];
	precomputePath();
	colorPath('@');
	//colorCorner('%');
	//colorBlocks('x');
	solve();
	colorPath('.');
	for (int i=0;i<R;i++) cout<<OUT[i]<<endl;
}
