#include <bits/stdc++.h>

using namespace std;

void solve() {
  int n, s;

  cin >> n >> s;
  vector<int> w(n + 1), c(n + 1);

  for (int i = 1; i <= n; ++i) {
    cin >> w[i];
  }
  for (int i = 1; i <= n; ++i) {
    cin >> c[i];
  }

  vector<vector<int>> dp(n + 1, vector<int>(s + 1, 0));
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= s; ++j) {
      if (j >= w[i]) {
        dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - w[i]] + c[i]);
      } else {
        dp[i][j] = dp[i - 1][j];
      }
    }
  }

  cout << dp[n][s];
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  solve();
}