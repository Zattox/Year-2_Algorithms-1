#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

void solve() {
  string s1, t;
  cin >> t >> s1;

  string s;
  s = t + "#" + s1;
  int n = s.size();
  vector<int> pref(n);
  pref[0] = 0;
  for (int i = 1; i < n; ++i) {
    int cur = pref[i - 1];
    while (cur > 0 && s[i] != s[cur])
      cur = pref[cur - 1];
    if (s[i] == s[cur])
      ++cur;
    pref[i] = cur;
  }

  vector<int> ans;
  for (int i = 2 * t.size(); i < n; ++i) {
    if (pref[i] == (int)t.size()) {
      ans.push_back(i - 2 * (int)t.size());
    }
  }

  cout << ans.size() << '\n';
  for (auto el : ans) {
    cout << el << '\n';
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int t = 1;
  //cin >> t;
  while (t > 0) {
    solve();
    --t;
  }
}