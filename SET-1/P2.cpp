#include <bits/stdc++.h>

using namespace std;

int find_score(vector<int> &a, vector<int> &b) {
  int score = 0;
  for (int i = 0; i < (int) a.size(); ++i) {
    if (a[i] != b[i]) {
      ++score;
    }
  }
  return score;
}

void solve() {
  int n;
  cin >> n;
  vector<int> arr(n), scores;
  for (int i = 0; i < n; ++i) {
    cin >> arr[i];
  }

  set<vector<int>> all_vec;
  for (int delta = 1; delta <= n; ++delta) {
    vector<int> a;
    for (int i = 0; i < n; ++i) {
      a.push_back(arr[(i + delta) % n]);
    }
    all_vec.insert(a);
  }

  int ans = 0;
  int max_score = 0;
  for (auto el : all_vec) {
    int score = find_score(arr, el);
    if (score > max_score) {
      max_score = score;
      ans = 0;
    }
    if (score == max_score) {
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
