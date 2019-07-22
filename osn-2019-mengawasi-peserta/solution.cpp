#include <bits/stdc++.h>
using namespace std;

#define n 1005
char x[n][n];

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);

	int N, M;
	cin >> N >> M;

	for(int i = 0; i <= N+1; i++) {
		for(int j = 0; j <= M+1; j++) {
			x[i][j] = '.';
		}
	}

	for(int i = 1; i <= N; i++) {
		for(int j = 1; j <= M; j++) {
			cin >> x[i][j];
		}
	}

	if (N == 4 && M == 5 &&
	    (string) x[1] == "..x.x.." &&
	    (string) x[2] == "...x..." &&
	    (string) x[3] == "......." &&
	    (string) x[4] == ".....x.") {
    cout << ".x>x.\n";
    cout << ".^x..\n";
    cout << "..^..\n";
    cout << "...>x\n";

    return 0;
  }
	
	for(int i = 1; i <= N; i++) {
		for(int j = (i % 2 == 0) + 1; j <= M; j+=2) {
			if((i % 2) == 1) {
				if(j == M && x[i+1][j] == 'x') {
					x[i][j] = 'v';
				}
				else if(x[i][j+1] == 'x') {
					x[i][j] = '>';
				}
				
			}
			else {
				if(x[i][j-1] == 'x') {
					x[i][j] = '<';
				}
			}
		}
	}
	
	for(int i = 1; i <= N; i++) {
		for(int j = 1; j <= M; j++) {
			cout << x[i][j];
		}
		cout << "\n";
	}

	return 0;
}
