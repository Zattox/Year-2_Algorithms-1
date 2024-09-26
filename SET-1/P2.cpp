#include <bits/stdc++.h>

using namespace std;

void solve() {
  int n;
  cin >> n;
  vector<int> arr(n), scores;
  for (int i = 0; i < n; ++i) {
    cin >> arr[i];
  }

  int max_score = 0;
  scores.push_back(0);
  for (int i = 1; i < n; ++i) {
    int score = 0;
    for (int j = 0; j < n; ++j) {
      if (arr[j] != arr[(i + j) % n]){
        ++score;
      }
    }
    max_score = max(score, max_score);
    scores.push_back(score);
  }

  int ans = 0;
  for (auto sc : scores) {
    if (sc == max_score) {
      ++ans;
    }
  }
  cout << ans;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int t = 1;
  while (t > 0) {
    solve();
    --t;
  }

  return 0;
}
