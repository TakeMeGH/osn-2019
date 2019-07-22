// this version is when we still bruteforce to finding the rectangle but using prefix sum to compute
#include <bits/stdc++.h>
using namespace std;

#define n 2005

int R, C;
int val[n], sum, pref[n];

int getArrayIndex(int i, int j) {
	if(i == 0 || j == 0) return 0;
	return (i - 1) * C  + j;
}	

pair<int,int> getCoordinateIndex(int pos) {
	return {(pos - 1) / C + 1 , (pos - 1) % C + 1};
}

pair<int,int> computeArea(int l1, int r1, int l2, int r2) {
	int area = (r2 - r1 + 1) * (l2 - l1 + 1);
	
	return {area, pref[getArrayIndex(l2, r2)] - pref[getArrayIndex(l2, r1 - 1)] - pref[getArrayIndex(l1 - 1, r2)] + pref[getArrayIndex(l1 - 1, r1 - 1)]};
}

int main() {
	cin >> R >> C;
	
	for(int i = 1; i <= R * C; i++) {
		char ch;
		cin >> ch;
		if(ch == '1') val[i] = 1;
		sum += val[i];
	}
	
	for(int i = 1; i <= R; i++) {
		for(int j = 1; j <= C; j++) {
			pref[getArrayIndex(i, j)] =  val[getArrayIndex(i, j)] + pref[getArrayIndex(i - 1, j)] + pref[getArrayIndex(i, j - 1)] - pref[getArrayIndex(i - 1, j - 1)];
		}
	}
	
	int mini = 1e9;
	
	for(int i = 1; i <= R; i++) {
		for(int j = 1; j <= C; j++) {
			for(int ii = 1; ii <= i; ii++) {
				for(int jj = 1; jj <= j; jj++) {
					pair<int,int> tmp = computeArea(ii, jj, i , j);
					
					if(tmp.first == sum) {
						mini = min(mini, sum - tmp.second);
					}
				}
			}
		}
	}
	
	if (mini == 1e9) mini = -1;
	
	cout << mini << "\n";
}
