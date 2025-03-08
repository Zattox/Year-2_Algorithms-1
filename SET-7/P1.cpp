#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const ll INF = 1e18;

struct Edge {
  int to;
  ll capacity;
  ll flow;
  int rev;
};

bool bfs(int start, int finish, vector<int> &level, vector<vector<Edge>> &gr) {
  queue<int> q;
  level.assign(gr.size(), -1);

  level[start] = 0;
  q.push(start);
  while (!q.empty()) {
    auto u = q.front();
    q.pop();
    for (auto &el : gr[u]) {
      if (level[el.to] == -1 && el.flow < el.capacity) {
        level[el.to] = level[u] + 1;
        q.push(el.to);
      }
    }
  }
  return level[finish] != -1;
}

ll dfs(int cur, int finish, ll flow, vector<int> &ptr, vector<int> &level, vector<vector<Edge>> &gr) {
  if (cur == finish || flow == 0) {
    return flow;
  }

  for (int &v = ptr[cur]; v < gr[cur].size(); ++v) {
    Edge &el = gr[cur][v];

    if (level[el.to] == level[cur] + 1 && el.flow < el.capacity) {
      ll pushed = dfs(el.to, finish, min(flow, el.capacity - el.flow), ptr, level, gr);
      if (pushed > 0) {
        el.flow += pushed;
        gr[el.to][el.rev].flow -= pushed;
        return pushed;
      }
    }
  }

  return 0;
}

void solve() {
  int n, m;
  cin >> n >> m;
  vector<vector<Edge>> gr(n);

  for (int i = 0; i < m; i++) {
    int u, v;
    ll w;
    cin >> u >> v >> w;
    --u, --v;
    gr[u].push_back({v, w, 0, (int) gr[v].size()});
    gr[v].push_back({u, 0, 0, (int) gr[u].size() - 1});
  }

  vector<int> level(n), ptr(n);
  int start = 0, finish = n - 1;
  ll totalFlow = 0;
  while (bfs(start, finish, level, gr)) {
    ptr.assign(gr.size(), 0);
    while (ll pushed = dfs(start, finish, INF, ptr, level, gr)) {
      totalFlow += pushed;
    }
  }

  cout << totalFlow;
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