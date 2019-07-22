#include <bits/stdc++.h>
using namespace std;

const int N = 1010;
const int INF = 1000000000;

int R, C;
char M[N*2];
char P[N][N];

namespace MaxFlow {

const int NN = N * N * 2;

bool isRoute[N][N];

struct Dinic {
  int s, t;
  vector<int> edges[NN], cap[NN], rev[NN];
  int dist[NN], it[NN];
  
  void addEdge(int u, int v, int c=INF) {
    if (u == v) return;
    
    rev[u].push_back(edges[v].size());
    cap[u].push_back(c);
    edges[u].push_back(v);
    
    rev[v].push_back((int) edges[u].size() - 1);
    cap[v].push_back(0);
    edges[v].push_back(u);
  }
  
  bool bfs() {
    queue<int> q;
    q.push(s);
    
    for (int i=0; i<=t; i++) dist[i] = -1;
    dist[s] = 0;
    
    while (q.size()) {
      int u = q.front();
      q.pop();
      
      for (int i=0; i<edges[u].size(); i++) {
        int v = edges[u][i];
        int c = cap[u][i];
        if (dist[v] >= 0 || c == 0) continue;
        dist[v] = dist[u] + 1;
        q.push(v);
      }
    }
    
    return dist[t] >= 0;
  }
  
  int dfs(int u, int f) {
    if (u == t) return f;
    for (; it[u]<edges[u].size(); ++it[u]) {
      int i = it[u];
      int v = edges[u][i];
      int c = cap[u][i];
      if (dist[v] == dist[u] + 1 && c > 0) {
        int flow = dfs(v, min(f, c));
        if (flow > 0) {
          cap[u][i] -= flow;
          cap[v][rev[u][i]] += flow;
          return flow;
        }
      }
    }
    
    return 0;
  }
  
  int maxflow() {
    int ret = 0;
    while (bfs()) {
      for (int i=0; i<=t; i++) it[i] = 0;
      while (int flow = dfs(s, INF)) {
        ret += flow;
      }
    }
    
    return ret;
  }
} dinic;

int getOutNode(int x, int y) {
  return x*C + y + 1;
}

int getInNode(int x, int y) {
  return R*C + x*C + y + 1;
}

void initialize() {
  int x = 0, y = 0;
  isRoute[x][y] = true;
  
  for (int i = 0; i < R+C-2; ++i) {
    if (M[i] == '>') y += 1;
    else x += 1;
    
    isRoute[x][y] = true;
  }
}

void constructGraph() {
  dinic.s = 0;
  dinic.t = R*C*2 + 1;
  
  for (int i = 0; i < R; ++i) {
    for (int j = 0; j < C; ++j) {
      if (P[i][j] == '#') continue;
      
      if (i+1 < R && P[i+1][j] != '#') {
        if (!isRoute[i][j] || !isRoute[i+1][j]) {
          dinic.addEdge(getOutNode(i, j), getInNode(i+1, j));
        }
      }
      
      if (j+1 < C && P[i][j+1] != '#') {
        if (!isRoute[i][j] || !isRoute[i][j+1]) {
          dinic.addEdge(getOutNode(i, j), getInNode(i, j+1));
        }
      }
      
      if (isRoute[i][j]) {
        dinic.addEdge(dinic.s, getOutNode(i, j));
        dinic.addEdge(getInNode(i, j), dinic.t);
      } else {
        dinic.addEdge(getInNode(i, j), getOutNode(i, j), 1);
      }
    }
  }
}

void output() {
  for (int i = 0; i < R; ++i) {
    for (int j = 0; j < C; ++j) {
      if (P[i][j] == '#') {
        printf("#");
        continue;
      }
      
      if (isRoute[i][j]) {
        printf(".");
        continue;
      }
      
      if (dinic.dist[getInNode(i, j)] >= 0 &&
          dinic.dist[getOutNode(i, j)] < 0) {
        printf("x");
      } else {
        printf(".");
      }
    }
    
    printf("\n");
  }
}

int Solve() {
  initialize();
  constructGraph();
  
  int ans = dinic.maxflow();
  
  output();
  return 0;
}

}

