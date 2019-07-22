#include <bits/stdc++.h>
#define pb push_back
using namespace std;

vector<int> sort_goblok(vector<int> v) {
	for(int i = 0; i < v.size(); i++) {
		for(int j = i + 1; j < v.size(); j++) {
			if(v[j] > v[i]) {
				swap(v[j], v[i]);
			}
		}
	}
	
	return v;
}

int main() {
	int N, P, Q;
	cin >> N >> P >> Q;
	long long a[N+5], b[N+5], c[N+5];
	
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
	
	vector<int> v;
	
	for(int i = 1; i <= P; i++) {
		bool valid = 0;
		for(int j = 1; j <= Q; j++) {
			if(b[i] == c[j]) {
				v.pb(a[b[i]]);
				valid = 1;
			}
		}
		if(!valid) sum += a[b[i]];
	}
	
	v = sort_goblok(v);
	
	for(int i = 0; i < v.size(); i++){
		if((i % 2) == 0) {
			sum += v[i];
		}
	}
	
	cout << sum << "\n";
}
