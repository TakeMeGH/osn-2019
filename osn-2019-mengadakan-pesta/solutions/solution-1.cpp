#include <bits/stdc++.h>
using namespace std;

int main() {
	int N, M, Q;
	cin >> N >> M >> Q;
	cout << "? 1 1" << endl;
	int a;
	cin >> a;
	if(a != 1) {
		cout << "! 1" << endl;
	}
	else {
		int b;
		cin >> b;
		if(b == 2) cout << "! 3" << endl;
		else cout << "! 2" << endl;
	}

}
