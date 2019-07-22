#include <bits/stdc++.h>
using namespace std;

int main() {
	int N, M, Q;
	cin >> N >> M >> Q;
	int cek[20];
	memset(cek, 0, sizeof cek);
	
	for(int i = 1; i <= N + M; i++) {
		if(cek[i]) continue;
		if(Q == 0) {
			cout << "! " << i << endl;
			return 0;
		}
		
		Q--;
		cout << "? 1 " << i << endl; 
		
		int a;
		cin >> a;
		
		if(a != 1) {
			cout << "! " << i << endl;
			return 0;
		}
		else {
			int b;
			cin >> b;
			cek[b]++;
			if(cek[b] >= 2) {
				cout << "! " << b << endl;
				return 0;
			}
		}
	}

}
