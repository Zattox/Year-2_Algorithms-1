#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll INF = 1e18;

struct Edge {
  int u, v;
  ll cost;
};

void dfs(int v, vector<bool> &used, vector<bool> &in_cycle, vector<vector<int>> &gr) {
  used[v] = true;
  in_cycle[v] = true;
  for (int u : gr[v]) {
    if (!used[u]) {
      dfs(u, used, in_cycle, gr);
    }
  }
}

void solve() {
  int n, m;
  cin >> n >> m;

  vector<Edge> edges(m);
  vector<vector<int>> gr(n);
  for (int i = 0; i < m; ++i) {
    int u, v;
    ll w;
    cin >> u >> v >> w;
    gr[u].push_back(v);
    edges[i] = {u, v, w};
  }

  vector<ll> dist(n, INF);
  vector<bool> in_cycle(n, false);
  dist[0] = 0;
  for (int i = 0; i < n; ++i) {
    for (auto e : edges) {
      if (dist[e.u] != INF && dist[e.u] + e.cost < dist[e.v]) {
        if (i == n - 1) {
          in_cycle[e.v] = true;
        }
        dist[e.v] = dist[e.u] + e.cost;
      }
    }
  }

  vector<bool> used(n, false);
  for (int s = 0; s < n; ++s) {
    if (!used[s] && in_cycle[s]) {
      dfs(s, used, in_cycle, gr);
    }
  }

  for (int i = 1; i < n; ++i) {
    if (in_cycle[i]) {
      cout << "-inf\n";
    } else {
      cout << dist[i] << '\n';
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  solve();
  return 0;
}