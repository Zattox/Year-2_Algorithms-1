#include <bits/stdc++.h>

using namespace std;

bool cmp(const pair<int, int> &p1, const pair<int, int> &p2) {
  if (p1.second == p2.second) {
    return p1.first > p2.first;
  }
  return p1.second < p2.second;
}

void solve() {
  int n;
  cin >> n;
  vector<pair<int, int>> a(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i].first >> a[i].second;
  }

  std::sort(a.begin(), a.end(), cmp);

  vector<int> ans = {a[0].second};
  int cur = ans[0];
  for (auto el : a) {
    if (el.first > cur) {
      cur = el.second;
      ans.push_back(cur);
    }
  }

  cout << ans.size() << "\n";
  for (auto el : ans) {
    cout << el << ' ';
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  solve();
}