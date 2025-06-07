#include <bits/stdc++.h>

using namespace std;

void solve() {
  int n, l, r;
  cin >> n >> l >> r;

  int len = n;
  vector<int> v(n);
  --l;
  --r;

  int pick = (r + l) / 2;
  v[pick] = n--;

  int pos = pick, s = 1;
  while (n > 0) {
    pos += s;
    if (pos >= 0 && pos < len) {
      v[pos] = n--;
    }
    if (s > 0) {
      s = -s - 1;
    } else {
      s = -s + 1;
    }
  }

  for (int i = 0; i < len; ++i) {
    cout << v[i] << ' ';
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  solve();
}