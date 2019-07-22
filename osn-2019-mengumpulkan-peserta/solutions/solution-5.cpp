#include <bits/stdc++.h>
using namespace std;

#define n 205

int R, C;
int val[n], sum;

int getArrayIndex(int i, int j) {
	return (i - 1) * C  + j;
}	

pair<int,int> getCoordinateIndex(int pos) {
	return {(pos - 1) / C  + 1, (pos - 1) % C + 1};
}

int main() {
	cin >> R >> C;
	
	for(int i = 1; i <= R * C; i++) {
		char ch;
		cin >> ch;
		if(ch == '1') val[i] = 1;
		sum += val[i];
	}
	
	int mini = 1e9;
	
	for(int i = 1; i <= R; i++) {
		for(int j = 1; j <= C; j++) {
			for(int ii = 1; ii <= i; ii++) {
				for(int jj = 1; jj <= j; jj++) {
					int tmpSum = 0, tmpBanyak = 0;
					for(int iii=ii; iii <= i; iii++) {
						for(int jjj=jj;jjj<=j;jjj++) {
							tmpBanyak++;
							tmpSum += val[getArrayIndex(iii,jjj)];
						}	
					}
					if(tmpBanyak == sum) {
						mini = min(mini, sum - tmpSum);
					}
				}
			}
		}
	}
	
	if(mini == 1e9) mini = -1;
	
	cout << mini << "\n";
}
