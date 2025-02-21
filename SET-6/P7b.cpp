#include <bits/stdc++.h>

using namespace std;

void topsort(int v, vector<vector<int>> &graph,
             vector<bool> &used, vector<int> &order) {
  used[v] = true;
  for (auto u : graph[v]) {
    if (!used[u]) {
      topsort(u, graph, used, order);
    }
  }
  order.push_back(v);
}

void dfs(int v, int current_color, vector<vector<int>> &reverse_graph,
         vector<bool> &used, vector<int> &color) {
  color[v] = current_color;
  used[v] = true;
  for (auto u : reverse_graph[v]) {
    if (!used[u]) {
      dfs(u, current_color, reverse_graph, used, color);
    }
  }
}

void solve(int n, int m) {
  vector<int> color(2 * n, -1);
  vector<bool> used(2 * n, false);
  vector<vector<int>> graph(2 * n), reverse_graph(2 * n);

  for (int _ = 0; _ < m; ++_) {
    int i1, e1, i2, e2;
    cin >> i1 >> e1 >> i2 >> e2;

    int u = i2 + n * (!e2);
    int v = i1 + n * e1;
    graph[u].push_back(v);
    reverse_graph[v].push_back(u);

    u = i1 + n * (!e1);
    v = i2 + n * e2;
    graph[u].push_back(v);
    reverse_graph[v].push_back(u);
  }

  vector<int> order;
  for (int i = 0; i < 2 * n; ++i) {
    if (!used[i]) {
      topsort(i, graph, used, order);
    }
  }
  reverse(order.begin(), order.end());

  int current_color = 1;
  used.assign(2 * n, false);
  for (auto v : order) {
    if (!used[v]) {
      dfs(v, current_color, reverse_graph, used, color);
      ++current_color;
    }
  }

  for (int i = 0; i < n; ++i) {
    int ans;
    if (color[i] > color[i + n]) {
      ans = 0;
    } else {
      ans = 1;
    }
    cout << ans;
  }
  cout << "\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int n, m;
  while (cin >> n >> m) {
    solve(n, m);
  }
}