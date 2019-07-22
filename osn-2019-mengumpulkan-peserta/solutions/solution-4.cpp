#include <bits/stdc++.h>
using namespace std;

#define n 100005

int val[n], pref[n];

int main() {
	int R, C, count = 0;
	cin >> R >> C;
	
	for(int i = 1; i <= C; i++) {
		char ch;
		cin >> ch;
		if(ch == '1') val[i] = 1;
		count += val[i];
		pref[i] = count;
	}
	
	int mini = 1e9;
	
	for(int i = 1; i <= C; i++) {
		
		int awal = i;
		int akhir = i + count - 1;
		
		mini = min(mini, count - (pref[akhir] - pref[awal-1]));
	}
	
	cout << mini << "\n";
}
