#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;

void topsort(int u, vector<bool> &used,
             vector<vector<int>> &graph, vector<int> &order) {
  used[u] = true;
  for (int v : graph[u]) {
    if (!used[v]) {
      topsort(v, used, graph, order);
    }
  }
  order.push_back(u);
}

void dfs(int u, int current_color, vector<bool> &used,
         vector<vector<int>> &reverse_graph, vector<int> &color) {
  color[u] = current_color;
  used[u] = true;
  for (int v : reverse_graph[u]) {
    if (!used[v]) {
      dfs(v, current_color, used, reverse_graph, color);
    }
  }
}

void solve() {
  int n, m;
  cin >> n >> m;
  vector<vector<int>> graph(n), reverse_graph(n);
  for (int i = 0; i < m; ++i) {
    int u, v;
    cin >> u >> v;
    --u;
    --v;
    graph[u].push_back(v);
    reverse_graph[v].push_back(u);
  }

  vector<int> order;
  vector<bool> used(n, false);
  for (int i = 0; i < n; ++i) {
    if (!used[i]) {
      topsort(i, used, graph, order);
    }
  }
  std::reverse(order.begin(), order.end());

  vector<int> color(n);
  used.assign(n, false);
  int current_color = 1;
  for (int u : order) {
    if (!used[u]) {
      dfs(u, current_color, used, reverse_graph, color);
      ++current_color;
    }
  }

  cout << current_color - 1 << "\n";
  for (auto el : color) {
    cout << el << ' ';
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