#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int INF = 2e9;

struct DSU {
  vector<int> parent, rk;

  DSU(int n) : parent(n), rk(n, 0) {
    for (int i = 0; i < n; ++i) {
      parent[i] = i;
    }
  }

  int find(int v) {
    if (parent[v] == v)
      return v;
    return parent[v] = find(parent[v]);
  }

  void unite(int u, int v) {
    u = find(u), v = find(v);
    if (u == v)
      return;
    if (rk[u] > rk[v])
      swap(u, v);
    if (rk[u] == rk[v])
      ++rk[v];
    parent[u] = v;
  }
};

struct Edge {
  int to, capacity, rev;
};

bool bfs(int start, int finish, vector<int> &level, vector<vector<Edge>> &gr) {
  fill(level.begin(), level.end(), -1);
  queue<int> q;

  level[start] = 0;
  q.push(start);
  while (!q.empty()) {
    int u = q.front();
    q.pop();

    for (auto &el : gr[u]) {
      if (el.capacity > 0 && level[el.to] < 0) {
        level[el.to] = level[u] + 1;
        q.push(el.to);
      }
    }
  }

  return level[finish] != -1;
}

int dfs(int cur, int finish, int flow, vector<int> &ptr, vector<int> &level, vector<vector<Edge>> &gr) {
  if (cur == finish)
    return flow;

  for (int &v = ptr[cur]; v < gr[cur].size(); ++v) {
    Edge &el = gr[cur][v];

    if (el.capacity > 0 && level[cur] + 1 == level[el.to]) {
      int pushed = dfs(el.to, finish, min(flow, el.capacity), ptr, level, gr);
      if (pushed > 0) {
        el.capacity -= pushed;
        gr[el.to][el.rev].capacity += pushed;
        return pushed;
      }
    }
  }

  return 0;
}

ll findMaxFlow(int totalVertices, int start, int finish, int maxPossible, vector<vector<Edge>> &gr) {
  vector<int> level(totalVertices), ptr(totalVertices);
  int totalFlow = 0;
  while (bfs(start, finish, level, gr)) {
    fill(ptr.begin(), ptr.end(), 0);
    while (int pushed = dfs(start, finish, min(INF, maxPossible - totalFlow), ptr, level, gr)) {
      totalFlow += pushed;
      if (totalFlow >= maxPossible)
        return totalFlow;
    }
  }
  return totalFlow;
}

void solve() {
  int n, m, k;
  cin >> n >> m >> k;

  int nextId = 0;
  unordered_map<string, int> nameToId;

  vector<int> degree;
  vector<pair<int, int>> dsuEdges(m);
  vector<tuple<int, int, int>> edges(m);
  for (int i = 0; i < m; ++i) {
    string a, b;
    cin >> a >> b;
    if (nameToId.find(a) == nameToId.end()) {
      nameToId[a] = nextId++;
    }
    if (nameToId.find(b) == nameToId.end()) {
      nameToId[b] = nextId++;
    }

    int u = nameToId[a], v = nameToId[b];
    edges[i] = {u, v, 1};
    dsuEdges[i] = {u, v};

    if (degree.size() < nextId) {
      degree.resize(nextId, 0);
    }
    degree[u]++;
    degree[v]++;
  }

  vector<pair<string, string>> queries;
  queries.reserve(k);
  for (int i = 0; i < k; ++i) {
    string a, b;
    cin >> a >> b;
    queries.push_back({a, b});
    if (nameToId.find(a) == nameToId.end()) {
      nameToId[a] = nextId++;
      if (degree.size() < nextId)
        degree.resize(nextId, 0);
    }
    if (nameToId.find(b) == nameToId.end()) {
      nameToId[b] = nextId++;
      if (degree.size() < nextId)
        degree.resize(nextId, 0);
    }
  }

  int totalVertices = nextId;
  DSU dsu(totalVertices);
  for (const auto &edge : dsuEdges) {
    dsu.unite(edge.first, edge.second);
  }

  vector<vector<Edge>> baseGraph(totalVertices);
  for (auto &edge : edges) {
    int u, v, capacity;
    tie(u, v, capacity) = edge;
    baseGraph[u].push_back({v, capacity, (int) baseGraph[v].size()});
    baseGraph[v].push_back({u, capacity, (int) (baseGraph[u].size() - 1)});
  }

  for (const auto &query : queries) {
    string sName = query.first, tName = query.second;
    int s = nameToId[sName], t = nameToId[tName];

    if (s == t) {
      cout << 0 << "\n";
      continue;
    }

    if (dsu.find(s) != dsu.find(t)) {
      cout << 0 << "\n";
    } else {
      int maxPossible = min(degree[s], degree[t]);
      vector<vector<Edge>> graph = baseGraph;
      cout << findMaxFlow(totalVertices, s, t, maxPossible, graph) << "\n";
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
  return 0;
}