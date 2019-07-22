#include <bits/stdc++.h>
#define pb push_back
using namespace std;

#define n 200005

int a[n]; 

bool b[n], c[n];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int N, P, Q;
	cin >> N >> P >> Q;

	
	for(int i = 1; i <= N; i++) {
		cin >> a[i];
	}
	
	int val = a[1];
	
	for(int i = 1; i <= P; i++) {
		int tmp; 
		cin >> tmp;
		b[tmp] = 1;
	}
	
	for(int i = 1; i <= Q; i++) {
		int tmp;
		cin >> tmp;
		c[tmp] = 1;
	}
	
	long long sum = 0, banyak = 0;
	
	for(int i = 1; i <= N; i++) {
		if(b[i] && c[i]) banyak++;
		else if(b[i]) sum += val;
	}
	
	sum += (banyak + 1) / 2 * val;
	cout << sum << "\n";
}
