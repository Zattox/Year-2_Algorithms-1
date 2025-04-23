#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

void solve() {
  string s;
  cin >> s;

  int n = s.length(), k;
  vector<int> p(n, 0);

  for (int i = 1; i < n; ++i) {
    int cur = p[i - 1];
    while (cur > 0 && s[i] != s[cur])
      cur = p[cur - 1];
    if (s[i] == s[cur]) ++cur;

    p[i] = cur;
  }

  k = n - p[n - 1];
  cout << k;
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