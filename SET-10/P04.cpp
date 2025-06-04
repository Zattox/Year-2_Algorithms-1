#include <bits/stdc++.h>

typedef long long ll;
using namespace std;

const ll MOD = 1e9 + 7;

void solve() {
  int n;
  cin >> n;
  vector<ll> dp(n + 1, 0);
  dp[0] = 1;
  dp[1] = 2;
  for (int i = 2; i <= n; ++i) {
    dp[i] = (dp[i - 1] + dp[i - 2]) % MOD;
  }

  cout << dp[n];
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  solve();
}