#include <bits/stdc++.h>
using namespace std;

#define f first
#define s second

long long R, C, Q, ans[4], r[4], c[4];

int main(){
	cin >> R >> C >> Q;
	pair<int, int> ask[] = {
		{1, 1}, {1, C},			// 0, 1
		{R, 1}, {R, C}			// 2, 3
	};
	for (int i=0;i<4;i++){
		cout << "? " << ask[i].f << " " << ask[i].s << "\n";
		cout << flush;
		cin >> ans[i];
	}
	r[0] = (ans[0] + ans[1] - C + 3) / 2;	// 0 & 1
	c[0] = ans[0] + 2 - r[0];
	r[1] = (ans[1] - ans[3] + R + 1) / 2;	// 1 & 3
	c[1] = R + C - ans[3] - r[1];
	c[2] = (ans[2] - ans[3] + C + 1) / 2;	// 3 & 2
	r[2] = R + C - ans[3] - c[2];
	r[3] = (ans[0] - ans[2] + R + 1) / 2;	// 2 & 0
	c[3] = ans[0] + 2 - r[3];
	int ok = 0;
	if (1 <= r[0] && r[0] <= R && 1 <= c[0] && c[0] <= C){
		cout << "? " << r[0] << " " << c[0] << "\n";
		cout << flush;
		cin >> ans[0];
		if (!ans[0]){
			cout << "! " << r[0] << " " << c[0] << " " <<
					r[2] << " " << c[2] << "\n";
			ok = 1;
		}
	}
	if (!ok){
		cout << "! " << r[1] << " " << c[1] << " " <<
				r[3] << " " << c[3] << "\n";
	}
	cout << flush;
	return 0;
}
