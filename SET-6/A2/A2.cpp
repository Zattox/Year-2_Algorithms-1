#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const ll INF = 1e9;

vector<vector<int>> correct_floydWarshall(vector<vector<int>> dist, int n) {
  for (int k = 0; k < n; ++k) {
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        if (dist[i][k] != INF && dist[k][j] != INF) {
          dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
        }
      }
    }
  }
  return dist;
}

vector<vector<int>> incorrect_floydWarshall(vector<vector<int>> dist, int n, vector<string> &path) {
  path.push_back("======================================================\n");
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      for (int k = 0; k < n; ++k) {
        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
        path.push_back(format("d[{}][{}] = min(dist[{}][{}], dist[{}][{}] + dist[{}][{}]) = {}\n", i, j, i, k, k, j, i, j, dist[i][j]));
      }
      path.push_back("======================================================\n");
    }
  }
  return dist;
}

mt19937 rnd(13);

int main() {
  freopen("output.txt", "w", stdout);
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  while (true) {
    int n = 4;
    vector<vector<int>> dist(n, vector<int>(n, INF));

    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        if (i == j) {
          dist[i][j] = 0;
        } else {
          auto q = rnd() % 2;
          if (q == 0) {
            dist[i][j] = rnd() % 100 + 1;
          }
        }
      }
    }

    auto correct = correct_floydWarshall(dist, n);
    vector<string> path;
    auto incorrect = incorrect_floydWarshall(dist, n, path);
    if (correct != incorrect) {
      cout << "Start dist\n";
      for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
          cout << dist[i][j] << ' ';
        }
        cout << "\n";
      }
      cout << "Correct dist:\n";
      for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
          cout << correct[i][j] << ' ';
        }
        cout << "\n";
      }
      cout << "Incorrect dist:\n";
      for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
          cout << incorrect[i][j] << ' ';
        }
        cout << "\n";
      }
      for (auto el : path) {
        cout << el;
      }
      break;
    }
  }
}