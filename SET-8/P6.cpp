#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

void solve() {
  string s;
  cin >> s;
  ll n = s.length(), ans = 0;

  vector<int> d1(n);
  int l = 0, r = -1;
  for (int i = 0; i < n; ++i) {
    int k = 0;
    if (i <= r)
      k = min(r - i + 1, d1[r - i + l]);
    while (i + k < n && i - k >= 0 && s[i + k] == s[i - k])
      ++k;
    d1[i] = k;
    if (i + k -1> r) {
      l = i - k + 1;
      r = i + k - 1;
    }
  }

  vector<int> d2(n);
  l = 0, r = -1;
  for (int i = 0; i < n; ++i) {
    int k = 0;
    if (i <= r)
      k = min(r - i + 1, d2[r - i + l + 1]);
    while (i + k < n && i - k - 1 >= 0 && s[i + k] == s[i - k - 1])
      ++k;
    d2[i] = k;
    if (i + k - 1 > r) {
      l = i - k;
      r = i + k - 1;
    }
  }
  for (int i = 0; i < n; ++i) {
    ans += d1[i] + d2[i];
  }

  cout << ans;
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