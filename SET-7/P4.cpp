#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

bool dfs(int v, vector<int> &inLeft, vector<bool> &used, vector<vector<int>> &gr) {
  if (used[v]) return false;
  used[v] = true;
  for (auto u : gr[v]) {
    if (inLeft[u] == -1 || dfs(inLeft[u], inLeft, used, gr)) {
      inLeft[u] = v;
      return true;
    }
  }
  return false;
}

void solve() {
  int n, m, a, b;
  cin >> n >> m >> a >> b;
  vector<string> s(n);
  for (int i = 0; i < n; ++i) {
    cin >> s[i];
  }

  int empty = 0;
  vector<vector<int>> gr(n * m);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (s[i][j] == '.')
        continue;
      ++empty;
      if ((i + j) % 2)
        continue;

      if (j > 0 && (s[i][j - 1] == '*'))
        gr[i * m + j].push_back(i * m + j - 1);

      if ((j < m - 1) && (s[i][j + 1] == '*'))
        gr[i * m + j].push_back(i * m + j + 1);

      if (i > 0 && (s[i - 1][j] == '*'))
        gr[i * m + j].push_back((i - 1) * m + j);

      if ((i < n - 1) && (s[i + 1][j] == '*'))
        gr[i * m + j].push_back((i + 1) * m + j);
    }
  }

  if (2 * b <= a) {
    cout << empty * b;
    return;
  }

  vector<int> inLeft(n * m, -1);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if ((i + j) % 2)
        continue;
      vector<bool> used(n * m, false);
      bool flag = dfs(i * m + j, inLeft, used, gr);
    }
  }

  int ans = 0;
  for (int i = 0; i < n * m; ++i) {
    if (inLeft[i] != -1)
      ++ans;
  }
  cout << ans * a + (empty - 2 * ans) * b;
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