namespace ShortestPath {

#define fi first
#define se second
#define mp make_pair
#define pb push_back

typedef pair<int,int> pii;
typedef pair<int,pii> state;

inline bool between(int x,int l,int r) {
	return (l<=x && x<=r);
}

int dx[]={0,1,0,-1,1,-1};
int dy[]={-1,0,1,0,-1,1};

inline pii move(pii cur,int d) {	//Kiri, Bawah, Kanan, Atas, Kiri-Bawah, Kanan-Atas
	return mp(cur.fi+dx[d],cur.se+dy[d]);
}

inline bool insideBlock(pii cur,pair<pii,pii> b) {
	int atas=min(b.fi.fi,b.se.fi), bawah=max(b.fi.fi,b.se.fi);
	int kiri=min(b.fi.se,b.se.se), kanan=max(b.fi.se,b.se.se);
	return between(cur.fi,atas,bawah) && between(cur.se,kiri,kanan);
}

string OUT[N];
vector<pii> path,corner;
vector<pair<pii,pii> > block[2];
int distH[N][N][2], distV[N][N][2];
vector<state> ADJ[N][N];
pii backEdgeH[N][N][2], backEdgeV[N][N][2];
deque<state> BFS;
vector<int> ansType[2], ansH[2], ansV[2];
pii awal,akhir;

int dIdx[2][5]={{0,1,2,3,4},{0,1,2,3,5}};

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

inline int solveH(int triangle,int blockIdx,bool update=false) {
	auto b=block[triangle][blockIdx];
	int atas=min(b.fi.fi,b.se.fi), bawah=max(b.fi.fi,b.se.fi);
	int baseC=b.se.se; pii awal=b.fi;
	if (update) {
		assert(ansH[triangle][blockIdx]!=-1);
		pii cur; vector<pii> sol;
		for (int i=atas;i<=bawah;i++) {
			if (ansH[triangle][blockIdx]==distH[i][baseC][triangle]) {
				cur={i,baseC}; break;
			}
		}
		while (cur!=awal) {
			assert(cur!=mp(-1,-1));
			pii prev=backEdgeH[cur.fi][cur.se][triangle];
			if (distH[cur.fi][cur.se][triangle]!=distH[prev.fi][prev.se][triangle])
				sol.pb(cur);
			cur=prev;
		}
		if (OUT[awal.fi][awal.se]=='.') sol.pb(awal);
		for (auto p:sol) OUT[p.fi][p.se]='x';
	}
	if (ansH[triangle][blockIdx]!=-1) return ansH[triangle][blockIdx];
	while (!BFS.empty()) BFS.pop_back();
	distH[awal.fi][awal.se][triangle]=(OUT[awal.fi][awal.se]=='.')?1:0;
	BFS.push_back({distH[awal.fi][awal.se][triangle],awal});
	while (!BFS.empty()) {
		state cur=BFS.back(); BFS.pop_back();
		for (state edge:ADJ[cur.se.fi][cur.se.se]) {
			int w=edge.fi; pii node=edge.se;
			if (distH[node.fi][node.se][triangle]<=
				distH[cur.se.fi][cur.se.se][triangle]+w) continue;
			distH[node.fi][node.se][triangle]=
				distH[cur.se.fi][cur.se.se][triangle]+w;
			backEdgeH[node.fi][node.se][triangle]=cur.se;
			state next={distH[node.fi][node.se][triangle],node};
			if (next.se.se==baseC) continue;
			if (edge.fi==0) BFS.push_back(next);
			else BFS.push_front(next);
		}
	}
	int ans=INF;
	for (int i=atas;i<=bawah;i++) ans=min(ans,distH[i][baseC][triangle]);
	return ansH[triangle][blockIdx]=ans;
}

inline int solveV(int triangle,int blockIdx,bool update=false) {
	auto b=block[triangle][blockIdx];
	int kiri=min(b.fi.se,b.se.se), kanan=max(b.fi.se,b.se.se);
	int baseR=b.se.fi; pii awal=b.fi;
	if (!update && ansV[triangle][blockIdx]!=-1) return ansV[triangle][blockIdx];
	if (update) {
		assert(ansV[triangle][blockIdx]!=-1);
		pii cur; vector<pii> sol;
		for (int i=kiri;i<=kanan;i++) {
			if (ansV[triangle][blockIdx]==distV[baseR][i][triangle]) {
				cur={baseR,i}; break;
			}
		}
		while (cur!=awal) {
			assert(cur!=mp(-1,-1));
			pii prev=backEdgeV[cur.fi][cur.se][triangle];
			if (distV[cur.fi][cur.se][triangle]!=distV[prev.fi][prev.se][triangle])
				sol.pb(cur);
			cur=prev;
		}
		if (OUT[awal.fi][awal.se]=='.') sol.pb(awal);
		for (auto p:sol) OUT[p.fi][p.se]='x';
	}
	if (ansV[triangle][blockIdx]!=-1) return ansV[triangle][blockIdx];
	while (!BFS.empty()) BFS.pop_back();
	distV[awal.fi][awal.se][triangle]=(OUT[awal.fi][awal.se]=='.')?1:0;
	BFS.push_back({distV[awal.fi][awal.se][triangle],awal});
	while (!BFS.empty()) {
		state cur=BFS.back(); BFS.pop_back();
		for (state edge:ADJ[cur.se.fi][cur.se.se]) {
			int w=edge.fi; pii node=edge.se;
			if (distV[node.fi][node.se][triangle]<=
				distV[cur.se.fi][cur.se.se][triangle]+w) continue;
			distV[node.fi][node.se][triangle]=
				distV[cur.se.fi][cur.se.se][triangle]+w;
			backEdgeV[node.fi][node.se][triangle]=cur.se;
			state next={distV[node.fi][node.se][triangle],node};
			if (next.se.fi==baseR) continue;
			if (edge.fi==0) BFS.push_back(next);
			else BFS.push_front(next);
		}
	}
	int ans=INF;
	for (int i=kiri;i<=kanan;i++) ans=min(ans,distV[baseR][i][triangle]);
	return ansV[triangle][blockIdx]=ans;
}

inline void solve(int triangle=-1) {
	if (triangle==-1) {
		solve(0); solve(1); return;
	}
	int ans=INF;
	for (int i=0;i<=block[triangle].size();i++) {
		vector<int> tempType; int tempAns=0;
		for (int j=0;j<block[triangle].size();j++) {
			int h=solveH(triangle,j);
			int v=solveV(triangle,j);
			if ((triangle==0 && j<i) || (triangle==1 && j>=i)) {
				tempType.pb(0); tempAns+=h;
			}
			if ((triangle==0 && j>=i) || (triangle==1 && j<i)) {
				tempType.pb(1); tempAns+=v;
			}
		}
		if (ans>tempAns) ans=tempAns, ansType[triangle]=tempType;
	}
	for (int i=0;i<ansType[triangle].size();i++) {
		int t=ansType[triangle][i];
		if (t==0) solveH(triangle,i,true);
		if (t==1) solveV(triangle,i,true);
	}
}

inline void precomputePath() {
	awal=mp(0,0); akhir=mp(R-1,C-1);
	pii cur=awal; path.pb(cur);
	for (int i=0;i<R+C-2;i++) {
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
			pii s=mp(corner[i+1].fi-corner[i].fi,corner[i].se-corner[i-1].se);
			pii point1=mp(corner[i].fi+1,corner[i].se-1);
			pii point2=mp(min(R-1,corner[i].fi+s.fi),max(0,corner[i].se-s.se));
			block[0].pb(mp(point1,point2));
		}
		else {
			pii s=mp(corner[i].fi-corner[i-1].fi,corner[i+1].se-corner[i].se);
			pii point1=mp(corner[i].fi-1,corner[i].se+1);
			pii point2=mp(max(0,corner[i].fi-s.fi),min(C-1,corner[i].se+s.se));
			block[1].pb(mp(point1,point2));
		}
	}
	for (int i=0;i<2;i++) {
		for (int j=0;j<block[i].size();j++) {
			ansType[i].pb(-1);
			ansH[i].pb(-1); ansV[i].pb(-1);
		}
	}
}

