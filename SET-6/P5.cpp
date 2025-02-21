#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;

const ll INF = 1e18;

void solve() {
  int n, m;
  cin >> n >> m;

  vector<vector<ll>> dist(n, vector<ll>(n, INF));
  for (int i = 0; i < m; ++i) {
    int u, v, w;
    cin >> u >> v >> w;
    dist[u][v] = w;
  }

  for (int k = 0; k < n; ++k) {
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
      }
    }
  }

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (i == j) {
        continue;
      }
      if (dist[i][j] == INF) {
        dist[i][j] = -1;
      }
      cout << i << ' ' << j << ' ' << dist[i][j] << "\n";
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