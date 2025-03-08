#include <bits/stdc++.h>
using namespace std;

const int INF = 2e9;

struct Edge {
  int to, capacity, flow, rev;
  bool used;
};

bool bfs(int start, int finish, vector<int> &level, vector<vector<Edge>> &gr) {
  fill(level.begin(), level.end(), -1);
  queue<int> q;
  level[start] = 0;
  q.push(start);

  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (auto &edge : gr[u]) {
      if (level[edge.to] < 0 && edge.flow < edge.capacity) {
        level[edge.to] = level[u] + 1;
        q.push(edge.to);
      }
    }
  }
  return level[finish] >= 0;
}

int dfs(int cur, int finish, int flow, vector<int> &ptr, vector<int> &level, vector<vector<Edge>> &gr) {
  if (cur == finish)
    return flow;

  for (int v = ptr[cur]; v < gr[cur].size(); ++v) {
    Edge &edge = gr[cur][v];
    if (edge.flow < edge.capacity && level[edge.to] == level[cur] + 1) {
      int pushed = dfs(edge.to, finish, min(flow, edge.capacity - edge.flow), ptr, level, gr);
      if (pushed > 0) {
        edge.flow += pushed;
        gr[edge.to][edge.rev].flow -= pushed;
        return pushed;
      }
    }
  }
  return 0;
}

int maxFlow(int start, int finish, vector<vector<Edge>> &gr, vector<int> &level, vector<int> &ptr) {
  int total_flow = 0;
  while (bfs(start, finish, level, gr)) {
    fill(ptr.begin(), ptr.end(), 0);
    while (int pushed = dfs(start, finish, INF, ptr, level, gr)) {
      total_flow += pushed;
    }
  }
  return total_flow;
}

bool findPath(const vector<vector<Edge>> &gr, int cur, int finish, vector<int> &path) {
  if (cur == finish) return true;

  for (const Edge &edge : gr[cur]) {
    if (edge.capacity == 1 && edge.flow == 1 && !edge.used) {
      const_cast<Edge &>(edge).used = true;
      path.push_back(edge.to);
      if (findPath(gr, edge.to, finish, path)) {
        return true;
      }
      path.pop_back();
    }
  }
  return false;
}

void solve() {
  int n, m, s, t;
  cin >> n >> m >> s >> t;

  vector<vector<Edge>> gr(n + 1);
  vector<int> level(n + 1);
  vector<int> ptr(n + 1);

  for (int i = 0; i < m; ++i) {
    int u, v;
    cin >> u >> v;
    gr[u].push_back({v, 1, 0, (int) gr[v].size(), false});
    gr[v].push_back({u, 0, 0, (int) gr[u].size() - 1, false});
  }

  int flow = maxFlow(s, t, gr, level, ptr);
  if (flow < 2) {
    cout << "NO\n";
    return;
  }

  vector<vector<int>> paths;
  for (int i = 0; i < 2; ++i) {
    vector<int> path;
    path.push_back(s);
    if (findPath(gr, s, t, path)) {
      paths.push_back(path);
    } else {
      cout << "NO\n";
      return;
    }
  }

  cout << "YES\n";
  for (auto &path : paths) {
    for (int node : path) {
      cout << node << " ";
    }
    cout << "\n";
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