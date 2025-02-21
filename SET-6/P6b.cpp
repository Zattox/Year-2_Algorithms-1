#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int sumOfDigits(int number) {
  int sum = 0;
  while (number > 0) {
    sum += number % 10;
    number /= 10;
  }
  return sum;
}

vector<pair<int, int>> getValuesOfY(int x) {
  vector<pair<int, int>> values;
  string s = to_string(x);
  int len = (int) s.size();

  for (int i = 0; i < len; ++i) {
    for (int j = i; j < len; ++j) {
      string sub = s.substr(i, j - i + 1);
      int y = stoi(sub);
      if (y > 0) {
        int cost = sumOfDigits(y);
        values.emplace_back(y, cost);
      }
    }
  }

  return values;
}

void Dijkstra(int s, vector<ll> &dist, vector<int> &parent,
              vector<int> &valueOfY, vector<char> &operation) {
  int n = (int) dist.size() - 1;
  dist[s] = 0;
  set<pair<int, int>> q;
  q.insert({dist[s], s});

  while (!q.empty()) {
    int x = q.begin()->second;
    q.erase(q.begin());

    auto values = getValuesOfY(x);
    for (auto el : values) {
      int y = el.first;
      long long cost = el.second;

      int new_val = x + y;
      if (new_val <= n) {
        if (dist[new_val] > dist[x] + cost) {
          dist[new_val] = dist[x] + cost;
          parent[new_val] = x;
          operation[new_val] = '+';
          valueOfY[new_val] = y;
          q.insert({dist[new_val], new_val});
        }
      }

      new_val = x - y;
      if (new_val > 0) {
        if (dist[new_val] > dist[x] + cost) {
          dist[new_val] = dist[x] + cost;
          parent[new_val] = x;
          operation[new_val] = '-';
          valueOfY[new_val] = y;
          q.insert({dist[new_val], new_val});
        }
      }
    }
  }
}

const ll INF = 1e10;

void solve() {
  int n, a, b;
  cin >> n >> a >> b;

  vector<ll> dist(n + 1, INF);
  vector<int> parent(n + 1, -1);
  vector<int> valueOfY(n + 1, 0);
  vector<char> operation(n + 1, ' ');

  Dijkstra(a, dist, parent, valueOfY, operation);

  if (dist[b] == INF) {
    cout << "-1\n";
    return;
  }

  vector<pair<char, int>> path;
  int current = b;
  while (current != -1) {
    if (parent[current] != -1) {
      path.emplace_back(operation[current], valueOfY[current]);
    }
    current = parent[current];
  }
  reverse(path.begin(), path.end());

  cout << dist[b] << "\n";
  cout << path.size() << "\n";
  for (auto el : path) {
    cout << el.first << el.second << "\n";
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