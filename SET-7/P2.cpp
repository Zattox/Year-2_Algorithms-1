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
  int n, m;
  cin >> n >> m;
  vector<vector<int>> gr(n);
  for (int i = 0; i < n; ++i) {
    int x;
    cin >> x;
    while (x != 0) {
      gr[i].push_back(x - 1);
      cin >> x;
    }
  }

  int ans = 0;
  vector<int> inLeft(m, -1);
  for (int i = 0; i < n; ++i) {
    vector<bool> used(n, false);
    ans += dfs(i, inLeft, used, gr);
  }

  cout << ans << "\n";
  for (int i = 0; i < m; ++i) {
    if (inLeft[i] != -1) {
      cout << inLeft[i] + 1 << ' ' << i + 1 << "\n";
    }
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