#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const ll INF = 1e18;
int n;
vector<vector<int>> gr, children;
vector<int> values, leafCount;
vector<bool> isLeaf;
vector<vector<ll>> dp;

void buildTree(int v, int parent) {
  for (int u : gr[v]) {
    if (u != parent) {
      children[v].push_back(u);
      buildTree(u, v);
    }
  }
}

void calculateLeafCounts(int v) {
  if (children[v].empty()) {
    isLeaf[v] = true;
    leafCount[v] = 1;
    return;
  }

  isLeaf[v] = false;
  leafCount[v] = 0;

  for (int child : children[v]) {
    calculateLeafCounts(child);
    leafCount[v] += leafCount[child];
  }
}

void solve(int v) {
  if (isLeaf[v]) {
    dp[v].assign(leafCount[v] + 1, INF);
    dp[v][0] = abs(values[v] - 0);
    dp[v][1] = abs(values[v] - 1);
    return;
  }

  for (int child : children[v]) {
    solve(child);
  }
  dp[v].assign(leafCount[v] + 1, INF);

  if (children[v].size() == 1) {
    int child = children[v][0];
    for (int k = 0; k <= leafCount[v]; k++) {
      if (dp[child][k] != INF) {
        dp[v][k] = abs(values[v] - k) + dp[child][k];
      }
    }
  } else if (children[v].size() == 2) {
    int left = children[v][0], right = children[v][1];
    vector<ll> tmp(leafCount[v] + 1, INF);

    for (int k1 = 0; k1 <= leafCount[left]; k1++) {
      if (dp[left][k1] == INF) {
        continue;
      }
      for (int k2 = 0; k2 <= leafCount[right]; k2++) {
        if (dp[right][k2] == INF) {
          continue;
        }
        int totalLeaves = k1 + k2;
        tmp[totalLeaves] = min(tmp[totalLeaves], dp[left][k1] + dp[right][k2]);
      }
    }

    for (int k = 0; k <= leafCount[v]; k++) {
      if (tmp[k] != INF) {
        dp[v][k] = abs(values[v] - k) + tmp[k];
      }
    }
  }
}

ll findMinimumCost() {
  ll result = INF;
  for (ll cost : dp[1]) {
    result = min(result, cost);
  }
  return result;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n;

  gr.resize(n + 1);
  children.resize(n + 1);
  values.resize(n + 1);
  leafCount.resize(n + 1);
  isLeaf.resize(n + 1);
  dp.resize(n + 1);

  for (int i = 1; i <= n; i++) {
    cin >> values[i];
  }

  for (int i = 0; i < n - 1; i++) {
    int u, v;
    cin >> u >> v;
    gr[u].push_back(v);
    gr[v].push_back(u);
  }

  buildTree(1, 0);
  calculateLeafCounts(1);
  solve(1);

  cout << findMinimumCost() << "\n";

  return 0;
}
