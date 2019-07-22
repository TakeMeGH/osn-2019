#include <bits/stdc++.h>
#define pb push_back
using namespace std;

#define n 200005

long long a[n]; 

bool b[n], c[n];

int main() {
	int N, P, Q;
	cin >> N >> P >> Q;
	
	for(int i = 1; i <= N; i++) {
		cin >> a[i];
	}
		
	for(int i = 1; i <= P; i++) {
		cin >> b[i];
	}
	
	for(int i = 1; i <= Q; i++) {
		cin >> c[i];
	}
	
	long long sum = 0;
	
	sort(a + 1, a + N + 1, greater<int>());
	
	for(int i = 1; i <= N; i++) {
		if(i % 2) sum += a[i];
	}
	
	cout << sum << "\n";
	
}
