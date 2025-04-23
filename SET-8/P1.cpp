#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

void solve() {
  string s;
  cin >> s;

  int n = s.length();
  vector<int> p(n, 0);
  for (int i = 1; i < n; ++i) {
    int cur = p[i - 1];
    while (cur > 0 && s[i] != s[cur]) {
      cur = p[cur - 1];
    }
    if (s[i] == s[cur])
      ++cur;
    p[i] = cur;
  }

  for (auto el : p) {
    cout << el << ' ';
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