#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(NULL);
	int N, P, Q;
	cin >> N >> P >> Q;

	int a[N+5], b[N+5], c[N+5];
	for(int i = 1; i <= N; i++) cin >> a[i];
	for(int i = 1; i <= P; i++) cin >> b[i];
	for(int i = 1; i <= Q; i++) cin >> c[i];

	if(N == 1) {
		cout << a[1] << "\n";
	}
	else if(P == 1) {
		cout << a[b[1]] << "\n";
	}
	else if(Q == 1) {
		cout << a[1] + a[2] << "\n";
	}
	else {
		cout << max(a[1], a[2]) << "\n";
	}
}
