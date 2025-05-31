#include <bits/stdc++.h>

typedef long long ll;
using namespace std;

void solve() {
  int n, W1, W2;
  cin >> n >> W1 >> W2;

  vector<ll> v(n), w1(n), w2(n);
  for (int i = 0; i < n; ++i) {
    cin >> v[i] >> w1[i] >> w2[i];
  }

  vector<vector<ll>> prev(W1 + 1, vector<ll>(W2 + 1, 0));
  vector<vector<ll>> cur(W1 + 1, vector<ll>(W2 + 1, 0));

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j <= W1; ++j) {
      for (int k = 0; k <= W2; ++k) {
        cur[j][k] = prev[j][k];
        if (j - w1[i] >= 0 && k - w2[i] >= 0) {
          ll take = prev[j - w1[i]][k - w2[i]] + v[i];
          cur[j][k] = max(cur[j][k], take);
        }
      }
    }
    swap(prev, cur);
  }

  cout << prev[W1][W2] << "\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;
  // cin >> t;
  while (t > 0) {
    solve();
    --t;
  }

  return 0;
}