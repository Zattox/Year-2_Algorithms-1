#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;

const int N = 100000;

vector<int> rk(N), parent(N);

int findPrev(int v) {
  if (parent[v] == v)
    return v;
  return parent[v] = findPrev(parent[v]);
}

void unionSet(int u, int v) {
  u = findPrev(u), v = findPrev(v);
  if (u == v)
    return;
  if (rk[u] > rk[v])
    swap(u, v);
  if (rk[u] == rk[v])
    ++rk[v];
  parent[u] = v;
}

void solve() {
  int n, m, k;
  cin >> n >> m >> k;
  for (int i = 0; i < n; ++i) {
    parent[i] = i;
  }

  vector<pair<string, pair<int, int>>> graph;
  for (int i = 0; i < m; ++i) {
    int x, y;
    cin >> x >> y;
  }

  for (int i = 0; i < k; ++i) {
    string str;
    cin >> str;
    int v, u;
    cin >> v >> u;
    graph.push_back({str, {v, u}});
  }

  string s;
  vector<string> ans;
  pair<int, int> cur;
  for (int i = k - 1; i >= 0; --i) {
    s = graph[i].first, cur = graph[i].second;
    if (s == "cut") {
      if (findPrev(cur.first) != findPrev(cur.second)) {
        unionSet(cur.first, cur.second);
      }
    } else {
      if (findPrev(cur.first) == findPrev(cur.second))
        ans.push_back("YES\n");
      else
        ans.push_back("NO\n");
    }
  }

  reverse(ans.begin(), ans.end());

  for (auto el : ans) {
    cout << el;
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