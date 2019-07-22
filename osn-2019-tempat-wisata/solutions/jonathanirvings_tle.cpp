#include <bits/stdc++.h>
using namespace std;

int main() {
  int N, M;
  scanf("%d %d", &N, &M);

  vector<int> A(N), B(N);
  vector<int> answer(N);

  vector<int> places;

  for (int i = 0; i < N; ++i) {
    scanf("%d %d", &A[i], &B[i]);
    places.push_back(A[i]);
    places.push_back(B[i]);
  }

  sort(places.begin(), places.end());
  places.erase(unique(places.begin(), places.end()), places.end());

  unordered_map<int, int> placesMapping;
  for (int i = 0; i < places.size(); ++i) {
    placesMapping[places[i]] = i;
  }

  vector<vector<int>> in(places.size()), out(places.size());
  for (int i = 0; i < N; ++i) {
    in[placesMapping[A[i]]].push_back(i);
    out[placesMapping[B[i]]].push_back(i);
  }

  unordered_set<int> onlineUsers;

  for (int p = 0; p < places.size(); ++p) {
    for (int user : in[p]) {
      for (int onlineUser : onlineUsers) {
        ++answer[onlineUser];
      }
      answer[user] = onlineUsers.size();
      onlineUsers.insert(user);
    }
    for (int user : out[p]) {
      onlineUsers.erase(user);
    }
  }

  for (int i = 0; i < N; ++i) {
    printf("%d\n", answer[i]);
  }
}
