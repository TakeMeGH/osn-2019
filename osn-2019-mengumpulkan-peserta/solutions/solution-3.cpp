#include <bits/stdc++.h>
using namespace std;

#define n 2005

int val[n];

int main() {
	int R, C, count = 0;
	cin >> R >> C;
	
	for(int i = 1; i <= C; i++) {
		char ch;
		cin >> ch;
		if(ch == '1') val[i] = 1;
		count += val[i];
	}
	
	int mini = 1e9;
	
	for(int i = 1; i <= C; i++) {
		
		int awal = i;
		int akhir = i + count - 1;
		int sum = 0;
		
		if (akhir > C) break;
		
		for(int j = awal; j <= akhir; j++) {
			sum += val[j];
		}
		
		mini = min(mini, count - sum);
	}
	
	cout << mini << "\n";
}
