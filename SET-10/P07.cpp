#include <bits/stdc++.h>

typedef long long ll;
using namespace std;

void solve() {
  ll L, n;

  cin >> L >> n;

  vector<ll> mas(n + 2);
  mas[0] = 0;
  for (int i = 1; i <= n; ++i)
    cin >> mas[i];
  mas[n + 1] = L;

  vector<vector<ll>> dp(n + 2, vector<ll>(n + 2));
  for (int r = 2; r < n + 2; ++r) {
    for (int l = 0; l < n + 2 - r; ++l) {
      dp[l][l + r] = mas[l + r] - mas[l];
      ll mini = 1e+10;
      for (int k = l + 1; k < l + r; ++k) {
        mini = min(mini, dp[l][k] + dp[k][l + r]);
      }
      dp[l][l + r] += mini;
    }
  }

  cout << dp[0][n + 1];
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  solve();
}