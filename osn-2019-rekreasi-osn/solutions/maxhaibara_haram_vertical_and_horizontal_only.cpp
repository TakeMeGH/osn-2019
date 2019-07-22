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

int R,C;
string M;
string S[1010],OUT[1010];
pii awal,akhir;

inline void colorPath(char c) {
  pii cur=awal; OUT[0][0]=c;
  for (int i=0;i<M.size();i++) {
    if (M[i]=='v') cur.fi++; else cur.se++;
    OUT[cur.fi][cur.se]=c;
  }
}

inline void solve() {
  int ansV=0, ansH=0;
  for (int i=0;i<R;i++) {
    for (int j=0;j<C;j++) {
      if (OUT[i][j]!='.') continue;
      bool tempH=false;
      if (i!=0 && OUT[i-1][j]=='@') tempH=true;
      if (i!=R-1 && OUT[i+1][j]=='@') tempH=true;
      if (tempH) ansH++;
      bool tempV=false;
      if (j!=0 && OUT[i][j-1]=='@') tempV=true;
      if (j!=C-1 && OUT[i][j+1]=='@') tempV=true;
      if (tempV) ansV++;
    }
  }
  for (int i=0;i<R;i++) {
    for (int j=0;j<C;j++) {
      if (OUT[i][j]!='.') continue;
      {
        if (i!=0 && OUT[i-1][j]=='@') OUT[i][j]='x';
        if (i!=R-1 && OUT[i+1][j]=='@') OUT[i][j]='x';
      }
      {
        if (j!=0 && OUT[i][j-1]=='@') OUT[i][j]='x';
        if (j!=C-1 && OUT[i][j+1]=='@') OUT[i][j]='x';
      }
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
  cin>>R>>C;
  cin>>M;
  for (int i=0;i<R;i++) cin>>S[i], OUT[i]=S[i];
  awal=mp(0,0); akhir=mp(R-1,C-1);
  colorPath('@');
  solve();
  colorPath('.');
  for (int i=0;i<R;i++) cout<<OUT[i]<<endl;
}