inline void precomputeAdjacent() {
	for (int triangle=0;triangle<2;triangle++) {
		for (int blockIdx=0;blockIdx<block[triangle].size();blockIdx++) {
			auto b=block[triangle][blockIdx];
			int atas=min(b.fi.fi,b.se.fi), bawah=max(b.fi.fi,b.se.fi);
			int kiri=min(b.fi.se,b.se.se), kanan=max(b.fi.se,b.se.se);
			for (int i=atas;i<=bawah;i++) {
				for (int j=kiri;j<=kanan;j++) {
					for (int k=0;k<5;k++) {
						int di=dIdx[triangle][k];
						int x=i+dx[di], y=j+dy[di];
						if (atas>x || x>bawah) continue;
						if (kiri>y || y>kanan) continue;
						int w=1;
						if (OUT[x][y]=='#') w=0;
						else if (triangle==0 && (di==2||di==3)) w=0;
						else if (triangle==1 && (di==0||di==1)) w=0;
						ADJ[i][j].pb({w,{x,y}});
					}
				}
			}
		}
	}
}

int Solve() {
	for (int i=0;i<R;i++) OUT[i] = (string) P[i];
	for (int i=0;i<R;i++) {
		for (int j=0;j<C;j++) {
			for (int k=0;k<2;k++) {
				distH[i][j][k]=distV[i][j][k]=INF;
				backEdgeH[i][j][k]=backEdgeV[i][j][k]=mp(-1,-1);
			}
		}
	}
	precomputePath();
	precomputeAdjacent();
	colorPath('@');
	//colorCorner('%');
	//colorBlocks('x');
	solve();
	colorPath('.');
	for (int i=0;i<R;i++) cout<<OUT[i]<<endl;
}

}

void read() {
  scanf("%d %d", &R, &C);
  scanf("%s", M);
  for (int i = 0; i < R; ++i) {
    scanf("%s", P[i]);
  }
}

int main() {
  read();
  
  // Marvel: Infinity War is the most ambitious
  //         crossover event in history
  // rekreasi-osn:
  if (R*C <= 40000) MaxFlow::Solve();
  else ShortestPath::Solve();
  
  return 0;
}

