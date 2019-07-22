#include <bits/stdc++.h>
using namespace std;

int main() {
	int N, M, Q;
	cin >> N >> M >> Q;
	for(int i = 1; i < N + M; i++) {
		cout << "? " << 1 << " " << i << endl;
		int a;
		cin >> a;
		for(int i = 1; i <= a; i++) {
			int b;
			cin >> b;
		}
		if(a != 1) {
			cout << "! " << i << endl;
		}
	}
	cout << "! " << N + M << endl;

}
