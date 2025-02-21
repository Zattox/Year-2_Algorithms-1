#include <bits/stdc++.h>

using namespace std;

const int INF = 2e9;
const int INF_WEIGHT = 1e9;

vector<pair<int, int>> findSpanningTree(vector<set<pair<int, int>>> &graph) {
  int n = (int) graph.size();
  vector<pair<int, int>> spanningTree;
  vector<bool> used(n, false);
  vector<int> min_edge(n, INF), best_edge(n, -1);

  min_edge[0] = 0;
  for (int _ = 0; _ < n; ++_) {
    int v = -1;
    for (int u = 0; u < n; ++u) {
      if (!used[u] && (v == -1 || min_edge[u] < min_edge[v])) {
        v = u;
      }
    }
    used[v] = true;

    if (v != 0) {
      spanningTree.emplace_back(v, best_edge[v]);
    }
    for (auto edge : graph[v]) {
      int u = edge.first, w = edge.second;
      if (!used[u] && w < min_edge[u]) {
        min_edge[u] = w;
        best_edge[u] = v;
      }
    }
  }

  return spanningTree;
}

int calculateCostSpanningTree(vector<pair<int, int>> &spanningTree, map<pair<int, int>, int> &edges) {
  int cost = 0;
  for (auto edge : spanningTree) {
    cost += edges[edge];
  }
  return cost;
}

void solve() {
  int n, m;
  cin >> n >> m;
  map<pair<int, int>, int> edges;
  vector<set<pair<int, int>>> graph(n);
  for (int i = 0; i < m; ++i) {
    int u, v, w;
    cin >> u >> v >> w;
    --u;
    --v;
    graph[u].insert({v, w});
    graph[v].insert({u, w});
    edges[{u, v}] = w;
    edges[{v, u}] = w;
  }

  auto firstSpanningTree = findSpanningTree(graph);
  int costFirstSpanningTree = calculateCostSpanningTree(firstSpanningTree, edges);

  int costSecondSpanningTree = INF;
  for (auto &edge : firstSpanningTree) {
    int u = edge.first;
    int v = edge.second;
    int w = edges[edge];

    graph[u].erase({v, w});
    graph[v].erase({u, w});
    graph[u].insert({v, INF_WEIGHT});
    graph[v].insert({u, INF_WEIGHT});
    edges[{u, v}] = INF_WEIGHT;
    edges[{v, u}] = INF_WEIGHT;

    auto currentSpanningTree = findSpanningTree(graph);
    int currentCost = calculateCostSpanningTree(currentSpanningTree, edges);
    costSecondSpanningTree = min(costSecondSpanningTree, currentCost);

    edges[{u, v}] = w;
    edges[{v, u}] = w;
    graph[u].erase({v, INF_WEIGHT});
    graph[v].erase({u, INF_WEIGHT});
    graph[u].insert({v, w});
    graph[v].insert({u, w});
  }

  cout << costFirstSpanningTree << ' ' << costSecondSpanningTree;
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