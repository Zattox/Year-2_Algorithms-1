#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const ll INF = 1e18;

bool is_subset(vector<ll> &a, vector<ll> &b) {
  size_t i = 0, j = 0;
  while (i < a.size() && j < b.size()) {
    if (a[i] == b[j]) {
      i++;
      j++;
    } else if (a[i] > b[j]) {
      j++;
    } else {
      return false;
    }
  }
  return i == a.size();
}

bool bfs(vector<vector<ll>> &subset_graph, vector<ll> &l_match, vector<ll> &r_match, vector<ll> &dist, ll l_size) {
  const ll INF = 1e18;
  queue<ll> q;

  for (ll u = 0; u < l_size; ++u) {
    if (l_match[u] == -1) {
      dist[u] = 0;
      q.push(u);
    } else {
      dist[u] = INF;
    }
  }

  ll min_dist = INF;

  while (!q.empty()) {
    ll u = q.front();
    q.pop();

    if (dist[u] < min_dist) {
      for (ll v : subset_graph[u]) {
        if (r_match[v] == -1) {
          min_dist = dist[u] + 1;
        } else if (dist[r_match[v]] == INF) {
          dist[r_match[v]] = dist[u] + 1;
          q.push(r_match[v]);
        }
      }
    }
  }

  return min_dist != INF;
}

bool dfs(ll u, ll cur_dist, vector<vector<ll>> &subset_graph, vector<ll> &l_match,
         vector<ll> &r_match, vector<ll> &dist, ll l_size) {
  if (dist[u] == cur_dist) {
    dist[u] = INF;
    for (ll v : subset_graph[u]) {
      ll w = r_match[v];
      if (w == -1 || (dist[w] == cur_dist + 1 && dfs(w, cur_dist + 1, subset_graph, l_match, r_match, dist, l_size))) {
        l_match[u] = v;
        r_match[v] = u;
        return true;
      }
    }
  }
  return false;
}

ll max_match(vector<vector<ll>> &subset_graph, vector<ll> &l_match, vector<ll> &r_match, vector<ll> &dist, ll l_size) {
  ll match_size = 0;
  while (bfs(subset_graph, l_match, r_match, dist, l_size)) {
    for (ll u = 0; u < l_size; ++u) {
      if (l_match[u] == -1 && dfs(u, 0, subset_graph, l_match, r_match, dist, l_size)) {
        match_size++;
      }
    }
  }
  return match_size;
}

void solve() {
  ll n_juices;
  cin >> n_juices;

  unordered_map<string, ll> comp_id;
  ll next_id = 0;

  vector<vector<ll>> juices(n_juices);
  for (ll i = 0; i < n_juices; ++i) {
    ll n_comps;
    cin >> n_comps;
    juices[i].resize(n_comps);
    for (ll j = 0; j < n_comps; ++j) {
      string comp;
      cin >> comp;
      if (comp_id.find(comp) == comp_id.end()) {
        comp_id[comp] = next_id++;
      }
      juices[i][j] = comp_id[comp];
    }
    sort(juices[i].begin(), juices[i].end());
  }

  vector<vector<ll>> subset_graph(n_juices);
  vector<ll> l_match(n_juices, -1);
  vector<ll> r_match(n_juices, -1);
  vector<ll> dist(n_juices, 0);

  for (ll i = 0; i < n_juices; ++i) {
    for (ll j = 0; j < n_juices; ++j) {
      if (i == j) continue;
      if (is_subset(juices[i], juices[j])) {
        subset_graph[i].push_back(j);
      }
    }
  }

  ll match_size = max_match(subset_graph, l_match, r_match, dist, n_juices);
  ll min_cover = n_juices - match_size;
  cout << min_cover << "\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  solve();
}