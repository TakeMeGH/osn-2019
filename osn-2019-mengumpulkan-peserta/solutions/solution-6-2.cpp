// this version is when we use factorization to find the rectangle but still bruteforce to count one.
#include <bits/stdc++.h>
using namespace std;

#define n 2005

int R, C;
int val[n], sum;

int getArrayIndex(int i, int j) {
	if(i == 0 || j == 0) return 0;
	return (i - 1) * C  + j;
}

pair<int,int> getCoordinateIndex(int pos) {
	return {(pos - 1) / C + 1 , (pos - 1) % C + 1};
}

pair<int,int> computeArea(int l1, int r1, int l2, int r2) {
	if(l1 <= 0 || r1 <= 0) return {0, 0};
	int area = (r2 - r1 + 1) * (l2 - l1 + 1);
	int sum = 0;

	for(int i = l1; i <= l2; i++) {
		for(int j = r1; j <= r2; j++) {
			sum += val[getArrayIndex(i, j)];
		}
	}

	return {area, sum};
}

int main() {
	cin >> R >> C;

	for(int i = 1; i <= R * C; i++) {
		char ch;
		cin >> ch;
		if(ch == '1') val[i] = 1;
		sum += val[i];
	}

	vector<int> listDivisor;

	for(int i = 1; i <= sum; i++) {
		if (sum % i == 0) {
			listDivisor.push_back(i);
		}
	}

	int mini = 1e9;

	for(int i = 1; i <= R; i++) {
		for(int j = 1; j <= C; j++) {
			for(int k = 0; k < listDivisor.size(); k++) {
				int divisor = listDivisor[k];
				int anotherDivisor = sum / divisor;

				int l1 = i - divisor + 1, r1 = j - anotherDivisor + 1;

				pair<int,int> tmp = computeArea(l1, r1, i , j);

				if(tmp.first == sum) {
					mini = min(mini, sum - tmp.second);
				}
			}
		}
	}

	if (mini == 1e9) mini = -1;

	cout << mini << "\n";
}
