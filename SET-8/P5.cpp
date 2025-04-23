#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

void solve(string &str1, string &str2) {
  string s1 = '/' + str1, s2 = '/' + str2;
  int n = s1.length(), m = s2.length();

  vector<vector<int>> dp(n, vector<int>(m));
  for (int i = 0; i < n; ++i) {
    dp[i][0] = i;
  }
  for (int i = 0; i < m; ++i) {
    dp[0][i] = i;
  }

  for (int i = 1; i < n; ++i) {
    for (int j = 1; j < m; ++j) {
      if (s1[i] == s2[j]) {
        dp[i][j] = dp[i - 1][j - 1];
      }
      else {
        dp[i][j] = min(dp[i - 1][j - 1] + 1, min(dp[i - 1][j], dp[i][j - 1]) + 1);
      }
    }
  }

  cout << dp[n - 1][m - 1] << ' ';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  string t_str;
  getline(cin, t_str);
  int t = atoi(t_str.c_str());

  while (t > 0) {
    string s1, s2;
    getline(cin, s1);
    getline(cin, s2);
    solve(s1, s2);
    --t;
  }
}